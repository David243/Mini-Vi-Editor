#ifndef EDITOR_
#define EDITOR_
#include"LinkedList.h"
#include"Point.h"
#include"windows.h"
#include"CommandPlus.h"
#include"LinkedStack.h"
#include"BinarySearchTree.h"

class Editor
{
private:
	LinkedList<string> aList;
	Point aPoint;
	string line;
	int lastLinePosition;
	LinkedStack<CommandPlus> aStack;
	int deleteCount = 0;
	BinarySearchTree<string> BST;
public:
	Editor();
	Editor(string);
	void displayLines();
	void Run(string);
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void Erase();
	void DeleteLine();
	void Undo();
	void saveFile(string);
};

#endif