#include <fstream>
#include <string>
#include <iostream>
#include "Scanner.h"

using namespace std;

//int main(int argc, char *argv[])
int main(int argc, char *argv[]) {
	string fileName = argv[1];
	string line;

	LexicalParser lexi;
	lexi.openFile(fileName);
	lexi.toString();
	cout << "Total Tokens = " << lexi.totalTokens() << endl;
	return 0;
}