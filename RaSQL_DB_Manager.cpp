
// database reference tags '--db_reference'
// for different file arrangment 

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

		bool RaSQL_DB_Manager::manage_cmd(string commandStr, string& current_database)//string* commands, int command_count)
		{

			int error_code = 0;

			//parse
			RaSQL_Parser the_parser;
			
			the_parser.parse(commandStr);

			int command_count = 0;
			
			for(int i =0;i<20;i++)
			{
				if(the_parser.commandArray[i] != "")
				{
					//debugging
					cout<<"Command Array["<<i<<"]:"<<the_parser.commandArray[i]<<endl;

					command_count++;
				}

			}
			//validate
			//execute

			//Create Command
			if(the_parser.commandArray[0] == "create")
			{
				//cout<<"create"<<endl;

				//create database
				if(the_parser.commandArray[1] == "database")
				{
					string db_filename = "RaSQL_dbs/" + the_parser.commandArray[2] + ".txt";

					ifstream db_stream;
					db_stream.open(db_filename);

					//database exists.. will not create database
					if( db_stream.good() )
					{
						db_stream.close();

						cout<<"!Failed to create'"<<the_parser.commandArray[2]<<"\' because already exists."<<endl;
					}
					
					//database doesn't exist..create database
					else
					{
						ofstream db_create_stream(db_filename);
						db_create_stream.close();
						cout<<"Database '"<<the_parser.commandArray[2]<<"\' created."<<endl;
					}
					
					//cout<<"create file exists?: "<<db_stream.good()<<endl;
				}
				
				//create table
				else if(the_parser.commandArray[1] == "table")
				{
															//--db_reference
					string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[2] + ".txt";

					ifstream table_stream;
					table_stream.open(table_filename);

					//table exists..will not create table
					if( table_stream.good() )
					{
						table_stream.close();

						cout<<"!Failed to create table '"<<the_parser.commandArray[2]<<"\' because it already exists."<<endl;
					}
					
					//table doesn't exist..create table
					else
					{
						ofstream table_create_stream;
						table_create_stream.open(table_filename);
						
						//debug
						//cout<<"command_count: "<<command_count<<endl;

						for(int i=3;i<command_count;i++)
						{
							table_create_stream << the_parser.commandArray[i] << ',';
						}
						
						table_create_stream.close();
						cout<<"Table '"<<the_parser.commandArray[2]<<"\' created."<<endl;
					}

					//print attributes
					// for(int i = 3; i<command_count;i++)
					// {
					// 	cout<<the_parser.commandArray[i]<<" ";
					// 	if(i%2 == 1 && (i<command_count-1) )
					// 	{
					// 		cout<<"| ";
					// 	}
					// }
					// cout<<endl;
					
				}
			}

			//Drop Command
			else if(the_parser.commandArray[0] == "drop")
			{
				//cout<<"drop"<<endl;

				//Drop Database
				if(the_parser.commandArray[1] == "database")
				{
					string db_filename = "RaSQL_dbs/" + the_parser.commandArray[2] + ".txt";
					const char* db_filename_cstr = db_filename.c_str();

					ifstream db_stream;
					db_stream.open(db_filename);

					//database exists..drop database
					if( db_stream.good() )
					{
						db_stream.close();

						//removes database and creates error code on fail
						if(remove(db_filename_cstr) != 0)
						{
							error_code = 2;
						}

						cout<<"Database '"<<the_parser.commandArray[2]<<"\' deleted"<<endl;
					}

					//database doesn't exist..will not drop database
					else
					{
						cout<<"!Failed to delete '"<<the_parser.commandArray[2]<<"\' because it does not exist."<<endl;
					}
				}

				//Drop Table
				else if(the_parser.commandArray[1] == "table")
				{
															//--db_reference
					string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[2] + ".txt";
					const char* table_filename_cstr = table_filename.c_str();

					ifstream table_stream;
					table_stream.open(table_filename);

					//table exists..drop table
					if( table_stream.good() )
					{
						table_stream.close();

						//removes table and creates error code on fail
						if(remove(table_filename_cstr) != 0)
						{
							error_code = 2;
						}

						cout<<"Table '"<<the_parser.commandArray[2]<<"\' deleted"<<endl;
					}

					//table doesn't exist..will not drop table
					else
					{
						cout<<"Failed to delete '"<<the_parser.commandArray[2]<<"\' because it does not exist."<<endl;
					}
				}

			}

			//Use Command
			else if(the_parser.commandArray[0] == "use")
			{
				//cout<<"use"<<endl;

				current_database = the_parser.commandArray[1];
				cout<<"Using Database '"<<current_database<<"'"<<endl;
			}

			//Select Command
			else if(the_parser.commandArray[0] == "select")
			{
				//cout<<"select"<<endl;

				string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[3] + ".txt";

				ifstream table_stream;
				table_stream.open(table_filename);

				//table exists..will grab content
				if( table_stream.good() == 1 )
				{
					string temp_str = "";
					string attributes[20];
					int attribute_count = 0;

					// save for transition to table object
					// vector<string> table_2D[20];
					
					getline(table_stream,temp_str);

					stringstream string_line(temp_str);

					while( getline(string_line,attributes[attribute_count],',') )
					{
						// cout<<"["<<attribute_count<<"]: "<<attributes[attribute_count]<<endl;
						attribute_count++;
					}

					//print attributes
					for(int i = 0; i<attribute_count;i++)
					{
						cout<<attributes[i]<<" ";
						if(i%2 == 1 && (i<attribute_count-1) )
						{
							cout<<"| ";
						}
					}
					cout<<endl;
					
					
				}
				else
				{
					error_code = 4;
					cout<<"!Failed to query table '"<<the_parser.commandArray[3]<<"' because it does not exist."<<endl;
				}
				


			}
			else if(the_parser.commandArray[0] == "alter")
			{
				//cout<<"alter"<<endl;
				string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[2] + ".txt";
				ofstream table_stream;
				table_stream.open(table_filename,ios::app);

				//table is found..proceed with commands
				if( table_stream.good() == 1 )
				{
					//if alter command is add
					if( the_parser.commandArray[3] == "add" )
					{
						table_stream<<the_parser.commandArray[4]<<","<<the_parser.commandArray[5]<<",";
						cout<<"Table '"<<the_parser.commandArray[2]<<"\' modified."<<endl;
					}
				}
				
				// table is not found.. can not alter table
				else
				{
					cout<<"!Failed to alter table '"<<the_parser.commandArray[2]<<"\' because it doesn't exist."<<endl;
				}
				
			}
			else if(the_parser.commandArray[0] == "insert")
			{
				//cout<<"insert"<<endl;
			}
			else if(the_parser.commandArray[0] == ".exit")
			{
				//exit status
				status = -1;
				cout<<"All done"<<endl;
			}
			else
			{
				cout<<"Please enter correct Command"<<endl;
				
			}

			//error code (0=Good,1)
			if(error_code == 0)
			{
				return true;
			}
			else
			{
				string error_string;

				if(error_code == 1){error_string = "create";}
				else if (error_code == 2){error_string = "drop";}
				else if (error_code == 3){error_string = "use";}
				else if (error_code == 4){error_string = "select";}
				else if (error_code == 5){error_string = "alter";}
				else if (error_code == 6){error_string = "insert";}
				
				//debug
				//cout<<"****Error with '"<<error_string<<"' command****"<<endl;
				return false;
			}
			
		}

		int RaSQL_DB_Manager::get_status()
		{
			return status;
		}
