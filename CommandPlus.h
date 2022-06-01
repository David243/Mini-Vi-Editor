#ifndef COMMAND_
#define COMMAND_
#include<string>
using namespace std;

class CommandPlus
{
public:
	CommandPlus();
	void setPosition(int);
	int getPosition() const;
	void setCommand(char);
	char getCommand() const;
	string getValue() const;
	void setValue(string);
private:
	char command;
	int position;
	string value;
};


#endif
