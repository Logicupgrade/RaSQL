
#include <fstream>

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

			int command_count = 0;
			//debugging
			for(int i =0;i<20;i++)
			{
				if(the_parser.commandArray[i] != "")
				{
					cout<<"Command Array["<<i<<"]:"<<the_parser.commandArray[i]<<endl;
					command_count++;
				}

			}
			//validate
			//execute

			//Create Command
			if(the_parser.commandArray[0] == "create")
			{
				cout<<"create"<<endl;

				//create database
				if(the_parser.commandArray[1] == "database")
				{
					string db_filename = "RaSQL_dbs/" + the_parser.commandArray[2] + ".txt";

					ifstream db_stream;
					db_stream.open(db_filename);

					if( db_stream.good() )
					{
						db_stream.close();

						cout<<"Did not create DB. DB '"<<the_parser.commandArray[2]<<"\' already exists"<<endl;
					}
					
					else
					{
						ofstream db_create_stream(db_filename);
						db_create_stream.close();
						cout<<"Created DB '"<<the_parser.commandArray[2]<<endl;
					}
					
					cout<<"create file exists?: "<<db_stream.good()<<endl;
				}
				//create table
				else if(the_parser.commandArray[1] == "table")
				{
					string table_filename = "RaSQL_tables/" + the_parser.commandArray[2] + ".txt";

					ifstream table_stream;
					table_stream.open(table_filename);

					if( table_stream.good() )
					{
						table_stream.close();

						cout<<"Did not create DB. DB '"<<the_parser.commandArray[2]<<"\' already exists"<<endl;
					}
					
					else
					{
						ofstream table_create_stream;
						table_create_stream.open(table_filename);
						
						//debug
						cout<<"command_count: "<<command_count<<endl;

						for(int i=3;i<command_count;i++)
						{
							table_create_stream << the_parser.commandArray[i] << ',';
						}
						
						table_create_stream.close();
						cout<<"Created Table '"<<the_parser.commandArray[2]<<endl;
					}
					
					cout<<"create file exists?: "<<table_stream.good()<<endl;
				}
			}

			//Drop Command
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
