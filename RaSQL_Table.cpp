

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
		 
		//Debug*****
		cout<<"!table schema: "<<tempSchema<<endl;
		cout<<"!table schema count: "<<schema_attr_count<<endl;
		cout<<"!schema array: ";
		for(int i =0;i<schema_attr_count;i++)
		{
			cout<<"schema["<<i<<"]:"<<table_schema[i]<<endl;
		}
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