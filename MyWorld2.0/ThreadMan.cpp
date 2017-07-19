#include "ThreadMan.h"

ThreadMan::ThreadMan() {}

ThreadMan* ThreadMan::instance = new ThreadMan();

ThreadMan* ThreadMan::getInstance() {
	
	return instance;
}

void ThreadMan::addThreadID(string t_name, DWORD t_id) {
	name_id_map[t_name] = t_id;
}

DWORD ThreadMan::getThreadID(string t_name) {
	if (name_id_map.find(t_name) == name_id_map.end()) {
		printf("no this thread !");
		return -1;
	}
	return name_id_map[t_name];
}