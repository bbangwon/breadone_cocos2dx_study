#include "DatabaseManager.h"
#include <string>

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
	std::string query = "create table if not exists TB_FACE(";
	query += "NO integer primary key autoincrement";
	query += ")";

	_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);

	if (_result == SQLITE_OK) {
		log("createDB() SUCCESS");
	}
	else
		log("ERROR CODE: %d, ERROR MSG: %s", _result, _errorMSG);
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
