

#include "RaSQL_Table.h"

int RaSQL_Table::countSchemaAttr(string schemaLine)
{
	//count the '|' chars + 1
	int count = 1;

	//check for empty file
	if(schemaLine.length() > 0)
	{
		//count schema attributes
		
		for(int i=0;i<int(schemaLine.length());i++)
		{
			if(schemaLine[i] == '|')
			{
				count++;
			}
		}
	}

	return count;
}

bool RaSQL_Table::makeCurrentTable()
{
	current_table = new string*[table_entries];

	for(int i=0;i<table_entries;i++)
	{
		current_table[i] = new string[schema_attr_count]; 
	}
	return true;
}

int RaSQL_Table::getSchemaIndex(string possible_attr)
{
	//get table schema index for where key
	for(int i = 0;i<schema_attr_count;i++)
	{
		if(possible_attr == table_schema[i])
		{
			return i;
		}
	}

	return -1;
}

bool RaSQL_Table::whereMatch(string* check_entry, string where_key, string expressionStr, string where_value)
{
	int w_schema_index = getSchemaIndex(where_key);

	//default to false: nothing will be altered if there is issue
	bool isTrue = false;

	//keys did not match any attribute
	if( w_schema_index < 0 )
	{
		//debug
		if(isDebug)
		{
			cout<<"where key: '"<<where_key<<"' not found"<<endl;
		}

		return false;
	}

	if(expressionStr == "=")
	{
		if(check_entry[w_schema_index] == where_value )
		{
			isTrue = true;
		}
	}
	else if(expressionStr == "!=")
	{
		if(check_entry[w_schema_index] != where_value )
		{
			isTrue = true;
		}
	}
	else if(expressionStr == "<")
	{
		if(check_entry[w_schema_index] < where_value )
		{
			isTrue = true;
		}
	}
	else if(expressionStr == ">")
	{
		if(check_entry[w_schema_index] > where_value )
		{
			isTrue = true;
		}
	}
	else
	{
		if(isDebug)
		{
			cout<<"Did not match 'where' expression string"<<endl;
		}
	}

	return isTrue;
	
}

bool RaSQL_Table::update_table_file()
{
	//rewrite data after schema
	ofstream table_stream;
	table_stream.open(table_filename);

	//if table file found
	if( table_stream.good() == 1 )
	{
		table_stream<<schema_input<<endl;

		//iterate through each entry
		for(int i=0;i<table_entries;i++)
		{
			//if empty skip because most likely deleted
			if(current_table[i][0] != "")
			{
				//iterate through each entry's attribute
				for(int j=0;j<schema_attr_count;j++)
				{
					//print entry attribute to file
					table_stream<<current_table[i][j];

					//print spacer after entry except last entry
					if(j<schema_attr_count-1)
					{
						table_stream<<" | ";
					}
				}
			}
			
			//prints newline char after every entry but last
			if(i<table_entries-1)
			{
				table_stream<<endl;
			}
		}
	
		//close file stream
		table_stream.close();
		return true;
	}
	
	return false;
}

RaSQL_Table::RaSQL_Table(string table_name, string currentDB, bool debugger)
{
	//show variables for debugging or not
	debugMode( debugger );

	//create filename from inputs
	table_filename = "RaSQL_tables/" + currentDB +"-"+ table_name + ".txt";

	//read schema from table file
	ifstream table_stream;
	table_stream.open(table_filename);

	//if table file found
	if( table_stream.good() == 1 )
	{
		string tempSchema;
		//grab schema
		getline(table_stream,tempSchema);

		//grabbing schema for use in update (not relevant to this flow)
		schema_input = tempSchema;

		//update schema attr count
		schema_attr_count = countSchemaAttr(tempSchema);

		//instantiate schema array of count
		table_schema = new string[schema_attr_count];

		for(int i=0;i<schema_attr_count;i++)
		{
			table_schema[i] = tempSchema.substr(0,tempSchema.find(" "));

			tempSchema = tempSchema.substr(tempSchema.find("|")+2,-1);
		}

		//Get number of row entries in table
		table_entries = 0;
		while(!table_stream.eof())
		{
			if(table_stream.get() == '\n')
			{
				table_entries++;
			}
		}
		//add one more for the last line without a '\n' char
		table_entries++;

		//create empty 2D array
		makeCurrentTable();

		//reset ifstream flags
		table_stream.clear();
		//return stream to beginning
		table_stream.seekg(0);

		getline(table_stream,tempSchema);


		//fill current table
		for(int i=0;i<table_entries;i++)
		{
			getline(table_stream,tempSchema);

			for(int j=0;j<schema_attr_count;j++)
			{
				current_table[i][j] = tempSchema.substr(0,tempSchema.find(" "));
				tempSchema = tempSchema.substr(tempSchema.find("|")+2,-1);
			}	
		}


		//Debug*****
		if(isDebug)
		{
			cout<<"!table schema count: "<<schema_attr_count<<endl;
			cout<<"!schema array: ";
			for(int i =0;i<schema_attr_count;i++)
			{
				cout<<"schema["<<i<<"]:"<<table_schema[i]<<endl;
			}
			cout<<"!Table entries:"<<table_entries<<endl;

			cout<<"!!!theTABLE:"<<endl;
			for(int i=0;i<table_entries;i++)
			{
				getline(table_stream,tempSchema);

				for(int j=0;j<schema_attr_count;j++)
				{
					cout<<"table ["<<i<<"]["<<j<<"]: "<<current_table[i][j]<<",";
				}
				cout<<endl;
			}
			cout<<endl;
		}
		//*****
	}

	table_stream.close();
}
bool RaSQL_Table::delete_vals(string where_key, string expressionStr, string where_value)
{
	for(int i =0;i<schema_attr_count;i++)
	{
		if( whereMatch(current_table[i], where_key, expressionStr, where_value) )
		{
			current_table[i][0] = "";
		}		
	}

	update_table_file();

	return true;
}


//TODO: Incorporate whereMatch()
bool RaSQL_Table::update_table(string set_key, string set_value, 
								string where_key, string expressionStr, string where_value)
{
	int w_schema_index = getSchemaIndex(where_key);
	int s_schema_index = getSchemaIndex(set_key);

	//keys did not match any attribute
	if( w_schema_index < 0 || s_schema_index < 0)
	{

		string possible_attr;
		string key_type;
		//could not match where key
		if(w_schema_index < 0)
		{
			possible_attr = where_key;
			key_type = "where";
		}
		//could not match set key
		else
		{
			possible_attr = set_key;
			key_type = "set";
		}

		//debug
		if(isDebug)
		{
			cout<<"update "<<key_type<<" key: '"<<possible_attr<<"' not found"<<endl;
		}

		return false;
	}

	int i = 0;
	while(i<table_entries)
	{
		if(current_table[i][w_schema_index] == where_value)
		{
			//change value
			current_table[i][s_schema_index] = set_value;

			//update table file
			update_table_file();

			//debug
			if(isDebug)
			{
				cout<<"y index: "<<i<<endl;
				cout<<"x index: "<<s_schema_index<<endl;
				cout<<"value: "<<set_value<<endl;
			}
			
		}
		i++;
	}
	
	return true;
}

bool RaSQL_Table::set_table_name()
{
	return true;
}
bool RaSQL_Table::get_table_name()
{
	return true;
}

bool RaSQL_Table::add_schema_attr()
{
	return true;
}
bool RaSQL_Table::remove_schema_attr()
{
	return true;
}

//prints variables to the terminal output
void RaSQL_Table::debugMode( bool toDeOrNotToDe )
{
	isDebug = toDeOrNotToDe; 
}