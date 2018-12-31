#pragma once
#include <iostream>
#include <iterator>
#include <set>
using namespace std;
class node
{
private:
	int postOrder;
	set<int> n;
	bool visited;
	string ID;
	int numID;
	bool dependsOnSelf;

public:
	node(string newID, int numberID);
	node();
	string getID();
	int getNumID();
	void setVisited();
	set<int> getN();
	void addN(int i);
	bool getVisited();
	void printNs();
	void setPostOrder(int i);
	int getPostOrder();
	void setDepends();
	bool getDepends();
	~node();
};

