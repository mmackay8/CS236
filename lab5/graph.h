#pragma once
#include "node.h"
#include <map>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
using namespace std;
class graph : public map<int, node>
{
public:
	graph();
	void printGraph();
	bool notNeighbor(int i);
	void setPostOrderList(vector<int> v);
	vector<int> getPostOrderList();
	void makeVector();
	graph reverse();
	void dfs(node& curr);
	void dfsForrest(node& curr);
	void dfsRec(node& curr);
	vector<set<int>> getOrder();
	void dfsForrest2(node& curr);
	void dfsRec2(node& curr);
	void removeElement(int i);
	node getHighest();
	~graph();
private:
	set<int> temp;
	set<int> graphNodes;
	vector<int> postOrder;
	vector<set<int>> order;
	int count;
	node highestPostOrder;
//	stack<int> dfsStack;
};

