*This project has been created as part of the 42 curriculum by kalnajja.*

# ft_printf

## Description

A re-implementation of the C `printf` function, built as a static library (`libftprintf.a`).

- Conversions: `%c` `%s` `%p` `%d` `%i` `%u` `%x` `%X` `%%`
- Returns the number of printed characters, or `-1` if `write` fails.
- Unknown specifiers (e.g. `%y`) are printed as-is, like glibc.

## Instructions

```bash
make         # builds libftprintf.a
make clean   # removes object files
make fclean  # removes objects and the library
make re      # rebuilds everything
```

Usage:

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -I. -o test
```

## Variadic function (`stdarg.h`)

`ft_printf` is a **variadic function**: it takes a fixed first argument (the format string) followed by `...`, an unknown number of extra arguments.

```c
int ft_printf(const char *format, ...);
```

C gives no way to ask "how many arguments did the caller pass?", so the **format string is the only source of truth**: each `%` tells us that one more argument is waiting, and which type it has. The `<stdarg.h>` macros are used to read them:

| Macro | Job | Where it is used |
|---|---|---|
| `va_list args` | Holds the state of the argument list (a cursor). | Declared in `ft_printf` |
| `va_start(args, format)` | Puts the cursor right after the last named parameter (`format`). | Start of `ft_printf` |
| `va_arg(args, type)` | Returns the next argument as `type` and moves the cursor forward. | Dispatcher (`ft_handle_format`), once per conversion |
| `va_end(args)` | Cleans up the list. Must be called before returning. | End of `ft_printf` and in `handle_error` |

### Which type for which specifier

| Specifier | `va_arg` type | Note |
|---|---|---|
| `%c` | `int` | `char` is promoted to `int` when passed through `...` |
| `%s` | `char *` | `NULL` prints `(null)` |
| `%p` | `void *` | cast to `uintptr_t` to print; `NULL` prints `(nil)` |
| `%d` `%i` | `int` | |
| `%u` `%x` `%X` | `unsigned int` | |
| `%%` | none | no argument is consumed |

### Flow of the `va_list`

```
ft_printf(format, ...)
   va_list args;
   va_start(args, format);        <- cursor placed after `format`
        │
        ▼
   ft_process_format(..., &args)  <- passed down by pointer
        │
        ▼
   ft_handle_format(spec, &args)
        └── va_arg(*args, int)    <- cursor moves, one argument consumed
        │
        ▼
   va_end(args);                  <- always, on success AND on error
```

Two rules to remember:

- The `va_list` is passed **by pointer**, so every `va_arg` call advances the same cursor. If it were copied, the caller would not see the cursor move and the next conversion would read the wrong argument.
- Every `va_start` must have a matching `va_end`, including on the error path (that is why `handle_error` calls `va_end`).
- `%%` and unknown specifiers must **not** call `va_arg`, otherwise the arguments get out of sync.

## How it works

The code is split into three layers. Each layer only talks to the one below it.

```
        ┌────────────────────────────────────────┐
        │ 1. PARSER            (ft_printf.c)     │
        │    walks the format string             │
        └───────────────────┬────────────────────┘
                            │  '%' + specifier
                            ▼
        ┌────────────────────────────────────────┐
        │ 2. DISPATCHER   (ft_handle_format.c)   │
        │    specifier  ->  right printer        │
        └───────────────────┬────────────────────┘
                            │
                            ▼
        ┌────────────────────────────────────────┐
        │ 3. PRINTERS                            │
        │    putnbr / putstr / putptr / hex      │
        │    build the output                    │
        └───────────────────┬────────────────────┘
                            │
                            ▼
        ┌────────────────────────────────────────┐
        │ ft_putchar_fd   (one char at a time)   │
        └───────────────────┬────────────────────┘
                            │
                            ▼
                      ( write )
```

| Layer | Job |
|---|---|
| Parser | Reads the format string. Normal chars are written directly. On `%`, it hands the next char to the dispatcher and adds the returned count. |
| Dispatcher | A single `if/else` chain: `d` goes to `ft_putnbr_fd`, `s` to `ft_putstr_n`, and so on. Unknown specifiers go to `ft_print_unknown`. |
| Printers | Each one prints its type and returns how many chars it wrote. All of them end up calling `ft_putchar_fd`. |

### Example: `ft_printf("a%d\n", 42)`

1. `a` is a regular char, so `ft_print_regular_char` writes it. count = 1
2. `%` followed by `d`, so `ft_handle_conversion` calls `ft_handle_format('d')`.
3. The dispatcher calls `ft_putnbr_fd(42)`, which recurses: prints `4`, then `2`. It returns 2. count = 3
4. `\n` is a regular char. count = 4
5. End of string, `ft_printf` returns **4**.

### Errors

If any `write` fails, the `-1` travels upward through every layer until `ft_printf` calls `handle_error` (`va_end` then `return -1`).

### Call graph (who calls who)

```
ft_printf
├── ft_process_format
│   ├── ft_print_regular_char ─────────────────────► write
│   └── ft_handle_conversion
│       └── ft_handle_format
│           ├── 'c' '%'  ► ft_putchar_fd ──────────► write
│           ├── 's'      ► ft_putstr_n
│           │              └── ft_putstr_fd
│           │                  └── ft_putchar_fd
│           ├── 'p'      ► ft_putptr_fd
│           │              ├── ft_putstr_n   ("(nil)" and "0x")
│           │              └── ft_putptr_hex
│           │                  └── ft_putchar_fd
│           ├── 'd' 'i'  ► ft_putnbr_fd ───────────► ft_putchar_fd
│           ├── 'u'      ► ft_putnbr_unsigned_fd ──► ft_putchar_fd
│           ├── 'x'      ► ft_putnbr_hex_fd ───────► ft_putchar_fd
│           ├── 'X'      ► ft_putnbr_hex_upper_fd ─► ft_putchar_fd
│           └── else     ► ft_print_unknown ───────► ft_putchar_fd
└── handle_error        (called when any step returns -1)

ft_putchar_fd ─────────────────────────────────────► write
```

<details>
<summary>Function reference (click to expand)</summary>

| Function | File | Called by | Role |
|---|---|---|---|
| `ft_printf` | `ft_printf.c` | user | Entry point, accumulates the count. |
| `ft_process_format` | `ft_printf.c` | `ft_printf` | Conversion or regular char? |
| `ft_handle_conversion` | `ft_printf.c` | `ft_process_format` | Reads the specifier, advances by 2. |
| `ft_print_regular_char` | `ft_printf.c` | `ft_process_format` | Writes a normal char. |
| `handle_error` | `ft_printf.c` | `ft_printf` | `va_end` and return `-1`. |
| `ft_handle_format` | `ft_handle_format.c` | `ft_handle_conversion` | Specifier to printer. |
| `ft_print_unknown` | `ft_handle_format.c` | `ft_handle_format` | Prints `%` + unknown char. |
| `ft_putchar_fd` | `ft_putchar_fd.c` | most functions | Writes one char. |
| `ft_putstr_fd` | `ft_putstr_fd.c` | `ft_putstr_n` | Writes a string. |
| `ft_putstr_n` | `ft_putstr_fd.c` | `ft_handle_format`, `ft_putptr_fd` | NULL-safe string (`(null)`). |
| `ft_putnbr_fd` | `ft_putnbr_fd.c` | `ft_handle_format` | Signed decimal, `INT_MIN` safe. |
| `ft_putnbr_unsigned_fd` | `ft_putnbr_unsigned_fd.c` | `ft_handle_format` | Unsigned decimal. |
| `ft_putnbr_hex_fd` | `ft_putnbr_hex_fd.c` | `ft_handle_format` | Lowercase hex. |
| `ft_putnbr_hex_upper_fd` | `ft_putnbr_hex_upper_fd.c` | `ft_handle_format` | Uppercase hex. |
| `ft_putptr_fd` | `ft_putptr_fd.c` | `ft_handle_format` | `0x...` or `(nil)`. |
| `ft_putptr_hex` | `ft_putptr_fd.c` | `ft_putptr_fd` | Recursive hex for `uintptr_t`. |

</details>

## Resources

- `man 3 printf`, `man 3 stdarg`, `man 2 write`

### AI usage

AI (Claude) was used for the following tasks:

- **Learning:** explaining the topic of API calling (how functions call other functions and the `write` system call), to help me understand how the layers of the project talk to each other.
- **Review:** reviewing my code, suggesting tests, and pointing out what to clean up before submission.
- **Documentation:** helping structure this README and its diagrams.

All the code was written, understood, and tested by me.
