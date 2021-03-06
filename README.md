# doenv

A env derivation by Brett Huffman for CMP SCI 4760 - Project 1 - V1.1

This program implements env-like functionality.  It examines the environment and modifies it to execute another command. When called without arguments, the
env command writes the current environment to standard output. The optional utility argument specifies the command to be executed under the modified environment.


A log was kept of each day's activity.  It is found at the end of this README file.

A Git repository was maintained with a public remote found here: https://github.com/dicer2000/doenv

## Program Switches
The program can be invoked as:

```
doenv [-h]
doenv [-i] [var1=value] [var2=value] [...] {command1 [; command2] [; ...]}
Options:
  -h Show this help message
  -i Replace the external environment variable
  Optional environment variables can be defined to add/replace variables
  Commands are utilities to execute after the environment has been changed
  If commands are omitted, the updated environment is printed
```

## Install
To install this program, clone it with git to the folder to which you want 
it saved.
```
git clone https://github.com/dicer2000/doenv
```
## Compile
To compile the mydu application, simply run the make command:
```
make
```
## Run
To run the program, use the doenv command.  You can use any of the attributes listed in program switches area.

## Problems / Issues
The most serious problem was finding out how to best delete and re-add environment variables.  If I just set environ = NULL to delete all vars, a segment fault was generated.  However, I also found that clearenv() was not supported on all platforms.

My problem was two-fold.  First, I can use clearenv() on UNIX systems that support it.  That's most preferred.  However, if it isn't supported, then the same effect can be acheived by doing *environ = NULL (per UNIX man page: https://man7.org/linux/man-pages/man3/clearenv.3.html).

I needed to add the * before environ to dereference environ.  I was getting a segmentation fault when I was doing it to environ.

Another issue came up during testing:  When an unknown command is supplied to the application, it is outputting the perror with an error code of "No Such Process".  That's the closest I could find.  Also, the shell that is created also reports "command not found", so I end up with two error statements.  It looks like this:
```
➜ ./doenv clo
sh: clo: command not found
Unknown command: clo: No such process
```
Per my conversation with Jared Diehl on 2/8/2021, this response is acceptable.

## Work Log

- 1/28/2021 - Started re-working for doenv command. Created basic outline of program, Makefile, README. Performed Testing. Started a test program. Tested on UNIX. Fixed stat problem
- 1/29/2021 - Redesigned getopt logic; Added switch logic; Testing; Added pError
- 1/30/2021 - Finished Environ logic, debugging; Trying on different platforms to determine which will work best for UNIX. Made additional comments.  Handed in v1.0 of the program
- 2/7/2021 - Performed testing and changed the error reporting to better utilize sterror.

*©2021 Brett W. Huffman*