#include "node.h"



node::node(string newID, int numberID)
{
	ID = newID;
	visited = false;
	numID = numberID;
	dependsOnSelf = false;
}
void node::setDepends() {
	dependsOnSelf = true;
}
bool node::getDepends() {
	return dependsOnSelf;
}
node::node() {

}
int node::getNumID() {
	return numID;
}
string node::getID() {
	return ID;
}
void node::setVisited() {
	visited = true;
}
bool node::getVisited() {
	return visited;
}
void node::addN(int i) {
	n.insert(i);
}
void node::printNs() {
	if (n.size() > 0) {
		set<int>::iterator it;
		it = n.begin();
		if (n.size() == 1) {
			cout << "R" << *it;
		}
		else {
			cout << "R" << *it;
			it++;
			for (set<int>::iterator newIt = it; newIt != n.end(); newIt++) {
				cout << "," << "R" << *newIt;
			}
		}
	}
}
set<int> node::getN() {
	return n;
}
void node::setPostOrder(int i) {
	postOrder = i;
}
int node::getPostOrder() {
	return postOrder;
}
node::~node()
{
}
