
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
	int frontIndex = 0;
	int endIndex;
	int endCmdStr = cmd_str.length();
	bool clearEmpty = false;
	bool isLastCmd = false;
	string command;
	string leftOverStr;

	cmd_str = strToLower(cmd_str.length(),cmd_str);
	
	clear();

	
	
	while(!clearEmpty)
	{
		//parse out comments
		if( (cmd_str[frontIndex] == '-') && (cmd_str[frontIndex+1] == '-') )
		{
			int i = 0;
			while(cmd_str[i]!= '\r')
			{
				i++;
			}
			i++;
			frontIndex = i;	
		}
		//parse out nulls and new line chars and carriage returns
		else if(cmd_str[frontIndex] == '\0' || cmd_str[frontIndex] == '\n' || cmd_str[frontIndex] == '\r')
		{
			frontIndex++;
		}
		else
		{
			clearEmpty = true;	
		}
	}
	
	//parse out '.exit'
	if(int(cmd_str.find(".exit"))>-1)
	{
		commandArray[0] = ".exit";
		return true;
	}

	//parse out 'insert into'
	else if(int(cmd_str.find("insert into")) > -1 )
	{
		int tempBegin = cmd_str.find("into")+4;
		int tempEnd = cmd_str.find("values")-2;
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

		
		//another space check
		if(command[0] == ' ')
		{
			command = command.substr(2,command.length());
		}
		if(command[0] == int(13))
		{
			command = command.substr(2,command.length());
		}

		//comma check
		if(command[command.length()-1] == ',')
		{
			//remove ','
			command = command.substr(0,command.length() - 1);
		}

		//parenthesis check excluding "varchar()"
		if(command[command.length()-1] == ')' && 
			command.substr(0,7) != "varchar")
		{
			//remove ')'
			command = command.substr(0,command.length() - 1);
		}
		

		commandArray[commandCount] = command;

		if( command[command.length() - 1] == ';' )
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
	// if(commandCount > 0)
	// {
	// 	commandCount--;
	// }
	
	
	//Create Table Parsing
	if(commandArray[0] == "create" && commandArray[1] == "table")
	{
		//remove "(" from first property of schema
		commandArray[3] = commandArray[3].substr( 1, commandArray[3].length() );

		//remove last char "," from every attribute type
		// for(int j=4;j<21;j+=2)
		// {
		// 	if(commandArray[j] != "")
		// 	{
		// 		commandArray[j] = commandArray[j].substr( 0, (commandArray[j].length()-1) );
		// 	}
		// }

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

