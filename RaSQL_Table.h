
/*Table Class Header File

Author: Daniel Hayden
CS457

This table class parses the table file and implements it into a table object 
in order for maniputation of data and then updates the table file when done.

*/


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class RaSQL_Table
{
	private:

		//debug variable
		bool isDebug = false;

		int schema_attr_count;
		int table_entries;
		int where_entries;

		int where_match_count;
		int* where_matches;

		string table_filename;
		string schema_input;

		string* table_schema;
		string* table_schema_w_type;
		string* table_schema_w_pre;
		string* full_table_schema;

		string** current_table;
		string** selectTable;//used in select
		string** whereTable;//used in where
		string** deleteTable;//used in delete_vals

		//helper functions
		int countSchemaAttr(string schemaLine);

		//gets the schema and fills full_table_schema and table_schema
		//returns schema Attr count
		bool getSchema( string schema_line );

		bool makeCurrentTable();
		int getSchemaIndex(string possible_attr);
		bool whereMatch(string* check_entry, string where_key, string expressionStr, string where_value);

		//file maintenance
		bool update_table_file();

	public:
		//Normal single table constructor
		RaSQL_Table(string table_name, string currentDB, bool debugger);

		//Multitable join constructor
		RaSQL_Table(RaSQL_Table* t1, string t1_alias, RaSQL_Table* t2, string t2_alias,
						string join_type, string w_key, string w_expression, string w_value);

		bool insert(string* values);
		int delete_vals(string where_key, string expressionStr, string where_value);
		int update_table(string set_key, string set_value, 
							string where_key, string expressionStr, string where_value);

		//can call eachother --"FWGOS"--
		//bool where(string where_key, string expressionStr, string where_value);
		bool where(string** expression_2d_array, int expression_count);
		bool select( string* select_vals, int select_val_count );

		bool set_table_name();
		bool get_table_name();

		//schema functionality
		bool read_schema();
		bool write_schema();
		bool add_schema_attr();
		bool remove_schema_attr();

		void debugMode( bool toDeOrNotToDe );

		void addAttrPrefix(string table_name);

		//update table file
		bool commit();

		
		
};