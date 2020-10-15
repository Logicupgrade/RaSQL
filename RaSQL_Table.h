
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class RaSQL_Table
{
	private:
		int schema_attr_count;
		int table_entries;

		string table_filename;
		string schema_input;

		string* table_schema;

		string** current_table;
		string** selectTable;//used in select
		string** whereTable;//used in where
		string** deleteTable;//used in delete_vals

		//helper functions
		int countSchemaAttr(string schemaLine);
		bool makeCurrentTable();
		bool fillCurrentTable();
		int getSchemaIndex(string possible_attr);

		//file maintenance
		bool update_table_file();

	public:
		RaSQL_Table(string table_name, string currentDB);

		bool insert(string* values);
		string* delete_vals(bool expression);
		bool update_table(string set_key, string set_value, 
							string where_key, string where_value);

		//can call eachother --"FWGOS"--
		string* where(bool expression);
		string* select(string attr);

		bool set_table_name();
		bool get_table_name();

		//schema functionality
		bool read_schema();
		bool write_schema();
		bool add_schema_attr();
		bool remove_schema_attr();

		
		
};