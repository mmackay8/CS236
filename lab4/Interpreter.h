#pragma once
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter
{
public:
	Interpreter(DatalogProgram dp);
	void makeRelations();
	void addTuples();
	void evaluateRules();
	void checkQueries();
	Relation eval(Predicate p);
	vector<int> getHeadCols(Predicate p, Relation r);
	void print(Relation r);
	~Interpreter();
private:
	DatalogProgram datap;
	Database datab;
	
};

