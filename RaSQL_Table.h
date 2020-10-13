
#include <string>

using namespace std;

class RaSQL_Table
{
	private:
		
		string name;

		string* table_schema;

	public:
		RaSQL_Table();

		bool set_table_name();
		bool get_table_name();

		bool read_schema();
		bool write_schema();
		bool add_schema_attr();
		bool remove_schema_attr();
		
};