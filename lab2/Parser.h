#pragma once
#include "Scanner.h"
#include "Predicate.h"
#include "Rule.h"
#include <string>
#include <iostream>
#include <vector>



using namespace std;

class Parser
{
public:
	Parser(string fileName);

	void grammarCheck();
	void checkScheme(class DatalogProgram& datap);
	void checkFacts(class DatalogProgram& datap);
	void checkRules(class DatalogProgram& datap);
	void checkQueries(class DatalogProgram& datap);
	class Predicate headPredicate();
	void stringList(class Predicate& pred, class DatalogProgram& datap);
	void idList(class Predicate& pred);
	void schemeList(class DatalogProgram& datap);
	void parameterList(class Predicate& pred);
	void predicateList();
	void factList(class DatalogProgram& datap);
	class Predicate fact(class DatalogProgram& datap);
	void scheme(class DatalogProgram& datap);
	void query(class DatalogProgram& datap);
	void queryList(class DatalogProgram& datap);
	void ruleList(class DatalogProgram& datap);
	class Predicate predicate();
	class Parameter parameter(class Predicate& pred);
	void predicateList2(class Rule& ru);
	class Predicate predicate2(class Rule& ru);
	string expression(class Predicate& pred);
	class Rule rule(class DatalogProgram& datap);
	string operate();

	~Parser();
private:
	vector<Token> allTokens;


	int pos;

};

