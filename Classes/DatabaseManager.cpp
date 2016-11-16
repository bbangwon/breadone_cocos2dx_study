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
