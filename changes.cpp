#include "main.h"


void changes(dirMap &fileMap1, dirMap &fileMap2, rulesMap myRules) {
	std::vector<std::string> checked;
	char * bname;
	char * fullpath;
	time_t oldTime;
	time_t newTime;
	for (const auto &p: fileMap1) {
		bname = fileMap1[p.first].basename;
		fullpath = fileMap1[p.first].fullpath;
		//std::cout << "p.first: " << p.first << std::endl;
		//std::cout << fileMap1[p.first].basename << std::endl;
		if( access( p.first.c_str(), F_OK ) == -1 ) {
			std::cout << "Detected 'DELETE' event for " << bname << "\n";
			doesMatch("DELETE", bname, fullpath, myRules);
			fileMap2.erase(p.first);
		}else{
			//if in both maps, compare mod times
			oldTime = fileMap1[p.first].modtime;
			newTime = get_mtime(p.first.c_str());
			if (newTime > oldTime) {
				std::cout << "Detected 'MODIFY' event for " << bname << "\n";
				doesMatch("MODIFY", bname, fullpath, myRules);
			}
		}
		checked.push_back(p.first);
	}
	//now check for newly created files
	for (const auto &p: fileMap2) {
		bname = fileMap2[p.first].basename;
		fullpath = fileMap2[p.first].fullpath;

		//if we already determined it was modified it will be in vector, otherwise it must be new
		bool found = false;
		for (const auto &v: checked) {
			if (v == p.first) {
				found = true;
			}
		}
		if (found == false) {
			std::cout << "Detected 'CREATE' event for '" << bname << "'\n";
			doesMatch("CREATE", bname, fullpath, myRules);
			checked.push_back(p.first);
		}
			
	}
}

bool doesMatch(std::string event, const char * basename, const char * fullpath, rulesMap myRules) {

	for ( auto it : myRules[event] ) {
			const char * pattern = it.pattern.c_str();
			if (fnmatch(pattern, basename, FNM_FILE_NAME) == 0) {
				execute(event, basename, fullpath, it.command);
				return true;
			}else{
				return false;
			}
	}
	return false;
}

int	    execute(std::string EVENT,
				const char * BASENAME, 
				const char * FULLPATH,
				std::string command
				) {

	//set environment variables
	char time_char[16];
 	snprintf(time_char, 16, "%lu", time(NULL));

 	char * tmp_event = strdup(EVENT.c_str());

    char *args[4];
    std::string arg0 = "/bin/sh";
    std::string arg1 = "-c";
    args[0] = strdup(arg0.c_str());
    args[1] = strdup(arg1.c_str());

    char * tmp_command = strdup(command.c_str());
    args[2] = tmp_command;
    args[3] = NULL;
    //add null terminator


 	//fork and execution
	pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error: Fork did not work!\n"); 
    } else if (pid > 0) {   // we are the parent
        int status;
        wait(&status);
    } else {            // we are the child
    	setenv("BASEPATH",BASENAME,1);
    	setenv("FULLPATH",FULLPATH,1);
    	setenv("EVENT",tmp_event,1);
    	setenv("TIMESTAMP",time_char,1);
        execvp(args[0], args);
        return EXIT_FAILURE;  // this will only be reached if execvp goes wrong
    }
    return 0;
}