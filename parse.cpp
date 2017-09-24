#include "main.h"

//Function to parse command line options
void parse(int argc, char* argv[], settings &s) {
	if (argc == 1)
		usage(); 

	int argind = 1;
	while (argind < argc) {
		char* arg = argv[argind++];

        if (strcmp(arg, "-h")==0) {
            usage();

        }else if(argind < argc) {
        	if (strcmp(arg, "-t")==0) {
        		s.interval = atoi(argv[argind++]);
        	}else if (strcmp(arg, "-f")==0){
        		s.rules = argv[argind++];
        	}
        }else{
        	s.root = arg;
        }
	}
}

void usage() {
	fprintf(stderr, "Usage: rorschach [options] ROOT\n");
	fprintf(stderr, "\nOptions:\n");
	fprintf(stderr, "    -h          Print this help message\n");
	fprintf(stderr, "    -f RULES    Load rules from this file (default is rules)\n");
	fprintf(stderr, "    -t SECONDS  Time between scans (default is 5 seconds)\n");
	exit(1);

}