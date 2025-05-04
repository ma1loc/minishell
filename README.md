# Minishell

A simple shell implementation based on bash.

![C](https://img.shields.io/badge/language-C-blue)
![Status](https://img.shields.io/badge/status-completed-success)

![VN20250504_150041-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/b9cb0c3b-cc29-4c58-931a-03ff285a1f33)


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
