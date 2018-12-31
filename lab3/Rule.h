#pragma once
#include "Predicate.h"
#include <vector>
using namespace std;
class Rule {
private:
	Predicate head;
	vector<Predicate> bodyPredicates;
public:
	Rule(Predicate h);
	void addBodyPred(Predicate b);
	string toString();
	~Rule();
};