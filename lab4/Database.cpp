#include "Database.h"



Database::Database()
{
}

int Database::countTuple() {
	int count = 0;
	for (std::map<string, Relation>::iterator it = this->begin(); it != this->end(); ++it) {
		count += it->second.getTuples().size();
	}
	return count;
}
Database::~Database()
{
}
