#include "Token.h"
#include <string>
#include <iostream>
using namespace std;

Token::Token(TokenType t, string v, int lineNum) {
	type = t;
	value = v;
	lineNumber = lineNum;
}
Token::Token() {

}
int Token::getLineNumber() {
	return lineNumber;
}
TokenType Token::getType() {
	return type;
}
string Token::getValue() {
	return value;
}


void Token::setLineNumber(int lineNum) {
	lineNumber = lineNum;
}
void Token::setType(TokenType t) {
	type = t;

}
void Token::setValue(string v) {
	value = v;
}
string Token::tokenTypeToString()
{
	switch (type) {
	case(COMMA):
	{
		return "COMMA";
		break;
	}

	case(PERIOD):
	{
		return "PERIOD";
		break;
	}

	case(Q_MARK): {
		return "Q_MARK";
		break;
	}

	case(LEFT_PAREN): {
		return "LEFT_PAREN";
		break;
	}
	case(RIGHT_PAREN): {
		return "RIGHT_PAREN";
		break;
	}

	case(COLON): {
		return "COLON";
		break;
	}

	case(MULTIPLY): {
		return "MULTIPLY";
		break;
	}

	case(ADD): {
		return "ADD";
		break;
	}

	case(SCHEMES): {
		return "SCHEMES";
		break;
	}

	case(FACTS): {
		return "FACTS";
		break;
	}

	case(RULES): {
		return "RULES";
		break;
	}

	case(QUERIES): {
		return "QUERIES";
		break;
	}

	case(ID): {
		return "ID";
		break;
	}

	case(STRING): {
		return "STRING";
		break;
	}

	case(COMMENT): {
		return "COMMENT";
		break;
	}
	case(UNDEFINED): {
		return "UNDEFINED";
		break;
	}

	case(END): {
		return "EOF";
		break;
	}

	case(COLON_DASH): {
		return "COLON_DASH";
		break;
	}
	default: {
		return "BAD TOKEN";
		break;
	}

	}

}
void Token::toString() {
	cout << "(" + tokenTypeToString() + ",\"" + value + "\"," + to_string(lineNumber) + ")" << endl;
}
string Token::retString() {
	return "(" + tokenTypeToString() + ",\"" + value + "\"," + to_string(lineNumber) + ")";
}
Token::~Token() {

}