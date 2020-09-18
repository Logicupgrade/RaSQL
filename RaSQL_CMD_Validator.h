
#include <string>

using namespace std;

class RaSQL_CMD_Validator
{
    private:
            string RaSQL_DB_commands[3] = {"create","drop","use"};
            string RaSQL_Table_commands[4] = {"create","drop","alter","select"};
            string RaSQL_Table_Attributes[4] = {"int","char","varchar","float"};
};
