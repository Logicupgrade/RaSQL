
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class RaSQL_Table
{
	private:
		string table_filename;
		string* table_schema;
		int schema_attr_count;

		string** table;
		string** selectTable;//used in select
		string** whereTable;//used in where
		string** deleteTable;//used in delete_vals

		//helper functions
		int countSchemaAttr(string schemaLine);
		int countTableEntries();
		bool makeEmptyTable();

	public:
		RaSQL_Table(string table_name, string currentDB);

		bool insert(string* values);
		string* delete_vals(bool expression);

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

		bool update_table_file();
		
};