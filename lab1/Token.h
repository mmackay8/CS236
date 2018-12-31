#pragma once
#include <string>

using namespace std;
enum TokenType {
	COMMA, PERIOD, COLON_DASH, COLON, Q_MARK, MULTIPLY,
	ADD, SCHEMES, FACTS, RULES, QUERIES, STRING, COMMENT, END, UNDEFINED,
	LEFT_PAREN, RIGHT_PAREN, ID
};

class Token {
private:
	int lineNumber;
	TokenType type;
	string value;
public:
	int getLineNumber();
	TokenType getType();
	string getValue();
	Token(TokenType type, string value, int lineNumber);
	~Token();
	void setLineNumber(int lineNum);
	void setType(TokenType t);
	void setValue(string v);
	string tokenTypeToString();
	void toString();
};