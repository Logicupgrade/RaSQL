
/*Table Class CPP file

Author: Daniel Hayden
CS457

This table class parses the table file and implements it into a table object 
in order for maniputation of data and then updates the table file when done.

*/

#include "RaSQL_Table.h"

//description: counts the '|' chars + 1 in the first line of a table file to get the attribute count
//input: first line of table file
//output: number of '|' chars + 1
int RaSQL_Table::countSchemaAttr(string schemaLine)
{	
	int count = 0;

	//check for empty file
	if(schemaLine.length() > 0)
	{
		count = 1;

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



//description: initializes table_schema, table_schema_w_type, and full_table_schema
//input: first line of table file
//output: boolean of success
bool RaSQL_Table::getSchema( string schema_line )
{
	//checks for empty str
	if( schema_line.empty() )
	{
		return false;
	}

	//initialize schema(Table properties) variables
	schema_attr_count = countSchemaAttr(schema_line);

	//does include attr types
	full_table_schema = new string[schema_attr_count * 2];
	table_schema_w_type = new string[schema_attr_count];
	table_schema = new string[schema_attr_count];

	//full_table_schema indices
	int index = 0;
	//table_schema_w_type indices
	int index2 = 0;
	//table_schema indices
	int index3 = 0;

	//counts number of spaces
	int space_count = 0;

	//temp strings
	string temp_str = "";
	string temp_str2 = "";
	string temp_str3 = "";

	//loop length of schema string
	for(int i=0;i<int(schema_line.length());i++)
	{
		//if char is space store string as attr and 
		 
		if(schema_line[i] == ' ')
		{
			full_table_schema[index] = temp_str;
			
			//reset string
			temp_str = "";

			if(space_count < 1)
			{
				temp_str2 = temp_str2 + ' ';

				table_schema[index3] = temp_str3;

				//reset string
				temp_str3 = "";
				index3++;
			}


			index++;

			//skip 1 char
			i++;

			space_count++;
			if(space_count == 2)
			{
				space_count = 0;
			}

		}
		
		//if char is | skip 2 chars
		if(schema_line[i] == '|')
		{
			table_schema_w_type[index2] = temp_str2;
			temp_str2 = "";

			index2++;

			i+=2;
		}
		
		temp_str = temp_str + schema_line[i];
		temp_str2 = temp_str2 + schema_line[i];

		if(space_count < 1)
		{
			temp_str3 = temp_str3 + schema_line[i];
		}
		

		if( i == int(schema_line.length()-1) )
		{
			full_table_schema[index] = temp_str;
			table_schema_w_type[index2] = temp_str2;
		}
		
	}


	//***********************
	
	return true;
}

//description: initializes current_table property as empty 2D array
//input: none
//output: boolean of success
bool RaSQL_Table::makeCurrentTable()
{
	//initialize array by allocating table_entries(count) string pointers
	current_table = new string*[table_entries];

	//loops through array and initilizes array by allocating strings for pointer
	for(int i=0;i<table_entries;i++)
	{
		current_table[i] = new string[schema_attr_count]; 
	}
	return true;
}

//description: references input string to table_schema and returns index of first match
//input: reference string (possible attribute)
//output: matching index else -1
int RaSQL_Table::getSchemaIndex(string possible_attr)
{
	
	//get table schema index for where key
	for(int i = 0;i<schema_attr_count;i++)
	{
		//if input string matches table_schema[i]
		if(possible_attr == table_schema[i])
		{
			return i;
		}
	}
	
	return -1;
}


//description: checks if where expression is true or false in given string array (usually table row)
//input: string array to check and where expression
//output: returns if where expression is true or false for given string array
//notes: passes in a row to compare with expression
bool RaSQL_Table::whereMatch(string* check_entry, string where_key, string expressionStr, string where_value)
{
	//get given string(check_entry) index of where_key
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

	//checking for different boolean expressions
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
		if(stoi(check_entry[w_schema_index]) < stoi(where_value) )
		{
			isTrue = true;
		}
	}
	else if(expressionStr == ">")
	{
		if(stoi(check_entry[w_schema_index]) > stoi(where_value) )
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

//description: updates table file
//input: none
//output: success boolean
//notes: writes file after schema
//notes: skips entry if value at first index is ""
//**TODO: edit schema input to reflect current attributes
bool RaSQL_Table::update_table_file()
{
	//rewrite data after schema
	ofstream table_stream;
	table_stream.open(table_filename, ios::trunc);

	//number of times entries are skipped
	int skipped = 0;

	//if table file found
	if( table_stream.good() == 1 )
	{
		//**maybe replace with full_table_schema loop
		table_stream<<schema_input<<endl;

		//iterate through each entry
		for(int i=0;i<table_entries;i++)
		{
			//if empty skip because most likely deleted
			if(current_table[i][0] == "" )
			{
				skipped++;
			}
			else
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
				
				//loops through entries and finds first non "" then adds '\n'
				int k = i+1;
				while(k<table_entries)
				{
					if(current_table[k][0] != "" )
					{
						table_stream<<endl;
						break;
					}

					k++;
				}
					
			}
					
			
		}
	
		//close file stream
		table_stream.close();
		return true;
	}
	
	return false;
}

//description: Normal Table Constructor 
//input: name of the table, name of current database, boolean for debug comments
//output: none
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
		string tempSchema = "";

		//grab schema
		getline(table_stream,tempSchema);

		//grabbing schema for use in update (not relevant to this flow)
		schema_input = tempSchema;

		//initialize schema arrays
		getSchema(tempSchema);
		
		//Get number of row entries in table
		string placholder;
		table_entries = 0;

		//loop through file counting lines in file
		while(!table_stream.eof())
		{
			if(getline(table_stream,placholder))
			{
				table_entries++;
			}
		}

		//create empty 2D array
		makeCurrentTable();

		//reset ifstream flags
		table_stream.clear();

		//return stream to beginning
		table_stream.seekg(0,ios::beg);
		
		//skips schema
		getline(table_stream,tempSchema);
		
		//fill current table
		for(int i=0;i<table_entries;i++)
		{
			//grabs data row
			getline(table_stream,tempSchema);

			//loops through data attributes
			for(int j=0;j<schema_attr_count;j++)
			{
				//finds substring until " " and inserts data into current_table
				current_table[i][j] = tempSchema.substr(0,tempSchema.find(" "));

				//if finds '|' then grabs rest of substring 2 char after that
				if( int( tempSchema.find("|") ) > -1)
				{
					tempSchema = tempSchema.substr(tempSchema.find("|")+2,-1);
				}
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

//description: Table Join Constructor 
//input: pointer to table 1, alias of table 1, pointer to table 2, alias of table 2, 
//input: join type as a string, where key, where expression, and where value
//output: none
RaSQL_Table::RaSQL_Table(RaSQL_Table* t1, string t1_alias, RaSQL_Table* t2, string t2_alias,
							string join_type, string w_key, string w_expression, string w_value)
{
	//cout<<"params:"<<t1_alias<<","<<t2_alias<<","<<join_type<<","<<w_key<<","<<w_expression<<","<<w_value<<endl;

	//adds table name prefix to schema attributes in table 1 and table 2
	t1->addAttrPrefix(t1_alias);
	t2->addAttrPrefix(t2_alias);
	
	// initialize joined attributes of both table 1 and table 2
	schema_attr_count = t1->schema_attr_count + t2->schema_attr_count;

	//initialize different table schemas
	table_schema = new string[schema_attr_count];
	full_table_schema = new string[2*schema_attr_count];
	table_schema_w_pre = new string[schema_attr_count];

	//fills schema and schema with prefix arrays with values from table 1 and table 2 corresponding schema arrays
	//fills first part with table 1 values
	for(int i=0;i<t1->schema_attr_count;i++)
	{
		table_schema[i] = t1->table_schema[i];
		table_schema_w_pre[i] = t1->table_schema_w_pre[i];
	}
	//fills second part with table 2 values
	for(int j=t1->schema_attr_count;j<schema_attr_count;j++)
	{
		table_schema[j] = t2->table_schema[j-t1->schema_attr_count];
		table_schema_w_pre[j] = t2->table_schema_w_pre[j-t1->schema_attr_count];
	}

	//fills full_table_schema with values from table 1 and table 2 corresponding schema arrays
	//fills first part with table 1 values
	for(int i=0;i<t1->schema_attr_count*2;i++)
	{
		full_table_schema[i] = t1->full_table_schema[i];
	}
	//fills first part with table 2 values
	for(int j=t1->schema_attr_count*2;j<schema_attr_count*2;j++)
	{
		full_table_schema[j] = t2->full_table_schema[j-t1->schema_attr_count*2];
	}

	//create full table join 
	//multiply table 1 entry count by table 2 entry count
	table_entries = t1->table_entries * t2->table_entries;

	//initializes empty current_table 2D array using previous variables
	makeCurrentTable();

	//fill current table with both table entries

	//number of entries
	int q=0;
	//number of t1 entries
	for(int s=0;s<t1->table_entries;s++)
	{
		//number of t2 entries
		for(int r=0;r<t2->table_entries;r++)
		{
			//enter t1 entries
			for(int t=0;t<t1->schema_attr_count;t++)
			{
				current_table[q][t] = t1->current_table[s][t];
			}
			//enter t2 entries
			for(int u=t1->schema_attr_count;u<schema_attr_count;u++)
			{
				current_table[q][u] = t2->current_table[r][u-t1->schema_attr_count];
			}
			q++;	
		}
	}

	
	//Refactor at some point
	//saving initial table_schema values
	/*replacing table_schema with table_schema_w_pre values in order 
	to match schema attributes with w_key and w_value */
	string temp_string[schema_attr_count];

	for(int i=0;i<schema_attr_count;i++)
	{
		temp_string[i] = table_schema[i];
		table_schema[i] = table_schema_w_pre[i];
	}
	//****

	//get index values of keys
	int w_key_index = getSchemaIndex(w_key);
	int w_value_index = getSchemaIndex(w_value);


	//display

	//loops through full_table_schema
	for(int k =0;k<schema_attr_count*2;k++)
	{
		//prints attribute
		cout<<full_table_schema[k]<<" ";

		//after even num of attributes print '|' unless last two
		if(k%2==1 && k<(schema_attr_count*2 - 1) )
		{
			cout<<"| ";
		}
	}
	cout<<endl;
	
	//if "left outer join"
	if(join_type == "left outer join")
	{
		//initialize a count of passed entries
		int count_passed = 0;
		
		//loops through table entries
		for(int l=0;l<table_entries;l++)
		{
			//reset passed entry count after last instance of table 1 entries
			if(l%t1->table_entries == 0)
			{
				count_passed = 0;
			}

			//if row value at where key and where value are equal
			if(current_table[l][w_key_index] == current_table[l][w_value_index])
			{
				//loop through table row values
				for(int m=0;m<schema_attr_count;m++)
				{
					//print table row value
					cout<<current_table[l][m];

					//print "|" after row value unless its the last one
					if(m<schema_attr_count-1)
					{
						cout<<"|";
					}
				}
				cout<<endl;
			}
			//if where key and where value ar not equal
			else
			{
				//increment passed row count
				count_passed++;

				//if passed all instances of table one value
				if(count_passed == t2->table_entries)
				{
					//print all table 1 values
					for(int i=0;i<t1->schema_attr_count;i++)
					{
						cout<<current_table[l][i]<<"|";
					}
					//print empty "" for all table 2 values
					for(int j=0;j<t2->schema_attr_count;j++)
					{
						if(j<t2->schema_attr_count-1)
						{
							cout<<"|";
						}
					}
					cout<<endl;
				}
			}

		}
	}
	
	//if other type of join (inner joins)
	else
	{
		
		//loop through table entries
		for(int l =0;l<table_entries;l++)
		{
			//if row value at where key and where value are equal
			if(current_table[l][w_key_index] == current_table[l][w_value_index])
			{
				//loop through table row values
				for(int m=0;m<schema_attr_count;m++)
				{
					//print row values
					cout<<current_table[l][m];
					if(m<schema_attr_count-1)
					{
						cout<<"|";
					}
				}
				cout<<endl;
			}
			
		}
	}

	//**make function
	// prints entire current_table
	// cout<<"____________________"<<endl;
	// for(int l =0;l<table_entries;l++)
	// {
	// 	for(int m=0;m<schema_attr_count;m++)
	// 	{
	// 		cout<<current_table[l][m];
	// 		if(m<schema_attr_count-1)
	// 		{
	// 			cout<<",";
	// 		}
	// 	}
	// 	cout<<endl;
	// }

	// cout<<"____________________"<<endl;
	 
}

//description: Delete (filter values) function
//input: where key, where expression to compare, where value
//output: returns number of rows "deleted"
//notes: sets first value in row to "" and is skipped when updating file
int RaSQL_Table::delete_vals(string where_key, string expressionStr, string where_value)
{
	int deleteCount = 0;

	//loop through all rows
	for(int i =0;i<table_entries;i++)
	{
		//if where value matches current row attr delete first attribute 
			//- update_table_file() will then skip entry when updating file
		if( whereMatch(current_table[i], where_key, expressionStr, where_value) )
		{
			current_table[i][0] = "";
			deleteCount++;
		}		
	}

	update_table_file();

	return deleteCount;
}


//TODO: Incorporate whereMatch()
//description: Update table function
//input: set key, set value, where key, where expression to compare, where value 
//output: count of updated rows
int RaSQL_Table::update_table(string set_key, string set_value, 
								string where_key, string expressionStr, string where_value)
{
	int updatedCount = 0;

	//initializes variables with index of where_key and set_key when matching schema attributes
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

		return -1;
	}

	int i = 0;
	while(i<table_entries)
	{
		if(current_table[i][w_schema_index] == where_value)
		{
			//change value
			current_table[i][s_schema_index] = set_value;

			updatedCount++;

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

	//update table file
	//update_table_file();
	
	return updatedCount;
}


//description: SQL Where function
//input: 2D array of expressions, count of expressions 
//output: returns int array of rows that match given constraint(s)
//note: uses previously defined Table properties
bool RaSQL_Table::where(string** expression_2d_array, int expression_count)
{
	//initialize current number of rows = all rows
	int current_num_rows = table_entries;

	//debug
	//cout<<"current_num_rows: "<<current_num_rows<<endl;
	
	//initialize int arrray of rows with matching values
	int matches[current_num_rows];
	int match_count = 0;

	//loops through all expressions
	for(int exps=0;exps<expression_count;exps++)
	{
		
		//loops through current num_rows
		for(int i=0;i<current_num_rows;i++)
		{
			//if row matches expression 
			if( whereMatch(current_table[i], expression_2d_array[exps][0], expression_2d_array[exps][1], expression_2d_array[exps][2]) )
			{
				//adds index to matches array
				matches[match_count] = i;

				//increments matches array index
				match_count++;
			}			
		}
	}

	//initializes where_matches(table property) to current_num_rows size
	where_match_count = match_count;
	where_matches = new int [where_match_count];
	
	//copies local matches array to table property where_matches array
	for(int j = 0;j<current_num_rows;j++)
	{
		where_matches[j] = matches[j];
	}

	//debug
	//cout<<"where_match indices: ";
	// for(int m = 0; m<where_match_count;m++)
	// {
	// 	cout<<where_matches[m]<<",";
	// }
	// cout<<endl;
	// cout<<"________"<<endl;

	return true;

}

//description: SQL Select function
//input: string array of select values, count of select values 
//output: success boolean
//note: uses previously defined Table properties and Table "where" properties
bool RaSQL_Table::select( string* select_vals, int select_val_count )
{

	// if(select_vals[0] == "*")
	// {
	// 	select_vals = new string[where_match_count];

	// 	for(int i=0;i<where_match_count;i++)
	// 	{
	// 		select_vals[i] = where_matches[i];
	// 	}
		
	// 	select_val_count = where_match_count;
	// }

	//create array for schema indices of size of the count of the selectors
	int schemaIndices[select_val_count];

	//for each selector fill the schema indices array with the current table column index for matching attributes
	for(int i=0;i<select_val_count;i++)
	{
		schemaIndices[i] = getSchemaIndex(select_vals[i]);

		cout<<table_schema_w_type[schemaIndices[i]];

		if(i < select_val_count-1)
		{
			cout<<" | ";
		}
	}

	cout<<endl;
	
			

	//print the current table filtering out the where indicies(rows) and the selector indicies(columns)
	for(int j = 0;j<where_match_count;j++)
	{
		for(int k = 0;k<select_val_count;k++)
		{
			
			cout<<current_table[where_matches[j]][schemaIndices[k]];

			if(k<select_val_count-1)
			{
				cout<<" | ";
			}
		}

		cout<<endl;
		
	}

	
	// //remake currrent_table
	// for(int i=0;i<table_entries;i++)
	// {
	// 	delete[] current_table[i];
	// }

	// delete[] current_table;
	
	//make current table of size where_entries X select value count
	// current_table = new string* [where_entries];

	// for(int i=0;i<where_entries;i++)
	// {
	// 	current_table[i] = new string[select_val_count];
	// }

	
	// schema_attr_count = select_val_count;
	// table_entries = where_entries;

	// for(int j=0;j<where_entries;j++)
	// {
	// 	if(whereTable[j][0] != "")
	// 	{
	// 		for(int m=0;m<select_val_count;m++)
	// 		{
	// 			current_table[j][m]=whereTable[j][schemaIndices[m]];
	// 		}
	// 	}
		
	// }


	
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


//description: Verbose debug flag function
//input: bool to turn on or off debug mode
//output: none
//note: prints variables to the terminal output
void RaSQL_Table::debugMode( bool toDeOrNotToDe )
{
	//changes isDebug Table Property
	isDebug = toDeOrNotToDe; 
}


//description: add schema attribute prefix function
//input: table name
//output: none
//notes: adds table alias + '.' in front of all attributes
void RaSQL_Table::addAttrPrefix(string table_name)
{
	//initialize table schema with prefix 
	table_schema_w_pre = new string[schema_attr_count];

	//loops through all schema attributes
	for(int i=0;i<schema_attr_count;i++)
	{
		//adds prefix of <table name> + '.' to schema attributes in table_schema array
		table_schema_w_pre[i] = table_name + '.' + table_schema[i];
	}
}

bool RaSQL_Table::commit()
{
	//update table file with table object
	return update_table_file();
}