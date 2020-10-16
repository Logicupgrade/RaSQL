
/*RaSQL program driver

Author: Daniel Hayden
CS457

The driver for RaSQL. It mainly just gets the input commands and passes them to the manager.
As of now this driver is where you can toggle on and off the showDebug option, where if on
will display variables throughout the program which is useful for debugging.

*/

//**** Notes ****
    //using naming conventions for table files (<DB name>-<Table name>.txt)
    //using premade directories(RaSQL_dbs,RaSQL_tables,RaSQL_data)
    //don't know how to make directories in c++

#include <iostream>
#include <string>
//debug parser
// #include "RaSQL_Parser.cpp"
#include "RaSQL_DB_Manager.cpp"

using namespace std;

int main(int argc, char** argv)
{
    //show variables for debugging
    bool                showDebug = false;

    string              DBCommand;
    string              current_DB;
    bool                isGood = true;
    RaSQL_DB_Manager    the_manager(showDebug);

    //debug parser
    RaSQL_Parser        the_parser;

    //cout<<"Welcome to RaSQL Database Manager"<<endl;

    while(isGood)
    {
        if(showDebug)
        {
            cout<<">>";
        }
        
        getline(cin,DBCommand, ';' );

        //debug - repeats input command
        //cout<<DBCommand<<endl;
        
        //debug parser


        // the_parser.parseInput(DBCommand);

        // cout<<"||"<<endl;

        // if(the_parser.commandArray[0] == ".exit")
        // {
        //     isGood = false;
        // }

        // for(int i =0;i<20;i++)
        // {
        //     if(the_parser.commandArray[i] != "")
        //     {
        //         //debugging
        //         cout<<"Command Array["<<i<<"]:"<<the_parser.commandArray[i]<<endl;
        //     }

        // }

        

        //cout<<endl;

        the_manager.manage_cmd(DBCommand, current_DB);
        
        //Exit Conditions
        if(cin.eof() || (the_manager.get_status() == -1) )
        {
            isGood = false;
        }
    }
    
}

