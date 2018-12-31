#include <fstream>
#include <string>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Interpreter.h"

using namespace std;

//int main(int argc, char *argv[])
int main(int argc, char *argv[]) {
	string fileName =  argv[1];
	Parser p(fileName);
	DatalogProgram dp;
	try {
		p.grammarCheck(dp);
	}
	catch (const std::exception& e) {
		cout << "Failure!" << endl << "  ";
		cout << e.what() << endl;
	}
	Interpreter i(dp);

	return 0;

}