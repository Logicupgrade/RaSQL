
#include <string>
#include <iostream>

using namespace std;

class RaSQL_Parser
{
	

	public:
		int commandArraySize = 20;
		int commandCount = 0;

		string commandArray[20];
		string 	DB_name = ".RaSQL";
		string 	Table_name = "";
		

		RaSQL_Parser();
		string strToLower(int strLength, string theString);
		bool parseInput(string RaSQL_command_string);
		void clear();
};
