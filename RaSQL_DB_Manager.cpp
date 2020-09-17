
#include "RaSQL_DB_Manager.h"


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
		bool RaSQL_DB_Manager::delete_DB_file()//find,delete
		{
			return true;
		}


		RaSQL_DB_Manager::RaSQL_DB_Manager()
		{
		}
		bool RaSQL_DB_Manager::manage_input(string* commands, int command_count)
		{
			for(int i =0;i<command_count;i++)
			{
				cout<<"command["<<i<<"]:"<<commands[i]<<endl;
			}
			return true;
		}
