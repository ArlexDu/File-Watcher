#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fstream>
#include <vector>
#include <map>
#include <fnmatch.h>

int notify();

// --- Used to hold directory information ---
typedef struct {
	char * basename;
	char * fullpath;
	time_t modtime;
} file;

typedef std::map<std::string, file> dirMap;
//KEY= File path, VALUE= File info 


// --- Used to store rule information ---
typedef struct {
	std::string pattern;
	std::string command; 
} rule;

typedef std::map<std::string, std::vector<rule>> rulesMap;
//KEY= Event type (Modify, Create, Delete), VALUE= vector of individual rules


// --- Used to hold command line options. Defaults are intiliazed below ---
typedef struct {
	std::string rules = "rules";
	int interval = 5;
	std::string root = ".";
} settings;


// --- Functions from "parse.cpp" ---
void parse(int argc, char* argv[], settings &s);
void usage();


// --- Functions from "watch.cpp" ---
void watch(settings &s);

// --- Functions from "utilities.cpp" ---
int fillDirMap(std::string root, dirMap &m);
time_t get_mtime(const char *path);
void getRules(std::string file_name, rulesMap &myRules);

// --- Functions from "changes.cpp" ---
bool doesMatch(std::string event, const char * basename, const char * fullpath, rulesMap myRules);
void changes(dirMap &map1, dirMap &map2, rulesMap myRules);
int	execute(std::string EVENT, const char * BASENAME, const char * FULLPATH, std::string command);

#endif
