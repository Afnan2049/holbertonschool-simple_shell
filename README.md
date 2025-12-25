# C - Simple Shell

---
### this simple shell project is a simple implementation of a UNIX command interpreter written in C. It imitates the behaviour of the standard shell by handling user commands, executing programmes by their full paths, and mimics the behaviour of /bin/sh. It reads user input, analyses arguments, and executes system commands. It demonstrates a deep understanding of low-level system calls, memory management, and process synchronization.
---

---
## Table of Contents
- Description 
- Project Files
- Requirements 
- Compilation & Usage 
- Authors
---

---
## Description
 This project is a simple UNIX command line interpreter (shell) written in C. It replicates basic functionalities of the `/bin/sh` shell, including command execution, and argument parsing.
---

---
|Project Files|File|Description| 
|:------:|:-------------:|
|main.c|Entry point of the shell; contains the infinite loop and input reading logic|
|shell.c|Contains helper functions for string trimming and command execution|
|shell.h|Header file containing function prototypes, macros, and standard library includes|
|man_1_simple_shell |Manual page for the custom shell|
|AUTHORS|List of contributors to the project|
---

---
## Requirements

- Allowed editors: `vi`, `vim`, `emacs`.
- Compiled on Ubuntu 20.04 LTS using `gcc -Wall -Werror -Wextra -pedantic -std=gnu89`.
- No memory leaks. 
- Maximum of 5 functions per file.
- Code must adhere to the Betty style. 
- Include guards are mandatory for header files.
---

---
## Compilation:

To compile and run the simple shell, run the following commands:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

./hsh
---

---
## Authors:

- Salman Ghannam Al-Motairi
- Location: Riyadh, Saudi Arabia
- Student at Holberton School
- Email: sloome222@gmail.com
- GitHub: salman-ghannam1

- Afnan Mohammed Alfaidi
- Location: Riyadh, Saudi Arabia
- Physics graduate from the University of Jeddah
- Student at Holberton School
- Email: alfaidi.afnan@gmail.com
- GitHub: Afnan2049
---
