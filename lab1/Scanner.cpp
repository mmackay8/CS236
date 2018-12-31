#include "Scanner.h"
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

LexicalParser::LexicalParser()
{
	currState = start;
	temp = "";
	lineNumber = 1;
	addLine = 0;
	
}
void LexicalParser::idCase(char c) {
	if (isalnum(c)) {
		temp += c;
		currState = id;
	}
	else {
		if (temp == "Schemes") {
			tokenList.push_back(Token(SCHEMES, "Schemes", lineNumber));
			currState = start;
		}
		else if (temp == "Rules") {
			tokenList.push_back(Token(RULES, "Rules", lineNumber));
			currState = start;
		}
		else if (temp == "Facts") {
			tokenList.push_back(Token(FACTS, "Facts", lineNumber));
			currState = start;
		}
		else if (temp == "Queries") {
			tokenList.push_back(Token(QUERIES, "Queries", lineNumber));
			currState = start;
		}
		else {
			tokenList.push_back(Token(ID, temp, lineNumber));
			currState = start;
		}
		parseChar(c);
	}
}
void LexicalParser::colonCase(char c) {
	if (c == '-') {
		temp += c;
		tokenList.push_back(Token(COLON_DASH, temp, lineNumber));
	}
	else {
		tokenList.push_back(Token(COLON, temp, lineNumber));
		parseChar(c);
	}
}
void LexicalParser::stringCase(char c) {
	if (c == '\'') {
		temp += c;
		currState = endstrings;
	}
	else if (c == EOF) {
		tokenList.push_back(Token(UNDEFINED, temp, lineNumber));
		lineNumber += addLine;
		endOfFile();
		currState = start;
	}
	else if (c == '\n') {
		temp += c;
		addLine++;
		//lineNumber++;
	}
	else {
		temp += c;
		currState = strings;
	}
}
void LexicalParser::notBlockCommentCase(char c) {
	if (c == '\n') {
		currState = start;
		tokenList.push_back(Token(COMMENT, temp, lineNumber));
		lineNumber++;
	}
	else if (c == EOF) {
		tokenList.push_back(Token(COMMENT, temp, lineNumber));
		endOfFile();
		currState = start;
	}
	else {
		temp += c;
		currState = notBlockComment;
	}
}
void LexicalParser::commentEndCase(char c){
		if (c == '#') {
			temp+= c;
			tokenList.push_back(Token(COMMENT, temp, lineNumber));
			lineNumber += addLine;
			currState = start;
		}
		else if(c== EOF){
			tokenList.push_back(Token(UNDEFINED, temp, lineNumber));
			lineNumber += addLine;
			endOfFile();
			currState = start;

		}
		else if (c == '\n'){
			temp+= c;
			currState = blockComment;
			addLine++;
		}

		else if(c== '|'){
			temp += c;
			currState = commentEnd;
		}
		else{
			temp += c;
			currState = blockComment;
		}


}
void LexicalParser::endStringsCase(char c) {
	if (c == '\'') {
		temp += c;
		currState = strings;
	}
	else {
		tokenList.push_back(Token(STRING, temp, lineNumber));
		lineNumber += addLine;
		currState = start;
		parseChar(c);
	}
}
void LexicalParser::blockCommentCase(char c) {
	if (c == '|') {
		temp += c;
		currState = commentEnd;
	}
	else if (c == '\n') {
		temp += c;
		currState = blockComment;
		addLine++;
	}
	else if (c == EOF) {
		tokenList.push_back(Token(UNDEFINED, temp, lineNumber));
		lineNumber += addLine;
		endOfFile();
		currState = start;
	}
	else {
		temp += c;
		currState = blockComment;
	}
}
void LexicalParser::commentCase(char c) {
	if (c == '|') {
		temp += c;
		addLine = 0;
		currState = blockComment;

	}
	else{
	       temp+= c;	
		currState = notBlockComment;
	}
}

void LexicalParser::parseChar(char c)
{
	switch (currState) {
	case(start):
		//do something
		switch (c) {
		case(','):
			tokenList.push_back(Token(COMMA, ",", lineNumber));
			break;
		case('.'):
			tokenList.push_back(Token(PERIOD, ".", lineNumber));
			break;
		case ('('):
			tokenList.push_back(Token(LEFT_PAREN, "(", lineNumber));
			break;
		case (')'):
			tokenList.push_back(Token(RIGHT_PAREN, ")", lineNumber));
			break;
		case ('?'):
			tokenList.push_back(Token(Q_MARK, "?", lineNumber));
			break;
		case ('*'):
			tokenList.push_back(Token(MULTIPLY, "*", lineNumber));
			break;
		case ('+'):
			tokenList.push_back(Token(ADD, "+", lineNumber));
			break;
		case ('#'):
			temp = c;
			currState = comment;
			addLine = 0;
			break;
		case ('\''):
			temp = c;
			currState = strings;
			addLine = 0;
			break;
		case (':'):
			temp = c;
			currState = colon;
			break;
		case (EOF):
			endOfFile();
			break;
		case ('\n'):
			lineNumber++;
			break;
		default:
			if (isalnum(c)) {
				temp = c;
				if (isdigit(c)) {
					currState = undefined;
				}
				else {
					currState = id;
				}
			}
			else if (isspace(c)) {
				currState = start;
			}
			else {
				temp = c;
				tokenList.push_back(Token(UNDEFINED, temp, lineNumber));
				currState = start;
			}

			break;
		}


		break;
	case(colon):
		currState = start;
		colonCase(c);
		break;
	case(strings):
		stringCase(c);
		break;
	case(endstrings):
		endStringsCase(c);
		/*if (c == '\'') {
			temp += c;
			currState = strings;
		}
		else {
			tokenList.push_back(Token(STRING, temp, lineNumber));
			lineNumber += addLine;
			currState = start;
			parseChar(c);
		}*/
		break;
	case(notBlockComment):
		notBlockCommentCase(c);
		/*if (c == '\n') {
			currState = start;
			tokenList.push_back(Token(COMMENT, temp, lineNumber));
			lineNumber++;
		}
		else if (c == EOF) {
			tokenList.push_back(Token(COMMENT, temp, lineNumber));
			endOfFile();
			currState = start;
		}
		else {
			temp += c;
			currState = notBlockComment;
		}*/
		break;
	case(comment):
		commentCase(c);
		/*THIS IS COMMENTCASE
		if (c == '|') {
			temp += c;
			addLine = 0;
			currState = blockComment;

		}
		else {
			temp += c;
			currState = notBlockComment;
		}*/
		//commentCase(c);
/*		if (c == '|') {
			temp += c;
			addLine = 0;
			currState = blockComment;
		}
		else if (c == '\n') {
			currState = start;
			tokenList.push_back(Token(COMMENT, temp, lineNumber));
			lineNumber++;
		}
		else if (c == EOF) {			
			tokenList.push_back(Token(COMMENT, temp, lineNumber));
			endOfFile();
			currState = start;

		}
		else {
			temp += c;
			currState = comment;
		}*/
		break;

	case(blockComment):
		blockCommentCase(c);
		break;
	case(commentEnd):
	/*	if (c == '#') {
			temp+= c;
			tokenList.push_back(Token(COMMENT, temp, lineNumber));
			lineNumber += addLine;
			currState = start;
		}
		else if(c== EOF){
			tokenList.push_back(Token(UNDEFINED, temp, lineNumber));
			lineNumber += addLine;
			endOfFile();
			currState = start;

		}

		else if(c== '|'){
			temp += c;
			currState = commentEnd;
		}
		else{
			temp += c;
			currState = blockComment;
		}*/
		commentEndCase(c);
		break;
	case(undefined):
		tokenList.push_back(Token(UNDEFINED, temp, lineNumber));
		currState = start;
		parseChar(c);
		break;

	case(id):
		idCase(c);
		break;
	default:
		temp += c;
		tokenList.push_back(Token(UNDEFINED, temp, lineNumber));
		currState = start;
	}


}

void LexicalParser::openFile(string fileName)
{

	ifstream infile;
	infile.open(fileName, ios::in);
	while (!infile.eof()) {
		parseChar(infile.get());
	}
	//endOfFile();

}

void LexicalParser::toString()
{
	for (unsigned int i = 0; i < tokenList.size(); i++) {
		tokenList[i].toString();
	}
}

void LexicalParser::endOfFile()
{
	tokenList.push_back(Token(END, "", lineNumber));
}

int LexicalParser::totalTokens()
{
	return tokenList.size();
}

void LexicalParser::setLineCount()
{
	lineCount = lineNumber;
}
LexicalParser::~LexicalParser()
{
}
