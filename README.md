# Its_PKs_Shell

### An interactive user defined bash-like shell


*Coded by:*
**Prajwal Krishna**

_______________

This **README** file contains :
 1. Information About the Shell
 2. How to run
 3. List of builtin commands
 4. File structure

----------


## About The Game
An interactive user defined bash-like shell which supports semi-colon separated list of commands.It can take commands in input check if a builtin exists if exists then run the builtin else run it as separate process.

----------

## Running the program

- make main.c
- ./ItsPKsshell

-----------
## Builts in Commands

Command | Description | Flags | No. of Arguments
---- | ---- | ---- | ----
ls | Shows files and directory |-a,-l |0 or more
pwd| Shows current directory | - | -
cd| Change directory | - | 1
echo| Print on terminal |-| 0 or more
exit|Exit terminal|-|-
pinfo|Display process Info|-|0 or 1
clock|Starts foreground clock|-t,-n|1 or 2

## Features
* Supports semi-colon separated commands
* Has built in clock
* Modular code structure  
* Supports background process creation when command followed by '&'.
* Prints exit message when background exits

## File Structure

 * [argumentize.c](./argumentize.c) - Have functions to parse a command
 * [builtin_pk_ls.c](./builtin_pk_ls.c) - Have builtin ls command
 * [exec_clock.c](./exec_clock.c) - Have clock builtin command
 * [commandParser.c](./commandParser.c) - Have command parser
 * [display.c](./display.c) - Have functions to display
 * [execCmd.c](./execCmd.c)
 * [input.c](./input.c)
 * [lineParser.c](./lineParser.c)
 * [pinfo.c](./pinfo.c)
 * [main.c](./main.c)
 * [custom_header.h](./custom_header.h) - Has functions declaration and prototypes
 * [main.c](./main.c)
 * [makefile](./makefile) - Makes all files
 * [LICENSE](./LICENSE) - MIT License
 * [README.md](./README.md) - Readme aka about



_______________

#### Prajwal Krishna Maitin
