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
	void addParameter(Parameter param);
	string toString();
	~Predicate();
private:
	string ID;
	vector <Parameter> listOfParams;
};

