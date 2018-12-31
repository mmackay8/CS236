#include "graph.h"
#include <stack>
#include <algorithm>



graph::graph()
{
	count = 0;
}
void graph::setPostOrderList(vector<int> v) {
	postOrder = v;
}
vector<int> graph::getPostOrderList() {
	return postOrder;
}
bool graph::notNeighbor(int i) {
	set<int>::iterator it = order.at(i).begin();
		for (set<int>::iterator sIt = it; sIt != order.at(i).end(); ++sIt) {
			if (i == *sIt) {
				return false;
			}
		}
		return true;
}
graph graph::reverse() {
	
	graph g;
	for (std::map<int, node>::iterator it = this->begin(); it != this->end(); ++it) {
		node n(it->second.getID(), it->first);
		g[it->first] = n;
	}
	for (std::map<int, node>::iterator it = this->begin(); it != this->end(); ++it) {
		for (int i : it->second.getN()) {
				g[i].addN(it->first);
		}
	}
	return g;
}
node graph::getHighest() {
	return highestPostOrder;
}

void graph::dfs(node& curr) {
	curr.setVisited();
	for (int n: curr.getN()) {
		if (this->at(n).getVisited() == true) {
			continue;
		}
		else { // This node has not been visited yet
			dfs(this->at(n));
		}
	}
}
void graph::makeVector() {
	for (unsigned i = 0; i < this->size(); i++) {
		graphNodes.insert(i);
	}
}
void graph::dfsForrest(node& curr) {
	dfsRec(curr);
	set<int>::iterator it = graphNodes.begin();
	if (it != graphNodes.end()) {
		dfsForrest(this->at(*it));
	}
}
void graph::dfsRec(node& curr) {
	curr.setVisited();
	graphNodes.erase(graphNodes.find(curr.getNumID()));
	
	for (int n : curr.getN()) {
		if (this->at(n).getVisited() == false) {
			dfsRec(this->at(n));
		}
	}
	count++;
	curr.setPostOrder(count);
	vector<int>::iterator vectorIt = postOrder.begin();
	postOrder.insert(vectorIt, curr.getNumID()); // This puts the new elements at the beginning of the vector keeping it as postOrder
	highestPostOrder = curr;
}
vector<set<int>> graph::getOrder() {
	return order;
}
void graph::dfsForrest2(node& curr) {
	dfsRec2(curr);
	if (!temp.empty()) {
		order.push_back(temp);
	}
	vector<int> ::iterator it = postOrder.begin();
	if (it != postOrder.end()) {
		temp.clear();
		dfsForrest2(this->at(*it));//Go to the next node that has visit 
	}
}
void graph::removeElement(int i) {
	auto it = std::find(postOrder.begin(), postOrder.end(), i);
	if (it != postOrder.end())
		postOrder.erase(it);
}
void graph::dfsRec2(node& curr) {
		curr.setVisited();
		if (postOrder[0] == curr.getNumID()) {
			postOrder.erase(postOrder.begin());
		}
		else removeElement(curr.getNumID());
		temp.insert(curr.getNumID());
		for (int n : curr.getN()) { // this goes through all the neighbors 
			if (!this->at(n).getVisited()) {//This node has not been visited yet
				dfsRec2(this->at(n));
			}
		}
}
void graph::printGraph() {
	cout << "Dependency Graph\n";
	for (std::map<int, node>::iterator it = this->begin(); it != this->end(); ++it) {
		std::cout << "R" <<std::to_string(it->first) << ":";
		it->second.printNs();
		cout << endl;
	}
	cout << endl;
}
graph::~graph()
{
}
