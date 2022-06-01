#include"CommandPlus.h"

CommandPlus::CommandPlus()
{

}
//Setter for Command
void CommandPlus::setCommand(char Command)
{
	command = Command;
}
//Getter for Command
char CommandPlus::getCommand() const
{
	return command;
}
//Set start position
void CommandPlus::setPosition(int Position)
{
	position = Position;
}
//Get start position
int CommandPlus::getPosition() const
{
	return position;
}
//Get the line
string CommandPlus::getValue() const
{
	return value;
}
//Set the line value
void CommandPlus::setValue(string line)
{
	value = line;
}