#pragma once
#include<string>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate
{
public:
	Predicate(string newID);
	Predicate();
	void setID(string newID);
	string getID();
	void addParameter(Parameter param);
	vector<string> getParams();
	string toString();
	~Predicate();
private:
	string ID;
	vector <Parameter> listOfParams;
};

