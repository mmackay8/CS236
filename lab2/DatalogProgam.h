#pragma once
#include <vector>
#include <set>
#include "Rule.h"
#include "Predicate.h"

using namespace std;

class DatalogProgram {
public:
	DatalogProgram();
	void addScheme(Predicate scheme);
	void addFact(Predicate fact);
	void addRule(Rule r);
	void addDomain(string d);
	string toString();
	void addQuery(Predicate q);

	~DatalogProgram();
private:
	vector <Predicate> listOfSchemes;
	vector <Predicate> listOfFacts;
	vector <Rule> listOfRules;
	vector <Predicate> listOfQueries;
	set <string> domain;
	
};