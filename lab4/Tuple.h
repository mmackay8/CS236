#pragma once
#include <vector>
#include "Header.h"
#include <string>
using namespace std;
class Tuple : public vector<string>
{
public:
	string toString(Header h);
	bool checkTuple(string s, int col);
	bool checkTuple(int col1, int col2);
};

