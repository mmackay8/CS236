#pragma once
#include "Header.h"
#include "Tuple.h"
#include <set>


class Relation
{
public:
	Relation(string n, Header h);
	Relation(string n);
	Relation();
	void addTuple(Tuple t);
	set<Tuple> getTuples();
	Header getHeader();
	void addHeader(Header h);
	Relation select(int col1, int col2);
	Relation select(int col, string s);
	Relation project(vector<int> cols);
	Relation rename(vector<string> newHeader);
	~Relation();
private:
	string name;
	Header header;
	set<Tuple> tuples;
};

