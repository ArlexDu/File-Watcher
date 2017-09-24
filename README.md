# File-Watcher
File watching service called "rorschach" written in C++

Scans a given root directory for changes and executes command based on user-specified rules when a change in the files is detected.

## USAGE:

$ ./rorschach -h
Usage: rorschach [options] ROOT

Options:
-h          Print this help message
-f RULES    Load rules from this file (default is rules)
-t SECONDS  Time between scans (default is 5 seconds)

The "rules" file contains rules in the following format:
EVENT	PATTERN    ACTION

eg: MODIFY    *.c    cc -o ${BASEPATH} ${FULLPATH}


## TO DO:
-Fix Memory Leaks
