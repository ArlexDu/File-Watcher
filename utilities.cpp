#include "main.h"

//Gets modification time
time_t	get_mtime(const char *path) {
	time_t lastMod;
	struct stat s;
	if (lstat(path, &s) < 0) { fprintf(stderr, "Unable to check last time modified: %s\n", strerror(errno)); };
	lastMod = s.st_mtime;
    return lastMod;
}

//Trims beggining and end whitespace
std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//Fills in map holding rules
void getRules(std::string file_name, rulesMap &myRules) {
    myRules.insert(std::pair<std::string,std::vector<rule>>("MODIFY", std::vector<rule>()));
    myRules.insert(std::pair<std::string,std::vector<rule>>("CREATE", std::vector<rule>()));
    myRules.insert(std::pair<std::string,std::vector<rule>>("DELETE", std::vector<rule>()));
    
    std::ifstream fin(file_name);

    std::string action;
    std::string pattern;
    std::string command;

    while (fin >> action >> pattern) {
        if (action == "MODIFY" || action == "CREATE" || action == "DELETE" ) {
            rule R;
            R.pattern = pattern;

            std::string exec;
            getline(fin,exec);
            R.command = trim(exec);

            myRules[action].push_back(R);

        }
    }
}

//Fills in map holding directories
int fillDirMap(std::string r, dirMap &m) {
	DIR *dir;
	struct dirent *entry;
	struct stat file_stats;
	const char *root = r.c_str();

	lstat(root, &file_stats);

	//Check if root is directory
	if (!S_ISDIR(file_stats.st_mode)) {
        fprintf(stderr, "Please provide a directory as input.\n"); 
        return EXIT_FAILURE;
    }

    //Gets directory stream
    if ((dir = opendir(root)) == NULL) {
        fprintf(stderr, "find: '%s': %s\n", root, strerror(errno));
        return EXIT_FAILURE;
    }

    //Loops through directory stream
    char path[BUFSIZ];
    while ((entry = readdir(dir)) != NULL) {
    	char * name = entry->d_name;
    	//skip over "." and ".."
        if (!(strcmp(name,".")==0 || strcmp(name,"..")==0 || strcmp(name,"")==0)) {
        	memset(path, 0, strlen(path));

            strcpy(path, root);
        	strcat(path, "/");
            strcat(path, entry->d_name);
            std::string path_string(path);

        	lstat(path, &file_stats);

        	file f;
        	f.modtime = get_mtime(path);

            char * tmp_basename = basename(path);
            f.basename = strdup(tmp_basename);

        	char fullpath [PATH_MAX+1];
        	char * tmp_fullpath = realpath(path, fullpath);
            f.fullpath = strdup(tmp_fullpath);
        	
        	m[path_string]=f;

        }

    }
    return 0;
}