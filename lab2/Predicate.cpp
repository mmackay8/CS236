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
string Predicate::toString() {
	string str;
	str = ID + "(";
	str+= listOfParams[0].toString();
	for (unsigned int i = 1; i < listOfParams.size(); i++) {
		str +=","+ listOfParams[i].toString();
	}
	str += ")";
	return str;
	 
}
Predicate::~Predicate()
{
}
