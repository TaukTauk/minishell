# Minishell

A simple UNIX command-line shell implementation developed as part of the 42 school curriculum.

## Overview

Minishell is a simplified version of a bash-like shell that implements basic functionality including command execution, pipes, redirections, environment variables, and built-in commands. This project deepens understanding of processes, file descriptors, and signal handling in Unix-like operating systems.

## Features

- Command execution with PATH variable support
- Command history
- Environment variable expansion (`$VAR`)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Redirections (`<`, `>`, `>>`)
- Heredoc (`<<`)
- Pipes (`|`)
- Exit status handling (`$?`)
- Quote handling (single and double quotes)

## Built-in Commands

- `echo`: Display a line of text
- `cd`: Change the current directory
- `pwd`: Print the current working directory
- `export`: Set or display environment variables
- `unset`: Remove environment variables
- `env`: Display all environment variables
- `exit`: Exit the shell

## Installation

### Prerequisites

- GCC compiler
- Make
- Readline library

### Building

```bash
git clone https://github.com/TaukTauk/minishell.git
cd minishell
make
```

## Usage

```bash
./minishell
```

## Examples

```
minishell$ ls -la
minishell$ echo "Hello, world!"
minishell$ cd src
minishell$ pwd
minishell$ cat file.txt | grep pattern > output.txt
minishell$ export VAR=value
minishell$ echo $VAR
minishell$ exit
```

## Project Structure

```
.
├── include/        # Header files
├── src/            # Source files
├── Makefile        # Build instructions
└── README.md       # Project documentation
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- 42 School for the project requirements and educational framework
- The Bash documentation, which provided guidance on shell behavior
