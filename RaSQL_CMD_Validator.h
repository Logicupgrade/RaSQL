
#include <string>

using namespace std;

class RaSQL_CMD_Validator
{
    private:
            string RaSQL_DB_commands[3] = {"create","drop","use"};
            string RaSQL_Table_commands[4] = {"create","drop","alter","select"};
            string RaSQL_Table_Attributes[4] = {"int","char","varchar","float"};

            //TODO:specific error messages

            //default error message
            string syntax_error_response = "Sorry, entered wrong syntax";

            int valid_commands = 0;

    public:
    		RaSQL_CMD_Validator();
    		get_cmd_count();
    		
    		//validate DB Commands
    		validate_DB_create();
    		validate_DB_drop();
    		validate_DB_use();

    		//validate Table Commands
    		validate_Table_create();
    		validate_Table_drop();
    		validate_Table_alter();
    		validate_Table_select();
};
