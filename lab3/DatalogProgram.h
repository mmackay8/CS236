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
	vector<Predicate> getSchemes();
	void addFact(Predicate fact);
	vector<Predicate> getFacts();
	void addRule(Rule r);
	vector<Rule> getRules();
	void addDomain(string d);
	set<string> getDomain();
	string toString();
	void addQuery(Predicate q);
	vector<Predicate> getQueries();

	~DatalogProgram();
private:
	vector <Predicate> listOfSchemes;
	vector <Predicate> listOfFacts;
	vector <Rule> listOfRules;
	vector <Predicate> listOfQueries;
	set <string> domain;

};