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
	class graph makeGraph();
	vector<int> getHeadCols(Predicate p, Relation r);
	string makeSCCheader(int i);
	void print(Relation r);
	void evaluateInOrder(graph g);
	void oneRule(int i);
	int multiplePasses(int i);
	~Interpreter();
private:
	DatalogProgram datap;
	Database datab;
	vector<set<int>> order;
};

