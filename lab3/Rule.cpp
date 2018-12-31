#include "Rule.h"

Rule::Rule(Predicate h) {
	head = h;

}
void Rule::addBodyPred(Predicate b) {
	bodyPredicates.push_back(b);
}
string Rule::toString() {
	string str;
	str = head.toString() + " :- ";
	str += bodyPredicates[0].toString();
	for (unsigned int i = 1; i < bodyPredicates.size(); i++) {
		str += "," + bodyPredicates[i].toString();
	}
	return str;
}
Rule::~Rule() {

}