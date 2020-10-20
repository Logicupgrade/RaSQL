
/*Manager Class Header File

Author: Daniel Hayden
CS457

manages the parser to implement the commands
and manages the table objects and terminal output

*/


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include "RaSQL_Parser.cpp"
#include "RaSQL_Table.cpp"

using namespace std;

class RaSQL_DB_Manager
{
	private:
		//debug variable
		bool isDebug = false;

		int status = 0;
		int command_count = 0;

		string* DB_list;
		//string currentDB = "";

		bool find_DB_file(string DB_filename);//if found update currentDB with DB name
		bool load_DB_file();//use currentDB
		bool use_DB(string DB_name);//find,load
		bool create_DBO();
		bool create_DB_file(string db_name);
		bool delete_DB_file();//find,delete

	public:
		RaSQL_DB_Manager(bool debugger);
		bool manage_cmd(string commandStr, string& current_database);//string* commands, int command_count);
		int get_status();

		void debugMode( bool toDeOrNotToDe );
};