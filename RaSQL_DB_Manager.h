
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "RaSQL_Parser.cpp"

using namespace std;

class RaSQL_DB_Manager
{
	private:
		int status = 0;

		string* DB_list;
		//string currentDB = "";

		bool find_DB_file(string DB_filename);//if found update currentDB with DB name
		bool load_DB_file();//use currentDB
		bool use_DB(string DB_name);//find,load
		bool create_DBO();
		bool create_DB_file();
		bool delete_DB_file();//find,delete

	public:
		RaSQL_DB_Manager();
		bool manage_cmd(string commandStr, string& current_database);//string* commands, int command_count);
		int get_status();
};