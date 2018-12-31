#include "Predicate.h"



Predicate::Predicate(string newID)
{
	ID = newID;
}
Predicate::Predicate() {

}
void Predicate::addParameter(Parameter param) {
	listOfParams.push_back(param);
}
void Predicate::setID(string newID) {
	ID = newID;
}
string Predicate::getID() {
	return ID;
}
string Predicate::toString() {
	string str;
	str = ID + "(";
	str += listOfParams[0].toString();
	for (unsigned int i = 1; i < listOfParams.size(); i++) {
		str += "," + listOfParams[i].toString();
	}
	str += ")";
	return str;

}
vector<string> Predicate::getParams() {
	vector<string> stringParams;
	for (unsigned i = 0; i < listOfParams.size(); i++) {
		stringParams.push_back(listOfParams[i].toString());
	}
	return stringParams;
}
Predicate::~Predicate()
{
}
