#include "Parser.h"
#include "Parameter.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Expression.h"
#include "Rule.h"

using namespace std;

Parser::Parser(string fileName)
{
	LexicalParser lexi;
	lexi.openFile(fileName);
	pos = 0;
	allTokens = lexi.getTokensList();
}
void Parser::grammarCheck(DatalogProgram& datap) {
	checkScheme(datap);
	checkFacts(datap);
	checkRules(datap);
	checkQueries(datap);
//	cout << datap.toString();

}
void Parser::checkScheme(DatalogProgram& datap) {
	if (allTokens[pos].getType() == SCHEMES) {
		pos++;
		if (allTokens[pos].getType() == COLON) {
			pos++;
			scheme(datap);
			schemeList(datap);
		}
		else {
			throw runtime_error(allTokens[pos].retString());
		}
	}
	else {
		throw runtime_error(allTokens[pos].retString());
	}
}
void Parser::scheme(DatalogProgram& datap) {
	datap.addScheme(headPredicate());
	//headPredicate();
}
void Parser::schemeList(DatalogProgram& datap) {
	if (allTokens[pos].getType() == ID) {
		scheme(datap);
		schemeList(datap);
	}
	else return;

}
Predicate Parser::headPredicate() {
	if (allTokens[pos].getType() == ID) {
		Predicate pred(allTokens[pos].getValue());
		pos++;
		if (allTokens[pos].getType() == LEFT_PAREN) {
			pos++;
			if (allTokens[pos].getType() == ID) {
				Parameter p(allTokens[pos].getValue());
				pred.addParameter(p);
				pos++;
				idList(pred);
				if (allTokens[pos].getType() == RIGHT_PAREN) {
					pos++;
					return pred;
				}
				else {
					throw runtime_error(allTokens[pos].retString());
				}
			}
			else {
				throw runtime_error(allTokens[pos].retString());
			}

		}
		else {
			throw runtime_error(allTokens[pos].retString());
		}
	}
	else {
		throw runtime_error(allTokens[pos].retString());
	}
}
void Parser::idList(Predicate& pred) {		//Predicate& pred
	if (allTokens[pos].getType() == COMMA) {
		pos++;
		if (allTokens[pos].getType() == ID)
		{
			pred.addParameter(allTokens[pos].getValue());
			pos++;
			idList(pred);
		}
		else {
			throw runtime_error(allTokens[pos].retString());
		}
	}
	else return;
}
void Parser::stringList(Predicate& pred, DatalogProgram& datap) {
	if (allTokens[pos].getType() == COMMA) {
		pos++;
		if (allTokens[pos].getType() == STRING)
		{
			datap.addDomain(allTokens[pos].getValue());
			Parameter par(allTokens[pos].getValue());
			pred.addParameter(par);
			pos++;
			stringList(pred, datap);
		}
		else {
			throw runtime_error(allTokens[pos].retString());
		}
	}
	else return;
}
void Parser::checkFacts(DatalogProgram& datap) {
	if (allTokens[pos].getType() == FACTS) {
		pos++;
		if (allTokens[pos].getType() == COLON) {
			pos++;
			factList(datap);
		}
		else {
			throw runtime_error(allTokens[pos].retString());
		}
	}
	else {
		throw runtime_error(allTokens[pos].retString());
	}
}
void Parser::factList(DatalogProgram& datap) {
	if (allTokens[pos].getType() == ID) {
		datap.addFact(fact(datap));

		if (allTokens[pos].getType() == RIGHT_PAREN) {
			pos++;
			if (allTokens[pos].getType() == PERIOD) {
				pos++;
				//add it to the list
				factList(datap);
			}
			else throw runtime_error(allTokens[pos].retString());
		}
		else throw runtime_error(allTokens[pos].retString());
	}
	else return;

}
Predicate Parser::fact(DatalogProgram& datap) {
	if (allTokens[pos].getType() == ID) {
		Predicate pr(allTokens[pos].getValue());
		pos++;
		if (allTokens[pos].getType() == LEFT_PAREN) {
			pos++;
			if (allTokens[pos].getType() == STRING) {
				datap.addDomain(allTokens[pos].getValue());
				Parameter pa(allTokens[pos].getValue());
				pr.addParameter(pa);
				pos++;
				stringList(pr, datap);
				return pr;
			}
			else {
				throw runtime_error(allTokens[pos].retString());
			}
		}
		else {
			throw runtime_error(allTokens[pos].retString());
		}
	}
	else {
		throw runtime_error(allTokens[pos].retString());
	}
}

void Parser::checkRules(DatalogProgram& datap) {
	if (allTokens[pos].getType() == RULES) {
		pos++;
		if (allTokens[pos].getType() == COLON) {
			pos++;
			ruleList(datap);
		}
		else {
			throw runtime_error(allTokens[pos].retString());
		}
	}
	else {
		throw runtime_error(allTokens[pos].retString());
	}
}
void Parser::ruleList(DatalogProgram& datap) {
	if (allTokens[pos].getType() == ID) {
		datap.addRule(rule(datap));
		ruleList(datap);
	}
	else return;

}
Rule Parser::rule(DatalogProgram& datap) {
	Rule ru(headPredicate());

	if (allTokens[pos].getType() == COLON_DASH) {
		pos++;
		ru.addBodyPred(predicate2(ru));

		predicateList2(ru);
		if (allTokens[pos].getType() == PERIOD) {
			pos++;
			return ru;
		}
		else throw runtime_error(allTokens[pos].retString());
	}
	else throw runtime_error(allTokens[pos].retString());
}
Predicate Parser::predicate2(Rule& ru) {
	if (allTokens[pos].getType() == ID) {
		Predicate pred(allTokens[pos].getValue());
		pos++;
		if (allTokens[pos].getType() == LEFT_PAREN) {
			pos++;
			pred.addParameter(parameter(pred));
			parameterList(pred);
			if (allTokens[pos].getType() == RIGHT_PAREN) {
				pos++;
				return pred;
			}
			else throw runtime_error(allTokens[pos].retString());
		}
		else throw runtime_error(allTokens[pos].retString());
	}
	else throw runtime_error(allTokens[pos].retString());
}
void Parser::predicateList2(Rule& ru) {
	if (allTokens[pos].getType() == COMMA) {
		pos++;
		ru.addBodyPred(predicate2(ru));
		predicateList2(ru);
	}
	else return;
}
Predicate Parser::predicate() {
	if (allTokens[pos].getType() == ID) {
		Predicate pred(allTokens[pos].getValue());
		pos++;
		if (allTokens[pos].getType() == LEFT_PAREN) {
			pos++;
			pred.addParameter(parameter(pred));
			parameterList(pred);
			if (allTokens[pos].getType() == RIGHT_PAREN) {
				pos++;
				return pred;
			}
			else throw runtime_error(allTokens[pos].retString());
		}
		else throw runtime_error(allTokens[pos].retString());
	}
	else throw runtime_error(allTokens[pos].retString());
}
void Parser::predicateList() {
	if (allTokens[pos].getType() == COMMA) {
		pos++;
		predicate();
		predicateList();
	}
	else return;
}
void Parser::parameterList(class Predicate& pred) {
	if (allTokens[pos].getType() == COMMA) {
		pos++;
		pred.addParameter(parameter(pred));
		parameterList(pred);
	}
	else return;
}
Parameter Parser::parameter(Predicate& pred) {
	if (allTokens[pos].getType() == STRING) {
		Parameter p(allTokens[pos].getValue());
		pos++;
		return p;
	}
	else if (allTokens[pos].getType() == ID) {
		Parameter p(allTokens[pos].getValue());
		pos++;
		return p;
	}
	else if (allTokens[pos].getType() == LEFT_PAREN) {
		Parameter p(expression(pred));
		return p;
	}
	else {
		throw runtime_error(allTokens[pos].retString());
	}

}
string Parser::expression(class Predicate& pred) {
	if (allTokens[pos].getType() == LEFT_PAREN) {
		Expression expr;
		pos++;
		expr.setLeft(parameter(pred));
		expr.setOperator(operate());
		expr.setRight(parameter(pred));
		if (allTokens[pos].getType() == RIGHT_PAREN) {
			pos++;
			return expr.returnExpression();
			//add it to the list
		}
		else throw runtime_error(allTokens[pos].retString());
	}
	else throw runtime_error(allTokens[pos].retString());
}
string Parser::operate() {
	if (allTokens[pos].getType() == ADD) {
		pos++;
		return "+";
	}
	else if (allTokens[pos].getType() == MULTIPLY) {
		pos++;
		return "*";
	}
	else {
		throw runtime_error(allTokens[pos].retString());
	}

}
void Parser::checkQueries(DatalogProgram& datap) {
	if (allTokens[pos].getType() == QUERIES) {
		pos++;
		if (allTokens[pos].getType() == COLON) {
			pos++;
			query(datap);
			queryList(datap);
			if (allTokens[pos].getType() == END) {
//				cout << "Success!" << endl;
			}
			else throw runtime_error(allTokens[pos].retString());
		}
		else throw runtime_error(allTokens[pos].retString());
	}
	else throw runtime_error(allTokens[pos].retString());
}

void Parser::query(DatalogProgram& datap) {
	datap.addQuery(predicate());
	if (allTokens[pos].getType() == Q_MARK) {
		pos++;
	}
	else throw runtime_error(allTokens[pos].retString());
}
void Parser::queryList(DatalogProgram& datap) {
	if (allTokens[pos].getType() == ID) {
		query(datap);
		queryList(datap);
	}
	else return;
}



Parser::~Parser()
{
}
