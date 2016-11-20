#include "DatabaseManager.h"
#include <string>
#include "DevConf.h"

#define DB_FILE_NAME "db.sqlite"

static DatabaseManager *_sharedSqlite = nullptr;

DatabaseManager::DatabaseManager()
{
}

DatabaseManager::~DatabaseManager()
{
	if (_sharedSqlite != nullptr) {
		_sharedSqlite->closeDB();
		_sharedSqlite = nullptr;
	}
}

DatabaseManager * DatabaseManager::getInstance()
{
	if (!_sharedSqlite) {
		_sharedSqlite = new DatabaseManager;
		_sharedSqlite->openDB();
	}
	return _sharedSqlite;
}

bool DatabaseManager::openDB()
{
	std::string path = FileUtils::getInstance()->getWritablePath() + DB_FILE_NAME;
	log("path : %s", path.c_str());

	_result = sqlite3_open(path.c_str(), &_sqlite);
	if (_result != SQLITE_OK) {
		log("failed to create db");
		return false;
	}
	return true;
}

void DatabaseManager::closeDB() {
	sqlite3_close(_sqlite);
}

void DatabaseManager::createDB()
{
	if (DB_INIT) {
		std::string path = FileUtils::getInstance()->getWritablePath() + DB_FILE_NAME;
		closeDB();
		remove(path.c_str());
		openDB();
	}

	for (int i = 0; i < 7; i++)
	{
		std::string query;
		switch (i) {
		case 0:
			query = "create table if not exists TB_FACE(";
			break;
		case 1:
			query = "create table if not exists TB_HAIR1(";
			break;
		case 2:
			query = "create table if not exists TB_HAIR2(";
			break;
		case 3:
			query = "create table if not exists TB_EYE(";
			break;
		case 4:
			query = "create table if not exists TB_MOUSE(";
			break;
		case 5:
			query = "create table if not exists TB_ETC(";
			break;
		case 6:
			query = "create table if not exists TB_BG(";
			break;
		}
		query += "NO integer primary key autoincrement, ";
		query += "IMG varChar(100), ";
		query += "X double default 0, ";
		query += "Y double default 0, ";

		query += "COLOR1_R interger default 0, ";
		query += "COLOR1_G interger default 0, ";
		query += "COLOR1_B interger default 0, ";

		query += "COLOR2_R interger default 0, ";
		query += "COLOR2_G interger default 0, ";
		query += "COLOR2_B interger default 0, ";

		query += "COLOR3_R interger default 0, ";
		query += "COLOR3_G interger default 0, ";
		query += "COLOR3_B interger default 0, ";

		query += "COLOR4_R interger default 0, ";
		query += "COLOR4_G interger default 0, ";
		query += "COLOR4_B interger default 0";

		query += ")";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);

		if (_result == SQLITE_OK) {
			log("createDB() SUCCESS");
		}
		else {
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
		}
	}
}
void DatabaseManager::insertDB() {
    std::string query = "insert into TB_FACE(NO) values (1), (2), (3)";
    _result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
    
    if(_result == SQLITE_OK) {
        log("insertDB SUCCESS");
    }
    else {
        log("ERROR CODE: %d, ERROR MSG: %s", _result, _errorMSG);
    }
}
void DatabaseManager::selectDB(){
    std::string query = "select * from TB_FACE";
    
    sqlite3_stmt *stmt = nullptr;
    _result = sqlite3_prepare_v2(_sqlite, query.c_str(), query.length(), &stmt, nullptr);
    
    if(_result == SQLITE_OK){
        log("selectDB() SUCCESS");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int no = sqlite3_column_int(stmt, 0);
            log("no : %d", no);
        }
    }
    else {
        log("ERROR CODE: %d, ERROR MSG: %s", _result, _errorMSG);
    }
    sqlite3_finalize(stmt);
}
