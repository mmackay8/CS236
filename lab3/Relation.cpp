#include "Relation.h"



Relation::Relation(string n, Header h)
{
	name = n;
	header = h;
}
Relation::Relation(string n) {
	name = n;
}
Relation::Relation() {

}
void Relation::addHeader(Header h) {
	header = h;
}
Relation Relation::select(int col1, int col2) {
	Relation r(name, header);
	for (Tuple t : tuples) {
		if (t.checkTuple(col1, col2)) {
			r.addTuple(t);
		}
	}
	return r;
}
set<Tuple> Relation::getTuples() {
	return tuples;
}
Header Relation::getHeader() {
	return header;
}
Relation Relation::select(int col, string s) {
	Relation r(name, header);
	for (Tuple t : tuples) {
		if (t.checkTuple(s, col)) {
			r.addTuple(t);
		}
	}
	return r;
}
Relation Relation::project(vector<int> cols) {
	Relation r(name);
	Header h;
	for (unsigned int i = 0; i < cols.size(); i++) {
		h.push_back(header[cols[i]]);
	}
	r.addHeader(h);
	vector<string> tempttuple;
	for (auto t : tuples) { // this has t having size 0
		Tuple newTup;//Make new tuples with the right orders
		for (unsigned int i = 0; i < cols.size(); i++) {
			newTup.push_back(t[cols[i]]);
		}
		r.addTuple(newTup);//add new tuple to new relation
	}
	return r;
}
Relation Relation::rename(vector<string> newHeader) {
	Relation r(name);
	Header h;
	for (unsigned int i = 0; i < newHeader.size(); i++) {
		h.push_back(newHeader[i]);
	}
	r.addHeader(h);
	return r;
}
void Relation::addTuple(Tuple t) {
	tuples.insert(t);
}


Relation::~Relation()
{
}
