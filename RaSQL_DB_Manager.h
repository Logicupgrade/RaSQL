
#include <string>
#include <iostream>

using namespace std;
class RaSQL_DB_Manager
{
	private:
		string* DB_list;
		string currentDB = "";

		bool find_DB_file(string DB_filename);//if found update currentDB with DB name
		bool load_DB_file();//use currentDB
		bool use_DB(string DB_name);//find,load
		bool create_DBO();
		bool delete_DB_file();//find,delete
		

	public:
		RaSQL_DB_Manager();
		bool manage_input(string* commands, int command_count);
};