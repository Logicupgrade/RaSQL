
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

    while(isGood)
    {
        //command line prompt
        if(showDebug)
        {
            cout<<">>";
        }

        //copies input command until ';' into DBCommand variable
        getline(cin,DBCommand, ';' );

        //debug - repeats input command
        //cout<<DBCommand<<endl;

        //passese current command string and current db to be managed
        the_manager.manage_cmd(DBCommand, current_DB);
        
        //Exit Conditions
        if(cin.eof() || (the_manager.get_status() == -1) )
        {
            isGood = false;
        }
    }
    
}

