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
			query = "create table if not exists TB_MOUTH(";
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
	{
		std::string query = "insert into TB_FACE(NO, IMG, X, Y, COLOR1_R, COLOR1_G, COLOR1_B, COLOR2_R, COLOR2_G, COLOR2_B, COLOR3_R, COLOR3_G, COLOR3_B, COLOR4_R, COLOR4_G, COLOR4_B) values ";
		query += "(1, 'face1.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(2, 'face2.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(3, 'face3.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(4, 'face4.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(5, 'face5.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(6, 'face6.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(7, 'face7.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(8, 'face8.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(9, 'face9.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219), ";
		query += "(10, 'face10.png', 156, 173, 254, 225, 194, 237, 188, 137, 184, 137, 105, 253, 242, 219)";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
		if (_result == SQLITE_OK)
			log("insertDB() SUCCESS");
		else
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	{
		std::string query = "insert into TB_HAIR1(NO, IMG, X, Y, COLOR1_R, COLOR1_G, COLOR1_B, COLOR2_R, COLOR2_G, COLOR2_B, COLOR3_R, COLOR3_G, COLOR3_B, COLOR4_R, COLOR4_G, COLOR4_B) values ";
		query += "(1, 'hair_1.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(2, 'hair_2.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(3, 'hair_3.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(4, 'hair_4.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(5, 'hair_5.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(6, 'hair_6.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(7, 'hair_7.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(8, 'hair_8.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(9, 'hair_9.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(10, 'hair_10.png', 156, 151.5, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34)";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
		if (_result == SQLITE_OK)
			log("insertDB() SUCCESS");
		else
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	{
		std::string query = "insert into TB_HAIR2(NO, IMG, X, Y, COLOR1_R, COLOR1_G, COLOR1_B, COLOR2_R, COLOR2_G, COLOR2_B, COLOR3_R, COLOR3_G, COLOR3_B, COLOR4_R, COLOR4_G, COLOR4_B) values ";
		query += "(1, 'hair_11.png', 156, 157, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(2, 'hair_12.png', 156, 157, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(3, 'hair_13.png', 156, 157, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(4, 'hair_14.png', 156, 157, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(5, 'hair_15.png', 156, 157, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(6, 'hair_16.png', 156, 157, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34), ";
		query += "(7, 'hair_17.png', 156, 157, 98, 59, 22, 170, 24, 13, 236, 183, 81, 62, 45, 34)";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
		if (_result == SQLITE_OK)
			log("insertDB() SUCCESS");
		else
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	{
		std::string query = "insert into TB_EYE(NO, IMG, X, Y, COLOR1_R, COLOR1_G, COLOR1_B, COLOR2_R, COLOR2_G, COLOR2_B, COLOR3_R, COLOR3_G, COLOR3_B, COLOR4_R, COLOR4_G, COLOR4_B) values ";
		query += "(1, 'eye_1.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(2, 'eye_2.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(3, 'eye_3.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(4, 'eye_4.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(5, 'eye_5.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(6, 'eye_6.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(7, 'eye_7.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(8, 'eye_8.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(9, 'eye_9.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(10, 'eye_10.png', 156, 166.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
		if (_result == SQLITE_OK)
			log("insertDB() SUCCESS");
		else
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	{
		std::string query = "insert into TB_MOUTH(NO, IMG, X, Y, COLOR1_R, COLOR1_G, COLOR1_B, COLOR2_R, COLOR2_G, COLOR2_B, COLOR3_R, COLOR3_G, COLOR3_B, COLOR4_R, COLOR4_G, COLOR4_B) values ";
		query += "(1, 'm_1.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(2, 'm_2.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(3, 'm_3.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(4, 'm_4.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(5, 'm_5.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(6, 'm_6.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(7, 'm_7.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(8, 'm_8.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(9, 'm_9.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(10, 'm_10.png', 156, 101.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
		if (_result == SQLITE_OK)
			log("insertDB() SUCCESS");
		else
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
	}
	{
		std::string query = "insert into TB_ETC(NO, IMG, X, Y, COLOR1_R, COLOR1_G, COLOR1_B, COLOR2_R, COLOR2_G, COLOR2_B, COLOR3_R, COLOR3_G, COLOR3_B, COLOR4_R, COLOR4_G, COLOR4_B) values ";
		query += "(1, 'etc_1.png', 156, 259, 234, 104, 119, 126, 206, 244, 189, 243, 57, 146, 7, 131), ";
		query += "(2, 'etc_2.png', 198, 118, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(3, 'etc_3.png', 156.5, 156.5, 234, 104, 119, 126, 206, 244, 189, 243, 57, 146, 7, 131), ";
		query += "(4, 'etc_4.png', 156.5, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(5, 'etc_5.png', 156, 272.5, 234, 104, 119, 126, 206, 244, 189, 243, 57, 146, 7, 131), ";
		query += "(6, 'etc_6.png', 156, 125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(7, 'etc_7.png', 156, 270, 234, 104, 119, 126, 206, 244, 189, 243, 57, 146, 7, 131), ";
		query += "(8, 'etc_8.png', 156, 267, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(9, 'etc_9.png', 156, 125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), ";
		query += "(10, 'etc_10.png', 156, 115, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
		if (_result == SQLITE_OK)
			log("insertDB() SUCCESS");
		else
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);

	}
	{
		std::string query = "insert into TB_BG(NO, IMG, X, Y, COLOR1_R, COLOR1_G, COLOR1_B, COLOR2_R, COLOR2_G, COLOR2_B, COLOR3_R, COLOR3_G, COLOR3_B, COLOR4_R, COLOR4_G, COLOR4_B) values ";
		query += "(1, 'bg_1.png', 156, 155.5, 250, 237, 125, 171, 242, 0, 0, 216, 255, 243, 97, 166), ";
		query += "(2, 'bg_2.png', 156, 155.5, 250, 237, 125, 171, 242, 0, 0, 216, 255, 243, 97, 166), ";
		query += "(3, 'bg_3.png', 156, 155.5, 250, 237, 125, 171, 242, 0, 0, 216, 255, 243, 97, 166), ";
		query += "(4, 'bg_4.png', 156, 155.5, 250, 237, 125, 171, 242, 0, 0, 216, 255, 243, 97, 166)";

		_result = sqlite3_exec(_sqlite, query.c_str(), nullptr, nullptr, &_errorMSG);
		if (_result == SQLITE_OK)
			log("insertDB() SUCCESS");
		else
			log("ERROR CODE : %d, ERROR MSG : %s", _result, _errorMSG);
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
