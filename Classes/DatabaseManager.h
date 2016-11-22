#pragma once

#include "sqlite3.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

struct head
{
public:
    int no;
    char *image;
    
    Point position;
    
    Color3B color1;
    Color3B color2;
    Color3B color3;
    Color3B color4;

	bool isColor;
};

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
    void insertDB();
    
    list<head*> selectDB(string table, int no);
};

