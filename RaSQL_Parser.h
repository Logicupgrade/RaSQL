
#include <string>
#include <iostream>

using namespace std;

class RaSQL_Parser
{
	

	public:
		int commandArraySize = 20;

		string commandArray[20];
		string 	DB_name = ".RaSQL";
		string 	Table_name = "";

		RaSQL_Parser();
		bool parse(string RaSQL_command_string);
		void clear();
};
