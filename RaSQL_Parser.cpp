
#include "RaSQL_Parser.h"


RaSQL_Parser::RaSQL_Parser()
{
	//default constructor
}

string RaSQL_Parser::strToLower(int strLength, string theString)
{
    char upperCase[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char lowerCase[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
    for(int i=0;i<strLength;i++)
    {
        for(int j=0;j<26;j++)
        {
            if(theString[i] == upperCase[j])
            {
                theString[i] = lowerCase[j];
            }
        }
    }
    return theString;
}

bool RaSQL_Parser::parseInput(string cmd_str)
{
	int frontIndex = 1;
	int endIndex;
	int endCmdStr = cmd_str.length();
	bool isLastCmd = false;
	string command;
	string leftOverStr;

	cmd_str = strToLower(cmd_str.length(),cmd_str);
	
	clear();

	//parse out comments
	if( (cmd_str[0] == '-' && cmd_str[1] == '-') || (cmd_str[1] == '-' && cmd_str[2] == '-') )
	{
		return true;
	}
	
	//parse out nulls and new line chars
	else if(cmd_str[1] == '\0' || cmd_str[1] == '\n')
	{
		return true;
	}
	
	//parse out '.exit'
	else if(cmd_str.substr(1,6) == ".exit")
	{
		commandArray[0] = ".exit";
		return true;
	}

	//parse out 'insert into'
	else if(cmd_str.substr(1,11) == "insert into")
	{
		int tempBegin = cmd_str.find(" ",10);
		int tempEnd = cmd_str.find(" ",13);
		int strEnd;
		string tempString;

		commandArray[0] = "insert";
		commandArray[1] = "into";
		commandArray[2] = cmd_str.substr(tempBegin + 1,tempEnd-tempBegin);
		commandArray[3] = "values";

		tempBegin = cmd_str.find("(");
		strEnd = cmd_str.find(")");
		tempString = cmd_str.substr(tempBegin + 1,strEnd-tempBegin);

		tempBegin = 0;
		
		
			tempEnd = tempString.find(",");
			commandArray[4] = tempString.substr(tempBegin,tempEnd-tempBegin);
			
			tempBegin = tempEnd;
			tempString = tempString.substr(tempBegin,-1);
			tempEnd = tempString.find(",",2);
			commandArray[5] = tempString.substr(2,tempEnd - 2);

			tempBegin = tempString.find("\t",3);
			tempEnd =  tempString.find(")");
			commandArray[6] = tempString.substr(tempBegin + 1,tempEnd-tempBegin-1);
			
			// tempBegin = tempEnd-tempBegin;
			// tempString = tempString.substr(tempBegin,-1);
			// commandArray[6] = tempString;

		return true;
	}
	
	while(!isLastCmd)
	{
		leftOverStr = cmd_str;
		leftOverStr = leftOverStr.substr(frontIndex,endCmdStr);

	 	endIndex = leftOverStr.find(" ");

		//checks for last command
		if( endIndex == -1 )
		{
			isLastCmd = true;
		}

		//**-1 as endIndex will return entire string
		command = leftOverStr.substr(0,endIndex);

		commandArray[commandCount] = command;

		if(command[command.length() - 1] == ';')
		{
			//remove ';'
			commandArray[commandCount] = command.substr(0,command.length() - 1);

			//reset 
			commandCount = 0;
		}
		else
		{
			commandCount++;
		}

		frontIndex += endIndex+1;
	}
	
	//final parsing touch-ups:

	//makes sure multiline cmds don't skip count
	if(commandCount > 0)
	{
		commandCount--;
	}
	
	
	//Create Table Parsing
	if(commandArray[0] == "create" && commandArray[1] == "table")
	{
		//remove "(" from first property of schema
		commandArray[3] = commandArray[3].substr( 1, commandArray[3].length() );

		//remove last char "," from every attribute type
		for(int j=4;j<21;j+=2)
		{
			if(commandArray[j] != "")
			{
				commandArray[j] = commandArray[j].substr( 0, (commandArray[j].length()-1) );
			}
		}

	}

	return true;
}

void RaSQL_Parser::clear()
{
	for(int i = 0;i<20;i++)
	{
		commandArray[i] = "";
	}
}

