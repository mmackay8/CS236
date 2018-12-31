#include "Interpreter.h"
#include <iostream>
#include <iterator>
#include "graph.h"



Interpreter::Interpreter(DatalogProgram dp)
{
	datap = dp;
	makeRelations();
	addTuples();
	evaluateInOrder(makeGraph());
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
		datab[name] = r;
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
vector<int> Interpreter::getHeadCols(Predicate p, Relation r) {
	vector<int> headCols;
	map<string, int> mapForCols = r.getMapCols();
	for (unsigned i = 0; i < p.getParams().size(); i++) {
		headCols.push_back(mapForCols[p.getParams().at(i)]);
	}
	return headCols;
}
graph Interpreter::makeGraph() {
	graph g;
	for (unsigned i = 0; i < datap.getRules().size(); i++) {
		node n(datap.getRules().at(i).getHead().getID(), i);
		g[i] = n;
	}
	for (unsigned j = 0; j < datap.getRules().size(); j++) {
		for (unsigned k = 0; k < datap.getRules().at(j).getBody().size(); k++) {
			string nameID = datap.getRules().at(j).getHead().getID();
			string predID = datap.getRules().at(j).getBody().at(k).getID();
			for (std::map<int, node>::iterator it = g.begin(); it != g.end(); ++it) {
				string ruleID = it->second.getID();
				if (ruleID == predID) {
					g[j].addN(it->first);
					if (j == (unsigned)it->first) {
						g[j].setDepends();
					}
				}

			}
		}
	}
	g.printGraph();
	if (g.size() != 0) {
		graph revG = g.reverse();
		revG.makeVector();
		revG.dfsForrest(revG[0]);
		g.makeVector();
		g.setPostOrderList(revG.getPostOrderList());
		g.dfsForrest2(g[revG.getHighest().getNumID()]);
		order = g.getOrder();
	}
	return g;
}
string Interpreter::makeSCCheader(int i) {
	string s = "R";
	set<int>::iterator it = order[i].begin();
	s += to_string(*it);
	it++;
	for (set<int>::iterator myIt = it; myIt != order[i].end(); ++myIt){
		s += ",R" + to_string(*myIt);
	}
	return s;
}
void Interpreter::oneRule(int i) {
	Relation r;
	set<int>::iterator it = order[i].begin();
	cout << datap.getRules().at(*it).toString();//EVALUATE at the element in order!!
	Predicate head = datap.getRules().at(*it).getHead();
	vector<string> headHeader = datap.getRules().at(*it).getHead().getParams();
	Relation newR(head.getID());
	for (unsigned k = 0; k < datap.getRules().at(*it).getBody().size(); k++) {
		r = eval(datap.getRules().at(*it).getBody().at(k));
		newR = newR.join(r);//What does newR have in it?
	}
	newR = newR.project(getHeadCols(head, newR));// the new cols in the head predicate					
	newR.rename(headHeader);
	cout << datab[head.getID()].unite(newR);
	//cout << "1 passes: R" <<order[i][0]<< endl;

}
int Interpreter::multiplePasses(int i) {
	int post = -1;
	int passes = 0;
	int precount = 0;
	precount = datab.countTuple();
	while (precount != post) {
		precount = datab.countTuple();
		for (set<int>::iterator it = order[i].begin(); it != order[i].end(); ++it){
			cout << datap.getRules().at(*it).toString();
			Relation r;
			//EVALUATE at the element in order!!
			Predicate head = datap.getRules().at(*it).getHead();
			vector<string> headHeader = datap.getRules().at(*it).getHead().getParams();
			Relation newR(head.getID());
			for (unsigned k = 0; k < datap.getRules().at(*it).getBody().size(); k++) {
				r = eval(datap.getRules().at(*it).getBody().at(k));
				newR = newR.join(r);//What does newR have in it?
			}
			newR = newR.project(getHeadCols(head, newR));// the new cols in the head predicate					
			newR.rename(headHeader);
			cout << datab[head.getID()].unite(newR);
		}
		passes++;
		post = datab.countTuple();
	}
	return passes;
}
void Interpreter::evaluateInOrder(graph g) {
	//string scc; 
	int passes;
	cout << "Rule Evaluation\n";
	
	for (unsigned i = 0; i < order.size(); i++) {
		cout <<"SCC: "<< makeSCCheader(i) << endl;
		set<int> ::iterator it = order[i].begin();
		if(order[i].size() ==1 && !g[*it].getDepends()){ // THIS returns that the values are not neighbors therefore the rule should be evaluated once
			//if (!g.isNeighbor(i)) {//I need to fix this condition //|| g.at(i).getN().size()<2
				oneRule(i);
				passes = 1;
			}
			else {
				passes = multiplePasses(i);
				
			}
			
/*			int post = -1;
			int passes = 0;
			int precount = 0;
			precount = datab.countTuple();
			while (precount != post) {
				passes++;
				precount = datab.countTuple();
				Relation r;
				cout << datap.getRules().at(order[i][j]).toString();//EVALUATE at the element in order!!
				Predicate head = datap.getRules().at(order[i][j]).getHead();
				vector<string> headHeader = datap.getRules().at(order[i][j]).getHead().getParams();
				Relation newR(head.getID());
				for (unsigned k = 0; k < datap.getRules().at(order[i][j]).getBody().size(); k++) {
					r = eval(datap.getRules().at(order[i][j]).getBody().at(k));
					newR = newR.join(r);//What does newR have in it?
				}
				newR = newR.project(getHeadCols(head, newR));// the new cols in the head predicate					
				newR.rename(headHeader);
				cout << datab[head.getID()].unite(newR);
				post = datab.countTuple();
			}
			cout << passes<<" passes: R" <<endl;*/
		
		cout << passes << " passes: " << makeSCCheader(i) << endl;
	}
}


void Interpreter::evaluateRules() {
	int post = -1; 
	int passes = 0;
	int precount = 0;
	precount = datab.countTuple();
	cout << "Rule Evaluation\n";
	while (precount != post) {
		passes++;
		precount = datab.countTuple();
		for (unsigned i = 0; i < datap.getRules().size(); i++) {
			Relation r;
			cout << datap.getRules().at(i).toString();
			Predicate head = datap.getRules().at(i).getHead();
			vector<string> headHeader = datap.getRules().at(i).getHead().getParams();
			Relation newR(head.getID());
			for (unsigned j = 0; j < datap.getRules().at(i).getBody().size(); j++) {
				
				r = eval(datap.getRules().at(i).getBody().at(j));
				newR = newR.join(r);//What does newR have in it?
			}
			newR = newR.project(getHeadCols(head, newR));// the new cols in the head predicate
			newR.rename(headHeader);
			cout << datab[head.getID()].unite(newR);
		}
		post = datab.countTuple();
	}
	cout << endl << "Schemes populated after " << passes << " passes through the Rules." << endl<<endl;

	

}
Relation Interpreter::eval(Predicate p) {
	Relation r;
	Header newHeader;
	vector<int> colNums;
	map<string, int> first;
	string name = p.getID();
	r = datab[name];
	for (unsigned j = 0; j < p.getParams().size(); j++) {
		string s = p.getParams().at(j);
		if (s[0] == '\'') {//this element is a string
			r = r.select(j, p.getParams().at(j));
		}
		else {//this element is NOT a string
			if (first.count(p.getParams().at(j)) == 0) {
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
	r = r.rename(newHeader);
	return r;
}

void Interpreter::checkQueries() {
	cout << "\nQuery Evaluation\n";
	for (unsigned i = 0; i < datap.getQueries().size(); i++){
		Relation r= eval(datap.getQueries().at(i));
		//print it out
		cout<< datap.getQueries().at(i).toString()<< "?" ;
		if (r.getTuples().size() == 0) {
			cout << " No" << endl;
		}
		else {
			cout << " Yes(" + to_string(r.getTuples().size()) + ")" << endl;
			if (r.getHeader().size() != 0) {
				print(r);
			}
		}
	}


}
void Interpreter::print(Relation r) {
	string s = "";
	for (Tuple t : r.getTuples()) {
		s += t.toString(r.getHeader());
	}
	cout << s;

}
Interpreter::~Interpreter() {

}