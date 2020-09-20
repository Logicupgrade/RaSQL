
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

bool RaSQL_Parser::parse(string cmd_str)
{
	clear();

	bool isLastCmd = false;
	
	int endCmdStr = cmd_str.length()-1;
	int frontIndex = 0;
	int endIndex;
	int commandCount = 0;

	string command;
	string leftOverStr;

	cmd_str = strToLower(cmd_str.length(),cmd_str);
	cout<<"cmd_str:"<<cmd_str<<endl;
	while(!isLastCmd)
	{
		
		leftOverStr = cmd_str;
		leftOverStr = leftOverStr.substr(frontIndex,endCmdStr);

		endIndex = leftOverStr.find(" ");

		//checks for last command and executes parse tasks
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

		frontIndex += endIndex+1;
		
		commandCount++;
		
	}
	
	//final parsing touch-ups:
	//excludes "(" at begining, "," at end, ")" at end
	if(commandArray[0] == "create" && commandArray[1] == "table")
	{
		//remove "(" from first property of schema
		commandArray[3] = commandArray[3].substr( 1, commandArray[3].length() );

		//remove last char ( "," & ")" ) from every attribute type
		for(int i=4;i<21;i+=2)
		{
			if(commandArray[i] != "")
			{
				commandArray[i] = commandArray[i].substr( 0, (commandArray[i].length()-1) );
			}
		}
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

