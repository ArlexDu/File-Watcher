# File-Watcher
File watching service called "rorschach" written in C++

Scans a given root directory for changes and executes command based on user-specified rules when a change in the files is detected.

## USAGE:

$ ./rorschach -h
Usage: rorschach [options] ROOT

Options:
    <p>		-h          Print this help message</p>
   	<p>		-f RULES    Load rules from this file (default is rules)</p>
	<p>		-t SECONDS  Time between scans (default is 5 seconds)</p>

The "rules" file contains rules in the following format:
EVENT	PATTERN    ACTION

<p>		eg: MODIFY    *.c    cc -o ${BASEPATH} ${FULLPATH}</p>


## TO DO:
-Fix Memory Leaks
