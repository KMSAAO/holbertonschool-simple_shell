# 0x16. C - Simple Shell

This project is about writing a simple UNIX command interpreter, similar in behavior to /bin/sh but much simpler.

## Description
The shell:
- Displays a prompt (if in interactive mode).
- Waits for the user to type a command.
- Parses the command and its arguments.
- Searches for the command in the PATH.
- Creates a new process and executes the command with execve.
- Waits for the command to finish (unless in non-interactive mode / end of file).
- Must work in both interactive and non-interactive modes:
  - ./hsh
  - echo "ls" | ./hsh
  - cat commands.txt | ./hsh

Your shell must have the same output and the same error messages as /bin/sh, except that the program name must be your argv[0].

## Requirements
- Compiled on Ubuntu 20.04 LTS with:
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
- No memory leaks.
- No more than 5 functions per file.
- All header files must be include-guarded.
- A README.md, a man page, and an AUTHORS file are mandatory.

## Usage
Interactive:
    ./hsh
    ($) ls
    ($) exit

Non-interactive:
    echo "ls" | ./hsh
    cat file_with_cmds | ./hsh

## Files
- README.md
- man_1_simple_shell
- AUTHORS

