#include"Editor.h"
#include<fstream>
#include<iostream>
using namespace std;

void colorText(int value)
{

	COORD coord;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, value + 240);

}

void placeCursorAt(Point coordinate)
{
	COORD coord;
	coord.X = coordinate.getX();
	coord.Y = coordinate.getY();
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}

template<class ItemType>
int findIndexofLargest(const ItemType theArray[], int size)
{
	int indexSoFar = 0; // Index of largest entry found so far
	for (int currentIndex = 1; currentIndex < size; currentIndex++)
	{
		// At this point, theArray[indexSoFar] >= all entries in
		// theArray[0..currentIndex - 1]
		if (theArray[currentIndex] > theArray[indexSoFar])
			indexSoFar = currentIndex;
	} // end for
	return indexSoFar; // Index of largest entry
}


Editor::Editor()	//Constructor
{

}

Editor::Editor(string fileName)	
{
	LinkedList<string> tempArray;
	string keyword;
	lastLinePosition = 0;
	ifstream infile;
	infile.open(fileName);
	while (!infile.eof())	//Loops through file to grab each line in the file. Places the lines in aList.
	{
		lastLinePosition++;
		getline(infile, line);
		aList.insert(lastLinePosition, line);
	}
	infile.close();

	infile.open("keywords.txt");
	while (!infile.eof()) //Loops though keyword file to grab each keyword and place it in the Binary Search Tree
	{
		infile >> keyword;
		BST.add(keyword);
	}
}

void Editor::displayLines()
{
	system("CLS");
	// Displays each word and colors it blue if it is a keyword
	int position;
	string nextLine, nextWord, line;
	for (position = 1; position <= aList.getLength(); position++)
	{
		nextLine = aList.getEntry(position);

		int i = 0;
		while (i < nextLine.length())
		{
			string word = "";
			// isolate a word at a time (can contain underscores)
			if (isalpha(nextLine[i]))
			{
				while (isalpha(nextLine[i]) || nextLine[i] == '_')
				{
					word += nextLine[i];
					i++;
				}
				if (BST.contains(word))
				{
					colorText(1);
				}
				else
				{
					colorText(0);
				}
				cout << word;
			}

			else
			{
				colorText(0);
				cout << nextLine[i];
				i++;
			}
		}

		cout << endl;
	}
	placeCursorAt(aPoint);
} // end displayLines

void Editor::Run(string fileName)	//Gives the user the ability to manipulate the file.
{
	displayLines();
	string tempLine;
	const char QUIT = 'q';
	char command;
	char character;
	while ((command = _getwch()) != QUIT)	//Allows user to input key functions until they quit (q).
	{

		switch (command)
		{
		case 'h':   MoveLeft();
			break;
		case 'j':   MoveDown();
			break;
		case 'k':   MoveUp();
			break;
		case 'l':   MoveRight();
			break;
		case 'x':	Erase();
			break;
		case 'd':	DeleteLine();
			break;
		case 'u':	Undo();
			break;
		case ':':
		{
			//Set the cursor to the end of the editor
			aPoint.setX(aList.getEntry(lastLinePosition).length());
			aPoint.setY(aList.getLength() - 1);
			displayLines();
			char character = _getwch();
			//Saves the file if user presses w and quits the program without saving the file if the user presses q
			if (character == 'w')
			{
				saveFile(fileName);
			}
			else if (character == 'q')
			{
				return;
			}
		}
		break;
		default:
			break;
		}
		displayLines();
	}
	if (lastLinePosition == 0)
	{
		return;
	}
	else
	{
		//Set the cursor to the end of the text
		Point EditorEnd;
		EditorEnd.setX(aList.getEntry(lastLinePosition).length());
		EditorEnd.setY(aList.getLength() - 1);
		placeCursorAt(EditorEnd);
		return;
	}

}


void Editor::MoveRight()		//Moves the cursor to the right by one spot
{
	if (aList.getLength() == 0)
	{
		return;
	}
	if ((aList.getEntry(aPoint.getY() + 1).length() == aPoint.getX() + 1))
	{
		return;
	}
	aPoint.setX(aPoint.getX() + 1);
}

void Editor::MoveUp()			//Moves the cursor up one line
{
	if (aPoint.getY() == 0)
	{
		return;
	}
	if (aPoint.getX() > aList.getEntry(aPoint.getY()).length() - 1)
	{
		aPoint.setX(aList.getEntry(aPoint.getY()).length() - 1);
	}
	aPoint.setY(aPoint.getY() - 1);
}

void Editor::MoveDown()			//Moves the cursor down one line
{
	if (aPoint.getY() + 1 == lastLinePosition)
	{
		return;
	}
	if (lastLinePosition == 0)
	{
		return;
	}
	if (aPoint.getX() > aList.getEntry(aPoint.getY() + 2).length() - 1)
	{
		aPoint.setX(aList.getEntry(aPoint.getY() + 2).length() - 1);
	}
	aPoint.setY(aPoint.getY() + 1);
}

void Editor::MoveLeft()			//Moves the cursor to the left by one spot
{
	if (aPoint.getX() == 0)
	{
		return;
	}
	aPoint.setX(aPoint.getX() - 1);
}

void Editor::Erase()			//Deletes the character at the cursor
{
	if (lastLinePosition == 0)
	{
		return;
	}
	deleteCount++;
	string currentLine;
	currentLine = aList.getEntry(aPoint.getY() + 1);
	CommandPlus command;
	command.setValue(currentLine);
	command.setPosition(aPoint.getY() + 1);
	command.setCommand('x');
	aStack.push(command);

	currentLine.erase(aPoint.getX(), 1);
	aList.replace(aPoint.getY() + 1, currentLine);
}

void Editor::DeleteLine()		//Deletes the line the cursor is on if the user presses d again
{
	if (aList.isEmpty())
	{
		return;
	}
	char command = _getwch();
	if (command == 'd')
	{
		deleteCount++;
		string currentLine;
		currentLine = aList.getEntry(aPoint.getY() + 1);
		CommandPlus command;
		command.setValue(currentLine);
		command.setPosition(aPoint.getY() + 1);
		command.setCommand('d');
		aStack.push(command);
		displayLines();
		if (aPoint.getY() + 1 == aList.getLength())
		{
			aPoint.setY(aPoint.getY());
			aList.remove(aPoint.getY() + 1);
		}
		else
		{
			aList.remove(aPoint.getY() + 1);
		}
		aPoint.setX(0);
		lastLinePosition--;
	}
}

void Editor::Undo()				//Undo the previous change made
{
	if (!aStack.isEmpty())
	{
		CommandPlus command = aStack.peek();
		if (command.getCommand() == 'x')
		{
			aList.replace(command.getPosition(), command.getValue());
		}
		else if (command.getCommand() == 'd')
		{
			aList.insert(command.getPosition(), command.getValue());
			lastLinePosition++;
		}
		aStack.pop();
	}
}

void Editor::saveFile(string fileName)		//Saves the content that was changed into the textfile
{
	ofstream outFile;
	// open the file the user is working on as an output file
	outFile.open(fileName, ofstream::out);
	// write out all the lines from the linked list
	for (int i = 1; i <= aList.getLength(); i++) {
		outFile << aList.getEntry(i) << endl;
	}
	outFile.close();
}
