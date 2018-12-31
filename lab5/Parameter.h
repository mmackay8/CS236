#pragma once
#include <string>
using namespace std;

class Parameter {
private:
	string param;
public:
	Parameter(string p);
	Parameter();
	string toString();
	~Parameter();
};