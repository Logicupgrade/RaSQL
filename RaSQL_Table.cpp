

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

bool RaSQL_Table::fillCurrentTable()
{

	return true;
}

RaSQL_Table::RaSQL_Table(string table_name, string currentDB)
{
	//create filename from inputs
	string table_filename = "RaSQL_tables/" + currentDB +"-"+ table_name + ".txt";

	//read schema from table file
	ifstream table_stream;
	table_stream.open(table_filename);

	//if table file found
	if( table_stream.good() == 1 )
	{
		string tempSchema;
		//grab schema
		getline(table_stream,tempSchema);

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
		//*****
	}
	
	//loop through and make array of nodes
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