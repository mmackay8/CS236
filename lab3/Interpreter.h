#pragma once
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter
{
public:
	Interpreter(DatalogProgram dp);
	void makeRelations();
	void addTuples();
	void checkQueries();
	void print(Relation r, Header newH);
	~Interpreter();
private:
	DatalogProgram datap;
	Database datab;
};

