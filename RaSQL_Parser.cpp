
#include "RaSQL_Parser.h"

// std::string s = "scott>=tiger";
// std::string delimiter = ">=";
// std::string token = s.substr(0, s.find(delimiter)); // token is "scott"

RaSQL_Parser::RaSQL_Parser()
{
	//default constructor
}

bool RaSQL_Parser::parse(string cmd_str)
{
	bool isLastCmd = false;
	
	int frontIndex = 0;
	int endIndex;
	string command;

	while(!isLastCmd)
	{
		endIndex = cmd_str.find(" ");
		//checks for last command and then gets rid of ";"
		if(endIndex == -1 )
		{
			endIndex = (cmd_str.length()-1);
			isLastCmd = true;
		}

		command = cmd_str.substr(frontIndex,endIndex);

		cout<<"Command: "<<command<<endl;

		frontIndex = endIndex+1;
	}
	
	return true;
}

