# Minishell

A simple shell implementation based on bash.

![C](https://img.shields.io/badge/language-C-blue)
![Status](https://img.shields.io/badge/status-completed-success)

![minishell](https://github.com/user-attachments/assets/6f129293-a94d-42be-9fd8-2e9259230c24)

## Overview

Minishell is a custom implementation of a basic command line interpreter, similar to bash. This project is part of the 42 School curriculum and focuses on process creation, file descriptors, and signal handling in a Unix environment.

## Features

### Command Execution
- Execute external commands with arguments (e.g., `ls -la`, `grep pattern file`)
- Handle executable paths and environment PATH variable

### Built-in Commands
- `echo`: Display messages with `-n` option support
- `cd`: Change current directory
- `pwd`: Display current working directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: Display environment variables
- `exit`: Exit the shell with status code

### Input/Output Handling
- Input redirection (`<`)
- Output redirection (`>`)
- Append output (`>>`)
- Here documents (`<<`)
- Pipes (`|`) to connect commands

### Environment
- Environment variable expansion (e.g., `$USER`, `$PATH`)
- Exit status variable (`$?`)

### Signal Handling
- Ctrl+C (SIGINT): Interrupt current process
- Ctrl+D (EOF): Exit shell
- Ctrl+\ (SIGQUIT): Ignored in interactive mode

## Installation

```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
make
```

## Usage

```bash
./minishell
```

### Examples

Basic command execution:
```
> ls -la
```

Redirections:
```
> echo "Hello" > file.txt
> cat < file.txt
```

Pipes:
```
> ls -la | grep .c
```

Environment variables:
```
> echo $USER
> export VAR=value
> echo $VAR
```

## Technical Implementation

- **Lexer/Parser**: Tokenizes and analyzes user input
- **Command Execution**: Creates child processes using fork and execve
- **Redirections**: Manages file descriptors for I/O operations
- **Environment Management**: Handles environment variables in a linked list
- **Signal Handling**: Custom signal handlers for terminal signals

## Dependencies

- GNU Readline library

## Author Username

[@ma1loc](https://github.com/ma1loc) - [@bronIIcode](https://github.com/bornIIcode)

---

*This project was completed as part of the 42 School curriculum.*