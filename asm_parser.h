
#define ROWS 100
#define COLS 255

/**
* Reads the .asm file into 2D character array.
*   @param filename 
*   @param program array storing program.
*   @return succes/error code.
*/
int read_asm_file(char* filename, char program [ROWS][COLS]);

/**
 * Parsing the prorgam instructtion to binary equivalent text form
 * @param  instr pointer to line in the 2D program array
 * @param instr_bin_str pointer to binary equivalent line
 * @return success/failure code.
*/
int parse_instruction(char* instr, char* instr_bin_str);

/**
 * Parsing the register string into the register number
 * @param reg_num takes register string.
 * @param instr_bin_str binary string to which the output will be written
 * @return error/succes code 
 */
int parse_reg(char* reg_num, char* instr_bin_str) ;

/* add additional helper functions to support other instructions */

/**
 * Converts binary string to their hexadecimal value
 * @param instr_bin_str character string to be converted
 * @return hexadecimal value
*/
unsigned short int str_to_bin (char* instr_bin_str) ;

/**
 * Writes the hexcode to an object file
 * @param filename output filename
 * @param program_bin hexvalues
 * @param N line number 
 * @return succes/error code
*/
int write_obj_file(char* filename, unsigned short int program_bin[ROWS],unsigned short int N) ;

/**
*   Helper function to tokenize string.
*   @param argString input string to be tokenized.
*   @param argV character array pointer to store all the tokens.
*   @param delimiter character based on which to spilt the string.
*   @return count of tokens generated
*/
int tokenize(char * argString, char ** argV, const char * delimiter);
