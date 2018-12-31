#pragma once
#include "Token.h"
#include <vector>

using namespace std;

enum States {
	start, colon, letter, id,
	strings, keyword, comment, commentEnd, notBlockComment,
	blockComment, undefined, endState, endstrings
};


class LexicalParser
{
private:
	States currState;
	vector<Token> tokenList;
	string temp;
	int lineNumber;
	int lineCount;
	int addLine;

public:
	
	LexicalParser();
	void colonCase(char c);
	void stringCase(char c);
	void commentEndCase(char c);
	void notBlockCommentCase(char c);
	void endStringsCase(char c);
	void commentCase(char c);
	void blockCommentCase(char c);
	void idCase(char c);
	void setLineCount();
	void parseChar(char c);
	void openFile(string fileName);
	void toString();
	void endOfFile();
	int totalTokens();
	//int addToLineNumber();


	~LexicalParser();
};

