
/*Manager Class CPP file

Author: Daniel Hayden
CS457

manages the parser to implement the commands
and manages the table objects and terminal output

The manager object calls the parser object in order to interpret commands 
and also the table object for manipulating and updating the table data.

*/


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

		//creates database file and returns true or doesn't and returns false
		bool RaSQL_DB_Manager::create_DB_file(string db_name)
		{
			bool created_file = false;
			//initialize filename:"RaSQL_dbs/" + <database> + ".txt"
					string db_filename = "RaSQL_dbs/" + db_name + ".txt";

					//initialize read file stream
					ifstream db_stream;
					db_stream.open(db_filename);

					//database exists.. will not create database
					if( db_stream.good() )
					{
						cout<<"!Failed to create'"<<db_name<<"\' because already exists."<<endl;
					}
					
					//database doesn't exist..create database
					else
					{
						//write database file name
						ofstream db_create_stream(db_filename);
						db_create_stream.close();

						created_file = true;

						cout<<"Database '"<<db_name<<"\' created."<<endl;
					}
					
					db_stream.close();

			return created_file;
		}

		bool RaSQL_DB_Manager::delete_DB_file()//find,delete
		{
			return true;
		}

		RaSQL_DB_Manager::RaSQL_DB_Manager(bool debugger)
		{
			debugMode(debugger);
		}

		bool RaSQL_DB_Manager::manage_cmd(string commandStr, string& current_database, bool& is_locked, 
											bool& has_changes, string* prev_update_attr, string& prev_table)
		{
			//error code initialization
			int error_code = 0;

			//instantiate parser object
			RaSQL_Parser the_parser;
			
			//parse the input command string
			the_parser.parseInput2(commandStr);
			
			//Iterates through comand array
				//counts commands in command array -- updates command_count manager property
				//debug-prints commands to terminal
			
			//reset command_count
			command_count = 0;

			for(int i =0;i<20;i++)
			{
				if(the_parser.commandArray[i] != "")
				{
					//debug
					if(isDebug)
					{
						cout<<"Command Array["<<i<<"]:"<<the_parser.commandArray[i]<<endl;
					}

					command_count++;
				}

			}

			//Create Command
			if(the_parser.commandArray[0] == "create")
			{
				//create database file
				if(the_parser.commandArray[1] == "database")
				{
					create_DB_file(the_parser.commandArray[2]);
				}
				
				//create table
				else if(the_parser.commandArray[1] == "table")
				{
					//creates table filename: "RaSQL_tables/" + <current database> +"-"+ <table name> + ".txt"
					string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[2] + ".txt";
					
					//creates file read stream
					ifstream table_stream;
					table_stream.open(table_filename);

					//table exists..will not create table
					if( table_stream.good() )
					{
						cout<<"!Failed to create table '"<<the_parser.commandArray[2]<<"\' because it already exists."<<endl;
					}
					
					//table doesn't exist..create table
					else
					{
						//creates file write stream
						ofstream table_create_stream;
						table_create_stream.open(table_filename);
						
						//loops through commands starting at 3 to command count and writes tables attributes to file
						for(int i=3;i<command_count;i++)
						{
							table_create_stream << the_parser.commandArray[i];
							
							//adds space after attr or attr type unless it is the last string in commandArray
							if(i<command_count-1)
							{
								table_create_stream<< ' ';
							} 

							//adds '|' + space after every second attr string unless its the last string in commandArray
							if(i%2 == 0 && i<(command_count-1) )
							{
								table_create_stream<<"| ";
							}
						}
						
						table_create_stream.close();

						cout<<"Table '"<<the_parser.commandArray[2]<<"\' created."<<endl;

						//***TODO: add table to database obj -> then update file 
					}

					table_stream.close();
					
				}
			}

			//Drop Command
			else if(the_parser.commandArray[0] == "drop")
			{
				//Drop Database
				if(the_parser.commandArray[1] == "database")
				{
					//creates file name: "RaSQL_dbs/" + <database> + ".txt"
					string db_filename = "RaSQL_dbs/" + the_parser.commandArray[2] + ".txt";

					//converts db filename to const char*
					const char* db_filename_cstr = db_filename.c_str();

					ifstream db_stream;
					db_stream.open(db_filename);

					//database exists..drop database
					if( db_stream.good() )
					{
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

					db_stream.close();
				}

				//Drop Table
				else if(the_parser.commandArray[1] == "table")
				{
					//creates file name: "RaSQL_tables/" + <current database> + "-" + <table name> + ".txt"
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
				//set current database to commandArray[1]
				current_database = the_parser.commandArray[1];
				cout<<"Using Database '"<<current_database<<"'."<<endl;
			}

			//Select Command
			else if(the_parser.commandArray[0] == "select")
			{
				
				//put all selects in string array
				int select_count = 0;
				int table_count = 0;
				int command_search_index = 1;

				//get command Array index before "from" keyword and count of selectors
				while(the_parser.commandArray[command_search_index] != "from" && select_count<10 )
				{
					command_search_index++;
					select_count++;
				}

				command_search_index++;
				
				//get number of table arguments
				while( (the_parser.commandArray[command_search_index] != "where" &&
						the_parser.commandArray[command_search_index] != "on") &&
							command_search_index < the_parser.commandCount )
				{
					command_search_index++;
					table_count++;
				}

				//if dealing with more than one table
				
				if(table_count > 1)
				{
					

					if(the_parser.commandArray[5] == "left" &&
						the_parser.commandArray[6] == "outer" &&
							the_parser.commandArray[7] == "join")
					{
						RaSQL_Table* t1 = new RaSQL_Table(the_parser.commandArray[3], current_database, isDebug);
						RaSQL_Table* t2 = new RaSQL_Table(the_parser.commandArray[8], current_database, isDebug);

						//RaSQL_Table(RaSQL_Table* t1, string t1_alias, RaSQL_Table* t2, string t2_alias,
						//string join_type, string w_key, string w_expression, string w_value);
						RaSQL_Table joinedTable(t1, the_parser.commandArray[4], t2, the_parser.commandArray[9],"left outer join", 
												the_parser.commandArray[11], the_parser.commandArray[12], the_parser.commandArray[13]);
					}
					else if (the_parser.commandArray[5] == "inner" &&
								the_parser.commandArray[6] == "join")
					{
						RaSQL_Table* t1 = new RaSQL_Table(the_parser.commandArray[3], current_database, isDebug);
						RaSQL_Table* t2 = new RaSQL_Table(the_parser.commandArray[7], current_database, isDebug);

						RaSQL_Table joinedTable(t1, the_parser.commandArray[4], t2, the_parser.commandArray[8],"", 
												the_parser.commandArray[10], the_parser.commandArray[11], the_parser.commandArray[12]);
					}
					
					else
					{
						RaSQL_Table* t1 = new RaSQL_Table(the_parser.commandArray[3], current_database, isDebug);
						RaSQL_Table* t2 = new RaSQL_Table(the_parser.commandArray[5], current_database, isDebug);

						RaSQL_Table joinedTable(t1, the_parser.commandArray[4], t2, the_parser.commandArray[6],"", 
												the_parser.commandArray[8], the_parser.commandArray[9], the_parser.commandArray[10]);
					}
					
					
					//exit(0);
				}
				//if dealing with only one table
				else
				{
					
				
					//create select string array
					string selector_array[select_count];
					
					//for all selectors put them into selector array
					for(int i = 0;i<select_count;i++)
					{
						selector_array[i] = the_parser.commandArray[i+1];
					}
					//***above grabs variables needed below*********************************
					//select_count
					//command_search_index
					//selector_array
					//****************************************************************

					

					//string array for all select values
					//string 
					int table_parse_index;
					if(the_parser.commandArray[1] == "*")
					{
						table_parse_index = 3;

						// creates table filename: "RaSQL_tables/" + "current database" + "-" + <table name> + ".txt"
						string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[table_parse_index] + ".txt";
						
						//creates read file stream
						ifstream table_stream;
						table_stream.open(table_filename);

						//table exists..will grab content and print to terminal output
						if( table_stream.good() )
						{
							string temp_str = "";
							
							//loops through table file and prints to terminal until end of file
							while( !table_stream.eof() )
							{
								getline(table_stream,temp_str);

								cout<<temp_str<<endl;
							}
			
						}
						//did not find table
						else
						{
							error_code = 4;
							cout<<"!Failed to query table '"<<the_parser.commandArray[3]<<"' because it does not exist."<<endl;
						}
					}
					else
					{
						//finds 'where' index in command array
						int where_find = 0;
						while(the_parser.commandArray[where_find] != "where")
						{
							where_find++;
						}
						
						//future: can setup for multiple where expressions

						//2d array of strings.. each has 3 depth (ex: 'pid = 5')
						string expressions_vals[3] = {the_parser.commandArray[where_find+1], 
														the_parser.commandArray[where_find+2], 
															the_parser.commandArray[where_find+3]};

						//expressions contains only one array currently
						string* expressions[1] = {expressions_vals};

						//instantiates table object
						RaSQL_Table theTable(the_parser.commandArray[4], current_database, isDebug);

						//FWGOS
						theTable.where(expressions,1); 
						theTable.select( selector_array, select_count);
						
					}

				}

				
				
				
			}
			else if(the_parser.commandArray[0] == "alter")
			{
				//creates filename: "RaSQL_tables/" + <current database> + "-" + <table name> + ".txt"
				string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[2] + ".txt";
				
				//creates a file write stream that appends to the end of the table file
				ofstream table_stream;
				table_stream.open(table_filename,ios::app);

				//table is found..proceed with commands
				if( table_stream.good() )
				{
					//if alter command is add
					if( the_parser.commandArray[3] == "add" )
					{
						table_stream<<"| "<<the_parser.commandArray[4]<<' '<<the_parser.commandArray[5];
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
				//creates table file name: "RaSQL_tables/" + <current database> + "-" + <table name> + ".txt"
				string table_filename = "RaSQL_tables/" + current_database +"-"+ the_parser.commandArray[2] + ".txt";

				//creates file write stream
				ofstream table_stream;
				table_stream.open(table_filename,ios::app);

				if( table_stream.good() )
				{
					//assuming if table exists it has attributes in it... go to next line
					table_stream <<endl;

					//loop through commands starting at for to command_count
					for(int i=4;i<command_count;i++)
					{
						table_stream << the_parser.commandArray[i];

						//adds space after value unless it is the last string in commandArray
						if(i<command_count-1)
						{
							table_stream<< ' ';
						} 

						//adds '|' + space after value unless it is the last string in commandArray
						if(i>3 && i<(command_count-1) )
						{
							table_stream<<"| ";
						}
					}

					cout<<"1 new record inserted."<<endl;
				}
			}
			else if(the_parser.commandArray[0] == "update")
			{
				//************** lock **************************************
				//lock file name
				string lock_file_name = "RaSQL_tables/" + current_database +"-"+the_parser.commandArray[1]+".lock";

				//try to read lock file
				ifstream RaSQL_lock_check;
				RaSQL_lock_check.open(lock_file_name);
				
				//if lock file found return false
				if( RaSQL_lock_check.good() )
				{
					RaSQL_lock_check.close();
					is_locked = true;
					cout<<"Error: Table " + the_parser.commandArray[1] + " is locked!"<<endl;

					return false;
				}
				
				has_changes = true;
				//create lock file
				ofstream RaSQL_file_lock;
				RaSQL_file_lock.open(lock_file_name, ios::trunc);
				RaSQL_file_lock<<"lock"<<endl;

				prev_table = the_parser.commandArray[1];

				prev_update_attr[0] = the_parser.commandArray[3];
				prev_update_attr[1] = the_parser.commandArray[5];
				prev_update_attr[2] = the_parser.commandArray[7];
				prev_update_attr[3] = the_parser.commandArray[8];
				prev_update_attr[4] = the_parser.commandArray[9];

				//**********************************************************

				
				//contructs table object with arguments: table name, current database, debug variable(boolean)
				RaSQL_Table theTable(the_parser.commandArray[1], current_database, isDebug);


				//updating table file with arguments: skey, sval, wkey, boolean expression string, wval
				int modifiedRecords = theTable.update_table(the_parser.commandArray[3],
																	the_parser.commandArray[5],
																		the_parser.commandArray[7],
																			the_parser.commandArray[8],
																				the_parser.commandArray[9]);

				//records modified terminal output
				if(modifiedRecords == 1)
				{
					cout<<modifiedRecords<<" record modified."<<endl;
				}
				else if(modifiedRecords == 0 || modifiedRecords > 1)
				{
					cout<<modifiedRecords<<" records modified."<<endl;
				}
				
			}
			else if(the_parser.commandArray[0] == "delete")
			{
				//contructs table obj with arguments: table name, currrent database, debug variable(boolean)
				RaSQL_Table theTable(the_parser.commandArray[2], current_database, isDebug);

				//calls delete_vals member function with arguments:string where_key, string expressionStr, string where_value
				int deletedRecords = theTable.delete_vals(the_parser.commandArray[4], the_parser.commandArray[5], the_parser.commandArray[6]);

				//records deleted terminal output
				if(deletedRecords == 1)
				{
					cout<<deletedRecords<<" record deleted."<<endl;
				}
				else if(deletedRecords == 0 || deletedRecords > 1)
				{
					cout<<deletedRecords<<" records deleted."<<endl;
				}

				
			}
			else if(the_parser.commandArray[0] == "begin" )//&& the_parser.commandArray[1] == "tansaction")
			{
				//begin transaction
				cout<<"Transaction starts."<<endl;
			}
			else if(the_parser.commandArray[0] == "commit")
			{
				if(!has_changes)
				{
					cout<<"Transaction abort."<<endl;
				}
				else
				{
					RaSQL_Table theTable(prev_table, current_database, isDebug);

					//debug
					//cout<<"Table update attributes{"<<prev_update_attr[0]<<","<<prev_update_attr[1]<<","<<prev_update_attr[2]<<","<<prev_update_attr[3]<<","<<prev_update_attr[4]<<"}"<<endl;

					theTable.update_table(prev_update_attr[0], 
											prev_update_attr[1], 
												prev_update_attr[2],
													prev_update_attr[3],
														prev_update_attr[4]);


					theTable.commit();
					
					cout<<"Transaction committed."<<endl;

					is_locked = false;
					has_changes = false;

					string lock_to_remove = "RaSQL_tables/" + current_database +"-"+prev_table+".lock";

					remove( lock_to_remove.c_str() );
				}
				
			}
			else if(the_parser.commandArray[0] == ".exit")
			{
				//exit status
				status = -1;
				cout<<"All done."<<endl;
			}
			else
			{
				if( the_parser.commandArray[0] == " " || 
					the_parser.commandArray[0] == "\n" || 
					the_parser.commandArray[0] == "\t" ||
					the_parser.commandArray[0] == "" )
				{
					//do nothing
					cout<<endl;
				}
				else
				{
					if(isDebug)
					{
						cout<<"Please enter correct Command|"<<int(the_parser.commandArray[0][0])<<endl;
					}
				}
					
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
				if(isDebug)
				{
					cout<<"****Error with '"<<error_string<<"' command****"<<endl;
				}

				return false;
			}
			
		}

		int RaSQL_DB_Manager::get_status()
		{
			return status;
		}

		//prints variables to the terminal output
		void RaSQL_DB_Manager::debugMode( bool toDeOrNotToDe )
		{
			isDebug = toDeOrNotToDe;
		}
