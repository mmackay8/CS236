#include <fstream>
#include <string>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"

using namespace std;

//int main(int argc, char *argv[])
int main(int argc, char *argv[]) {
	string fileName = argv[1];
	Parser p(fileName);
	try {
		p.grammarCheck();
	}
	catch(const std::exception& e){
		cout << "Failure!"<<endl<< "  ";
		cout << e.what()<<endl;
	}


	return 0;

}