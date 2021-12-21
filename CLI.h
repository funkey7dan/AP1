

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"
#include <vector>

using namespace std;

class CLI {
    vector<Command*> commands;
	DefaultIO* dio;
public:
	CLI(DefaultIO* dio);
	void start();
	virtual ~CLI();
};

#endif /* CLI_H_ */
