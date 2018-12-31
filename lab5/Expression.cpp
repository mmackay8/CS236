#include "Expression.h"

Expression::Expression() {

}
void Expression::setLeft(Parameter l) {
	left = l;
}
void Expression::setRight(Parameter r) {
	right = r;
}
void Expression::setOperator(string o) {
	oper = o;
}
string Expression::returnExpression() {
	string str;
	str = "(" + left.toString() + oper + right.toString() + ")";
	return str;
}
string Expression::toString() {
	return "";
}
Expression::~Expression() {

}
