

#include <string>

#include "RaSQL_Table.h"

class RaSQL_DB
{
	private:
		string name;
		RaSQL_Table* table_list;
		int table_count;

	public:
		RaSQL_DB(string name);
};