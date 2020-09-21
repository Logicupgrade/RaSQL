
#include "RaSQL_DB_Manager.h"

#include "RaSQL_Parser.cpp"


		bool RaSQL_DB_Manager::find_DB_file(string DB_filename)//if found update currentDB with DB name
		{
			return true;
		}
		bool RaSQL_DB_Manager::load_DB_file()//use currentDB
		{
			return true;
		}
		bool RaSQL_DB_Manager::use_DB(string DB_name)//find,load
		{
			return true;
		}
		bool RaSQL_DB_Manager::create_DBO()
		{
			return true;
		}
		bool RaSQL_DB_Manager::create_DB_file()
		{
			return true;
		}
		bool RaSQL_DB_Manager::delete_DB_file()//find,delete
		{
			return true;
		}


		RaSQL_DB_Manager::RaSQL_DB_Manager()
		{
		}
		bool RaSQL_DB_Manager::manage_cmd(string commandStr)//string* commands, int command_count)
		{

			//parse
			RaSQL_Parser the_parser;
			the_parser.parse(commandStr);

			//debugging
			for(int i =0;i<20;i++)
			{
				if(the_parser.commandArray[i] != "")
				{
					cout<<"Command Array["<<i<<"]:"<<the_parser.commandArray[i]<<endl;
				}
			}
			//validate
			//execute
			if(the_parser.commandArray[0] == "create")
			{
				cout<<"create"<<endl;
			}
			else if(the_parser.commandArray[0] == "drop")
			{
				cout<<"drop"<<endl;
			}
			else if(the_parser.commandArray[0] == "use")
			{
				cout<<"use"<<endl;
			}
			else if(the_parser.commandArray[0] == "select")
			{
				cout<<"select"<<endl;
			}
			else if(the_parser.commandArray[0] == "alter")
			{
				cout<<"alter"<<endl;
			}
			else if(the_parser.commandArray[0] == ".exit")
			{
				status = -1;
				cout<<"bye bye"<<endl;
			}
			else
			{
				cout<<"Please enter correct Command"<<endl;
				
			}

			return true;
		}

		int RaSQL_DB_Manager::get_status()
		{
			return status;
		}
