#pragma once

#include "sqlite3.h"
#include "cocos2d.h"

USING_NS_CC;

class DatabaseManager
{
private:
	bool openDB();
	void closeDB();
	sqlite3 *_sqlite;

public:
	DatabaseManager();
	~DatabaseManager();

	char *_errorMSG;
	int _result;

	static DatabaseManager *getInstance();
	void createDB();
};

