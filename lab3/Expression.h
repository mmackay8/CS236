#pragma once
#include "Parameter.h"
#include <string>

using namespace std;
class Expression {
private:
	Parameter left;
	string oper;
	Parameter right;
public:
	Expression();
	string toString();
	~Expression();
	void setLeft(class Parameter l);
	void setRight(class Parameter r);
	void setOperator(string o);
	string returnExpression();

};