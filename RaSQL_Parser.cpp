
#include "RaSQL_Parser.h"


RaSQL_Parser::RaSQL_Parser()
{
	//default constructor
}

bool RaSQL_Parser::parse(string cmd_str)
{
	bool isLastCmd = false;
	
	int endCmdStr = cmd_str.length()-1;
	int frontIndex = 0;
	int endIndex;
	int commandCount = 0;

	string command;
	string leftOverStr;

	while(!isLastCmd)
	{
		
		leftOverStr = cmd_str;
		leftOverStr = leftOverStr.substr(frontIndex,endCmdStr);

		endIndex = leftOverStr.find(" ");

		//checks for last command and then gets rid of ";"
		if( endIndex == -1 || ( frontIndex > int(endCmdStr) ) )
		{
			endIndex = (endCmdStr - frontIndex);
			isLastCmd = true;
		}

		command = leftOverStr.substr(0,endIndex);

		commandArray[commandCount]=command;

		cout<<"LeftoverStr:"<<leftOverStr<<endl;

		cout<<"front Index:"<<frontIndex<<endl;
		cout<<"end Index:"<<endIndex<<endl;

		cout<<"Command:"<<command<<"|"<<endl;

		frontIndex += endIndex+1;
		
		commandCount++;
		
	}
	
	return true;
}

