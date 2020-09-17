
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

		//checks for last command and then removes ";"
		if( endIndex == -1 || ( frontIndex > int(endCmdStr) ) )
		{
			//wonky but excludes ".exit" and "--" from removing ";"
			if(leftOverStr.substr(0,endCmdStr - frontIndex) == ".exit" ||
				( commandArray[0][0] == '-' && commandArray[0][1] == '-' ) )
			{
				endIndex = ( endCmdStr - frontIndex);
			}
			else
			{
				endIndex = ( endCmdStr - frontIndex - 1);
			}
			
			isLastCmd = true;
		}

		command = leftOverStr.substr(0,endIndex);

		commandArray[commandCount] = command;

		// cout<<"LeftoverStr:"<<leftOverStr<<endl;

		// cout<<"front Index:"<<frontIndex<<endl;
		// cout<<"end Index:"<<endIndex<<endl;

		// cout<<"Command:"<<command<<"|"<<endl;

		frontIndex += endIndex+1;
		
		commandCount++;
		
	}
	
	return true;
}

void RaSQL_Parser::clear()
{
	for(int i = 0;i<10;i++)
	{
		commandArray[i] = "";
	}
}

