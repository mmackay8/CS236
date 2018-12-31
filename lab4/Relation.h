#pragma once
#include "Header.h"
#include "Tuple.h"
#include <set>
#include <map>


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
	Relation join(Relation r2);
	string unite(Relation r2);
	Header bothHeader(Relation r2);
	bool checkJoin(Tuple t1, Tuple t2);
	Tuple joinTuple(Tuple t1, Tuple t2);
	map<string, int> getMapCols();
	string getName();
	bool checkItemHeader(Header h2, string s);
	~Relation();
private:
	string name;
	Header header;
	set<Tuple> tuples;
	vector<pair<int, int>> matchCol;
	vector<int> excludes;
	vector<int> includes;
	//map<string, int> mapHeader;
};

