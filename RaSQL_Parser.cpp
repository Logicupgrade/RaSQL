
#include "RaSQL_Parser.h"

// std::string s = "scott>=tiger";
// std::string delimiter = ">=";
// std::string token = s.substr(0, s.find(delimiter)); // token is "scott"

RaSQL_Parser::RaSQL_Parser()
{
	//default constructor
}

bool RaSQL_Parser::parse(string cmd_str)
{
	string delim1 = " ";
	string delim2 = ";";

	string command = cmd_str.substr(0,cmd_str.find(delim1));

	cout<<"First Command: "<<command<<endl;
	return true;
}

