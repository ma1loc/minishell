# ft_printf

ft_printf is a custom implementation of the `printf` function in C. This project is part of the 1337 curriculum and aims to recreate formatted output functionality while working with variadic arguments.

## How Variadic Functions Work

In C, functions like `printf` use variadic arguments to handle a variable number of inputs. Variadic functions rely on:

1. **Registers**: On many modern systems, the first few function arguments are stored in CPU registers like `RDI`, `RSI`, etc., for efficiency.
2. **Stack**: If there are more arguments than available registers, the remaining arguments are stored in the stack.

### Registers
- Registers are small, fast memory locations inside the CPU.
- In the **x86-64 ABI**, the first arguments are passed in registers:
  - **General-purpose registers**: `RDI`, `RSI`, `RDX`, `RCX`, `R8`, `R9`.
  - **Floating-point registers**: `XMM0` to `XMM7`.
- Arguments exceeding the available registers are stored in the stack.

### `va_list` and Variadic Functions
The C standard provides tools to handle variadic arguments via `<stdarg.h>`:

- **`va_list`**: Tracks where the arguments are located (registers or stack).
- **`va_start`**: Initializes the `va_list` to point to the first argument.
- **`va_arg`**: Retrieves the next argument and moves to the next.
- **`va_end`**: Cleans up the `va_list` after usage.

## How ft_printf Works

1. **Parse the format string**:
   - Process normal text by printing it directly.
   - Handle format specifiers (e.g., `%d`, `%s`) by fetching arguments.

2. **Retrieve arguments**:
   - Use `va_arg` to get each argument based on the format specifier.
   - Convert the arguments into strings or appropriate formats.

3. **Output the result**:
   - Combine text and formatted arguments.
   - Use `write` to output the final result.

## Supported Format Specifiers
- `%c`: Print a single character.
- `%s`: Print a string.
- `%d` / `%i`: Print a decimal integer.
- `%u`: Print an unsigned decimal integer.
- `%x` / `%X`: Print a hexadecimal number (lowercase/uppercase).
- `%%`: Print a literal `%`.include "ft_printf.h"

> ⚠️ **Just for Educational Purposes** 📚  
> This project is for learning and practicing C programming. Do not use it in production environments.  


