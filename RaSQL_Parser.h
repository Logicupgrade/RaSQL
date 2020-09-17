
#include <string>
#include <iostream>

using namespace std;

class RaSQL_Parser
{
	private:
		string RaSQL_DB_commands[3] = {"create","drop","use"};
		string RaSQL_Table_commands[3] = {"create","alter","drop"};

	public:
		string commandArray[10] = {"","","","","","","","","",""};
		string 	DB_name = ".RaSQL";
		string 	Table_name = "";

		RaSQL_Parser();
		bool parse(string RaSQL_command_string);
		void clear();
};
