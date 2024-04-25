# Pipex

## Summary
This project allows you to explore the details of a UNIX mechanism by implementing it in your program.


## Table of Contents
- [Common Instructions](#common-instructions)
- [Mandatory Part](#mandatory-part)
- [Bonus Part](#bonus-part)


## Common Instructions
- Your project must be written in C.
- Your project must be written in accordance with the Norm.
- Your functions should not quit unexpectedly (segmentation fault, bus error, double free, etc) apart from undefined behaviors.
- All heap allocated memory space must be properly freed when necessary. No leaks will be tolerated.
- If required, you must submit a Makefile which will compile your source files.
- Your Makefile must at least contain the rules $(NAME), all, clean, fclean, and re.
- To turn in bonuses, include a rule bonus in your Makefile.
- If your project allows you to use your libft, include a separate libft folder with its associated Makefile.
- We encourage you to create test programs for your project.

## Mandatory Part
**Program name:** pipex

**Turn in files:** Makefile, *.h, *.c

**Makefile:** NAME, all, clean, fclean, re

**Arguments:** file1 cmd1 cmd2 file2

**External functs.:**
- open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid
- ft_printf and any equivalent YOU coded
- Libft authorized: Yes

**Description:**
This project is about handling pipes. Your program will be executed as follows: ```./pipex file1 cmd1 cmd2 file2```
It must take 4 arguments:
- file1 and file2 are file names.
- cmd1 and cmd2 are shell commands with their parameters.
It must behave exactly the same as the shell command below:
```$> < file1 cmd1 | cmd2 > file2```
### Examples
```$> ./pipex infile "ls -l" "wc -l" outfile```
Should behave like: ```< infile ls -l | wc -l > outfile```

```$> ./pipex infile "grep a1" "wc -w" outfile```
Should behave like: ```< infile grep a1 | wc -w > outfile```
### Requirements
Your project must comply with the following rules:
- You have to turn in a Makefile which will compile your source files. It must not relink.
- You have to handle errors thoroughly. In no way your program should quit unexpectedly.
- Your program mustn't have memory leaks.

## Bonus Part
You will get extra points if you:
- Handle multiple pipes.
- Support "<<" and ">>" when the first parameter is "here_doc".

The bonus part will only be assessed if the mandatory part is perfect.
