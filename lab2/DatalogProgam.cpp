#include "DatalogProgam.h"

using namespace std;

DatalogProgram::DatalogProgram() {
}
void DatalogProgram::addScheme(Predicate scheme) {
	listOfSchemes.push_back(scheme);
}
void DatalogProgram::addFact(Predicate fact) {
	listOfFacts.push_back(fact);
}
void DatalogProgram::addRule(Rule r) {
	listOfRules.push_back(r);
}
void DatalogProgram::addQuery(Predicate q) {
	listOfQueries.push_back(q);
}
void DatalogProgram::addDomain(string d) {
	domain.insert(d);
}
string DatalogProgram::toString() {
	string str;
	str = "Schemes(" + to_string(listOfSchemes.size()) + "):\n";
	for (unsigned int i = 0; i < listOfSchemes.size(); i++) {
		str+="  " + listOfSchemes[i].toString()+ "\n";
	}
	str += "Facts(" + to_string(listOfFacts.size()) + "):\n";
	for (unsigned int i = 0; i < listOfFacts.size(); i++) {
		str += "  " +listOfFacts[i].toString()+".\n";
	}
	str += "Rules(" + to_string(listOfRules.size()) + "):\n";
	for (unsigned int i = 0; i < listOfRules.size(); i++) {
		str += "  " + listOfRules[i].toString()+".\n";
	}
	str += "Queries(" + to_string(listOfQueries.size()) + "):\n";
	for (unsigned int i = 0; i < listOfQueries.size(); i++) {
		str += "  " + listOfQueries[i].toString()+"?\n";
	}
	str += "Domain("+ to_string(domain.size())+"):\n";
	for (auto iter = begin(domain); iter != end(domain); ++iter){
		str += "  " + *iter+"\n";
	}
	return str;
}
DatalogProgram::~DatalogProgram() {

}