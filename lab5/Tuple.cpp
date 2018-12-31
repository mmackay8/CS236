#include "Tuple.h"




string Tuple::toString(Header h) {
	string s;
	s += "  "+ h[0] + "=" + this->at(0);
	for (unsigned int i = 1; i < h.size(); i++) {
		s += ", " + h[i] + "=" + this->at(i);
	}
	s += "\n";
	return s;
}
bool Tuple::checkTuple(string s, int col) {
	if (s == this->at(col)) {
		return true;
	}
	else return false;
}
bool Tuple::checkTuple(int col1, int col2) {
	if (this->at(col1) == this->at(col2)) {
		return true;
	}
	else return false;
}
