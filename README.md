# C - Simple Shell

---
### this simple shell project is a simple implementation of a UNIX command interpreter written in C. It imitates the core behaviour of /bin/sh, the standard shell, by handling user commands, analyzing arguments, and environment management. By building this from scratch, we demonstrate a deep understanding of low-level system calls, the mechanics of process creation, memory management, and how the system locates executables using the PATH variable.
---

---
## Table of Contents
- Description 
- Project Files
- Learning Objectives
- Requirements 
- Compilation & Usage 
- Authors
---

---
## Learning Objectives
- Master system calls: fork, execve, wait, and access.
- Implement manual PATH resolution without using getenv.
- Manage the environment array (envp) and handle built-in commands.
- Analyze user input into tokens using strtok.
- Ensure robust error handling that matches the standard shell output format.
---

---
## Project Files
| File | Description |
| :--- | :--- |
| **main.c** | The main execution loop; contains the input reading logic, reads input via getline, and manages the shell's logic. |
| **shell.c** | Core process management; implements execute_command to handle the fork, execve, and wait lifecycle. |
| **shell.h** | Header file containing function prototypes, macros, and standard library includes. |
| **path.c** | Logic for locating commands. It searches through directories in the PATH environment variable. |
| **exec.c** | Handles the process lifecycle: forking, executing external programs, and waiting for completion. |
| **builtin_env.c** | Contains the env built-in function to print the current environment variables. |
| **env.c** | Helper functions to extract values from the environment and find the current working directory. |
| **trim.c** | Utility to clean user input by removing leading and trailing whitespace. |
| **man_1_simple_shell** | Manual page for the custom shell. |
| **AUTHORS** | List of contributors to the project. |
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

- Salman Ghannam Al-Mutairi
- Location: Riyadh, Saudi Arabia
- Student at Holberton School
- Email: sloome222@gmail.com
- GitHub: salman-ghannam1

--

- Afnan Mohammed Alfaidi
- Location: Riyadh, Saudi Arabia
- Physics graduate from the University of Jeddah
- Student at Holberton School
- Email: alfaidi.afnan@gmail.com
- GitHub: Afnan2049
---
