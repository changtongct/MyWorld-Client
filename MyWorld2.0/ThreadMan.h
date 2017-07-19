#ifndef _THREADMAN_H_
#define _THREADMAN_H_

#include <Windows.h>
#include <unordered_map>
#include <string>

using namespace std;

class ThreadMan {
public:
	static ThreadMan* getInstance();
	~ThreadMan(){}

	void addThreadID(string t_name, DWORD t_id);
	DWORD getThreadID(string t_name);

private:
	ThreadMan();
	static ThreadMan* instance;
	unordered_map<string, DWORD> name_id_map;
};

#endif