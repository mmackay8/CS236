#include "Interpreter.h"
#include <iostream>



Interpreter::Interpreter(DatalogProgram dp)
{
	datap = dp;
	makeRelations();
	addTuples();
	checkQueries();
}
void Interpreter::makeRelations() {
	for (unsigned i = 0; i < datap.getSchemes().size(); i++) {
		string name = datap.getSchemes().at(i).getID();
		Header header;
		for (unsigned j = 0; j < datap.getSchemes().at(i).getParams().size(); j++) {
			header.push_back(datap.getSchemes().at(i).getParams().at(j));
		}
		Relation r(name, header);
		datab[name] =r;
	}
	
}
void Interpreter::addTuples() {
	for (unsigned i = 0; i < datap.getFacts().size(); i++) {
		string name = datap.getFacts().at(i).getID();
		Tuple t;
		for (unsigned j = 0; j < datap.getFacts().at(i).getParams().size(); j++) {
			t.push_back(datap.getFacts().at(i).getParams().at(j));
		}

		datab[name].addTuple(t);
	}
}
void Interpreter::checkQueries() {
	Relation r;
	for (unsigned i = 0; i < datap.getQueries().size(); i++) {
		Header newHeader;
		vector<int> colNums;
		map<string, int> first;
		string name = datap.getQueries().at(i).getID();
		r = datab[name];
		cout << datap.getQueries().at(i).toString()<< "?";
		for (unsigned j = 0; j < datap.getQueries().at(i).getParams().size(); j++) {
			string s = datap.getQueries().at(i).getParams().at(j);
			if (s[0] == '\'') {//this element is a string
				r = r.select(j, datap.getQueries().at(i).getParams().at(j));
			}
			else {//this element is NOT a string
				if (first.count(datap.getQueries().at(i).getParams().at(j)) == 0) {
					//this string has not been seen yet
					//add the string and column number to first map
					first[s] = j;
					colNums.push_back(j);
					newHeader.push_back(s);
				}
				else {
					r = r.select(j, first[s]);
				}
			}
		}
		r = r.project(colNums);
		r.rename(newHeader);
		if (r.getTuples().size() == 0) {
			cout << " No" << endl;
		}
		else {
			cout << " Yes(" + to_string(r.getTuples().size()) + ")" << endl;
			if (newHeader.size() != 0) {
				print(r, newHeader);
			}
		}
	}
	

}
void Interpreter::print(Relation r, Header newH) {
	string s = "";
	for (Tuple t : r.getTuples()) {
		s += t.toString(newH);
	}
	cout << s;

}
Interpreter::~Interpreter() {

}