/*Parser Class CPP file

Author: Daniel Hayden
CS457

parses the input into commandArray property (array of strings)

*/
#include "RaSQL_Parser.h"

//description: parser default constructor 
//input: none 
RaSQL_Parser::RaSQL_Parser()
{
	//default constructor
}

//description: lowercase string conversion function 
//input: length of string, string to lowercase
//output: lowercase version of input string
string RaSQL_Parser::strToLower(int strLength, string theString)
{
	//array of uppercase alphabet
    char upperCase[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    //array of lowercase alphabet
	char lowerCase[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
	//loops through string and aphabet to find matches and replace with lowercase when match found
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

//****Function OLD - NOT USED*************
//description: input command string parser
//input: command string
//output: an array of parsed commands is created as a parser property(commandArray)
bool RaSQL_Parser::parseInput(string cmd_str)
{
	int frontIndex = 0;
	int endIndex;
	int endCmdStr = cmd_str.length();
	// bool clearEmpty = false;
	bool isLastCmd = false;
	string command;
	string leftOverStr;

	cmd_str = strToLower(cmd_str.length(),cmd_str);
	
	clear();
	
	//parse out '.exit'
	if(int(cmd_str.find(".exit"))>-1)
	{
		commandArray[0] = ".exit";
		return true;
	}

	//**TODO Parse out stuff with parenthesis ie: (kh,jkshdk,sdjf)
		//watch out for tabs and spaces

	//parse out 'insert into'
	if(int(cmd_str.find("insert into")) > -1 )
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
	
	//Create Table Parsing
	if(commandArray[0] == "create" && commandArray[1] == "table")
	{
		//remove "(" from first property of schema
		commandArray[3] = commandArray[3].substr( 1, commandArray[3].length() );

	}

	return true;
}

//description: input command string parser
//input: command string
//output: an array of parsed commands is created as a parser property(commandArray)
bool RaSQL_Parser::parseInput2(string cmd_str)
{
	string tempString = "";
	int temp_index = 0;

	//initialize string to parse
	cmd_str = strToLower(cmd_str.length(),cmd_str);
	clear();

	if( !cmd_str.empty() )
	{
		//loop through chars
		for(int i=0;i<int(cmd_str.length());i++ )
		{
			//if ' ' or '\t' or ',' or '(' or ')'
			if(	cmd_str[i] == ' '||
					cmd_str[i] == '\t'||
						cmd_str[i] == ','||
							cmd_str[i] == '('||
								cmd_str[i] == ')' )
			{
				//if string is not empty
				if( !tempString.empty() )
				{
					commandArray[commandCount] = tempString;
					commandCount++;
					tempString = "";
				}
			}
			else
			{
				tempString = tempString + cmd_str[i];
			}

			//if string == varchar skip '(',')'
			if(tempString == "varchar" || tempString == "char")
			{
				temp_index = cmd_str.find(')',i);
				commandArray[commandCount] = tempString + cmd_str.substr(i+1,temp_index-(i));
				
				commandCount++;
				i = temp_index;
				tempString = "";
			}

			//cout<<"tempString: "<<tempString<<endl;
		}

		commandArray[commandCount] = tempString;
		commandCount++;
	}

	return true;
}

//description: clears command array
//input: none
//output: command array has empty strings
void RaSQL_Parser::clear()
{
	for(int i = 0;i<20;i++)
	{
		commandArray[i] = "";
	}
}

