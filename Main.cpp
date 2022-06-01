/*
This program is called the "Mini VI". Its purpose is to allow its user to manipulate a file and save the changes.
The program is able to highlight words that are contained in the file that are also 'Keywords'
using the Binary Search Tree Data Structure.
*/
#include <iostream>
#include <string>
#include <fstream>
#include"Editor.h"
using namespace std;

void main(int argc, char** argv)
{
	ifstream infile;
	//To choose the text file on visual Studios: 
	//Go to Project tab -> Properties -> Debugging -> Command Arguments -> Change the text file to the one you want to use.
	//Remember to include it in the project
	Editor miniVi(argv[1]); //Opens the file
	miniVi.Run(argv[1]); //Give the user the ability to manipulate the file via console
}