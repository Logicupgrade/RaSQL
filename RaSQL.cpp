
//Prompts input
//Parses Input
//Manages DB using Parsed Input
    //Validates Input Command syntax
        //if Invalid commands provides error message
    //Executes Valid commands

#include <iostream>
#include <string>

//#include "RaSQL_Parser.cpp"
#include "RaSQL_DB_Manager.cpp"

using namespace std;

int main(int argc, char** argv)
{
    string              DBCommand;
    bool                isGood = true;
    RaSQL_DB_Manager    the_manager;

    cout<<"Welcome to RaSQL Database Manager"<<endl;

    while(isGood)
    {
        cout<<">>";
        getline(cin,DBCommand);
        cout<<endl;

        the_manager.manage_cmd(DBCommand);
        
        //Exit Conditions
        if(cin.eof() || (the_manager.get_status() == -1) )
        {
            isGood = false;
        }
    }
    
}

