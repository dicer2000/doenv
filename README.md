# doenv

A env derivation by Brett Huffman for CMP SCI 4760 - Project 1

This program implements env-like functionality.  It examines the environment and modifies it to execute another command. When called without arguments, the
env command writes the current environment to standard output. The optional utility argument specifies the command
to be executed under the modified environment.


A log was kept of each day's activity.  It is found at the end of this README file.

A Git repository was maintained with a public remote found here: https://github.com/dicer2000/doenv

## Program Switches
The program can be invoked as:

```
doenv [-h]
doenv 
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

## Problems
The most serious problem was

## Work Log

1/28/2021 - Started re-working for doenv command. Created basic outline of program, Makefile, README. Performed Testing. Started a test program. Tested on UNIX. Fixed stat problem
1/29/2021 - Redesigned getopt logic; Added switch logic; Testing; Added pError
1/30/2021 - Finished Environ logic, debugging

*©2021 Brett W. Huffman*