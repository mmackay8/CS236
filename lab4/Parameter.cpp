#include "Parameter.h"


Parameter::Parameter(string p) {
	param = p;
}
Parameter::Parameter() {

}
Parameter::~Parameter() {

}
string Parameter::toString() {
	return param;
}