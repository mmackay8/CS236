#pragma once
#include <map>
#include <string>
#include "Relation.h"
using namespace std;
class Database : public map<string, Relation>
{
public:
	Database();
	int countTuple();
	~Database();
};

