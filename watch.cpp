#include "main.h"

void watch(settings &s) {
	//Get rules
	rulesMap myRules;
	getRules(s.rules, myRules);

	dirMap dirMap1;
	dirMap dirMap2;
	//Initial scan
	fillDirMap(s.root, dirMap1);

	while(true) {
		sleep(s.interval);
		fillDirMap(s.root, dirMap2);
		changes(dirMap1,dirMap2, myRules);
		dirMap1 = dirMap2;

	}

}
