
//Prompts input
//Parses Input
//Manages DB using Parsed Input
    //Validates Input Command syntax
        //if Invalid commands provides error message
    //Executes Valid commands

#include <iostream>
#include <string>

#include "RaSQL_Parser.cpp"
#include "RaSQL_DB_Manager.cpp"

using namespace std;

string strToLower(int strLength, string theString);

int main(int argc, char** argv)
{
    string DBCommand;
    bool isGood = true;

    RaSQL_Parser        the_parser;
    RaSQL_DB_Manager    the_manager;

    cout<<"Welcome to RaSQL Database Manager"<<endl;

    while(isGood)
    {
        cout<<">>";
        getline(cin,DBCommand);
        DBCommand = strToLower( DBCommand.length(), DBCommand );
        
        the_parser.parse(DBCommand);

        the_manager.manage_cmd(the_parser.commandArray,the_parser.commandArraySize);

        //debugging
        for(int i =0;i<20;i++)
        {
            cout<<"Command Array["<<i<<"]:"<<the_parser.commandArray[i]<<endl;
        }
        cout<<endl;

        //Exit Conditions
        if(cin.eof() || the_parser.commandArray[0] == ".exit")
        {
            isGood = false;
        }

    }
    
}

string strToLower(int strLength, string theString)
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