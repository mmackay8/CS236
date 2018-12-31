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
string Relation::getName() {
	return name;
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
	for (Tuple t : tuples) {
		r.addTuple(t);
	}
	r.addHeader(h);
	return r;
}
void Relation::addTuple(Tuple t) {
	tuples.insert(t);
}
Relation Relation::join(Relation r2) {
	Relation r(getName());
	r.addHeader(bothHeader(r2));
	if (tuples.size() != 0) {
		for (Tuple t1 : tuples) {
			for (Tuple t2 : r2.getTuples()) {
				if (checkJoin(t1, t2)) {///NEED TO FIXX
					r.addTuple(joinTuple(t1, t2));
				}
			}
		}
	}
	else {
		for (Tuple t : r2.getTuples()) {
			r.addTuple(t);
		}
		
	}

	return r;
}
string Relation::unite(Relation r2) {
	string s;
	for (Tuple t : r2.getTuples()) {
		if (tuples.count(t) == 0) {
			addTuple(t);
			s+= t.toString(header);
		}
	}
	return s;
}
Header Relation::bothHeader(Relation r2) {
	Header h = header;
	if (header.size() != 0) {
		for (unsigned j = 0; j < r2.getHeader().size(); j++) {
			if (checkItemHeader(h, r2.getHeader().at(j))) {//matching
				int i = getMapCols()[r2.getHeader().at(j)];
				matchCol.push_back(make_pair(i, j));
				excludes.push_back(j);
			}
			else {// not matching
				h.push_back(r2.getHeader().at(j));
				includes.push_back(j);
			}
		}
	}
	else h = r2.getHeader();
	return h;
}

bool Relation::checkItemHeader(Header h2, string s) {
		for (unsigned i = 0; i < h2.size(); i++) {
			if (h2.at(i) == s) {
				return true;
			}
		}
		return false;
}
bool Relation::checkJoin(Tuple t1, Tuple t2) {
	for (unsigned i = 0; i < matchCol.size(); i++) {
		if (t1.at(matchCol.at(i).first) == t2.at(matchCol.at(i).second)){
			continue;
		}
		else return false;
	}
	return true;
}
Tuple Relation::joinTuple(Tuple t1, Tuple t2) {
	Tuple t; 
	t = t1;
	for (unsigned j = 0; j < includes.size(); j++) {
		t.push_back(t2.at(includes.at(j)));
	}
	return t;
}
map<string,int> Relation::getMapCols() {
	map<string, int> colsNeeded;
	for (unsigned i = 0; i < header.size(); i++) {
		colsNeeded[header.at(i)] = i;
	}
	return colsNeeded;
}
Relation::~Relation()
{
}
