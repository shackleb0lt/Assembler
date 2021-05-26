

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

/**
*   Helper function to tokenize string.
*   @param argString input string to be tokenized.
*   @param argV character array pointer to store all the tokens.
*   @param delimiter character based on which to spilt the string.
*   @return count of tokens generated
*/
int tokenize(char * argString, char ** argV, const char * delimiter)
{
	int index = 0;
    char * tokens =  strtok(argString, delimiter);
	while(tokens != NULL) {
		argV[index] = tokens;
		tokens = strtok(NULL, delimiter);
		index++;
	}
	return index;
}

/**
* Reads the .asm file into 2D character array.
*   @param filename 
*   @param program array storing program.
*   @return succes/error code.
*/
int read_asm_file(char* filename, char program[ROWS][COLS] )
{
    FILE* fptr = fopen(filename,"r");

    if(fptr == NULL) return 2;

    char buffer[256];
    char * my_argv[20];
    char * my_argv_com[2];
    int my_argc;

    int line_no=1;
    while(fgets(buffer,256,fptr))
    {
        buffer[strlen(buffer)-1]='\0';      //Removing the newline character
        my_argc = tokenize(buffer,my_argv_com,";");

        if(my_argc!=0) my_argc = tokenize(my_argv_com[0],my_argv," ");
        else continue;

        for(int i=0;i<my_argc;i++)
        {
            strcat(program[line_no-1],my_argv[i]);
            strcat(program[line_no-1]," ");
        }
        line_no++;
    }
    fclose(fptr);
    return 0;
}

/**
 * Parsing the prorgam instructtion to binary equivalent text form.
 * @param  instr pointer to line in the 2D program array
 * @param instr_bin_str pointer to binary equivalent line
 * @return success/failure code.
*/
int parse_instruction 	(char* instr, char* instr_bin_str)
{
    char * my_argv[5];
    int my_argc;

    my_argc = tokenize(instr,my_argv," ");

    if(my_argc!=4) return 3; 
    // printf("%d\n",my_argc);
    if(strcmp(my_argv[0],"ADD")==0)
    {
        if(my_argv[3][0]=='#')
        {
            strcat(instr_bin_str,"0001");
            if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
            if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
            strcat(instr_bin_str,"1");
            parse_reg(my_argv[3],instr_bin_str);
            
        }
        else {
            strcat(instr_bin_str,"0001");
            if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
            if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
            strcat(instr_bin_str,"000");
            if(parse_reg(my_argv[3],instr_bin_str)==4)return 3;
        }
    }
    else if(strcmp(my_argv[0],"MUL")==0)
    {
        strcat(instr_bin_str,"0001");
        if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
        if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
        strcat(instr_bin_str,"001");
        if(parse_reg(my_argv[3],instr_bin_str)==4)return 3;
    }
    else if(strcmp(my_argv[0],"SUB")==0)
    {
        strcat(instr_bin_str,"0001");
        if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
        if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
        strcat(instr_bin_str,"010");
        if(parse_reg(my_argv[3],instr_bin_str)==4)return 3;
    }
    else if(strcmp(my_argv[0],"DIV")==0)
    {
        strcat(instr_bin_str,"0001");
        if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
        if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
        strcat(instr_bin_str,"011");
        if(parse_reg(my_argv[3],instr_bin_str)==4)return 3;
    }
    else if(strcmp(my_argv[0],"OR")==0)
    {
        strcat(instr_bin_str,"0101");
        if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
        if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
        strcat(instr_bin_str,"010");
        if(parse_reg(my_argv[3],instr_bin_str)==4)return 3;
    }
    else if(strcmp(my_argv[0],"AND")==0)
    {
        if(my_argv[3][0]=='#'){
            strcat(instr_bin_str,"0101");
            if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
            if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
            strcat(instr_bin_str,"1");
            parse_reg(my_argv[3],instr_bin_str);
            // printf("%s\t%s",my_argv[3],instr_bin_str);
        }
        else{
            strcat(instr_bin_str,"0101");
            if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
            if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
            strcat(instr_bin_str,"000");
            if(parse_reg(my_argv[3],instr_bin_str)==4)return 3;
        }
    }
    else if(strcmp(my_argv[0],"XOR")==0)
    {
        strcat(instr_bin_str,"0101");
        if(parse_reg(my_argv[1],instr_bin_str)==4)return 3;
        if(parse_reg(my_argv[2],instr_bin_str)==4)return 3;
        strcat(instr_bin_str,"011");
        if(parse_reg(my_argv[3],instr_bin_str)==4)return 3;
    }
    return 0;
}

/**
 * Parsing the register string into the register number
 * @param reg_num takes register string.
 * @param instr_bin_str binary string to which the output will be written
 * @return error/succes code 
 */
int parse_reg(char* reg_num, char* instr_bin_str)
{
    if(reg_num[0]=='#')
    {
        reg_num[0]='0';
        unsigned short int n = strtol(reg_num,NULL,10);
        char binaryNum[6]={'0','0','0','0','0'};
    
        // counter for binary array
        int i = 0;
        while (n > 0) {
            binaryNum[4-i] = '0' + (n % 2);
            n = n / 2;
            i++;
        }
        binaryNum[5]='\0';
        strcat(instr_bin_str,binaryNum);
        return 0;
    }
    if(reg_num[0]!='R')return 4;
    reg_num[0]='0';
    // if(reg_num[strlen(reg_num)-1]==',')reg_num[strlen(reg_num)-1]='\0';

    int rnum = strtol(reg_num,NULL,10);
    switch (rnum)
    {
        case 0:
            strcat(instr_bin_str,"000");
            break;
        case 1:
            strcat(instr_bin_str,"001");
            break;
        case 2:
            strcat(instr_bin_str,"010");
            break;
        case 3:
            strcat(instr_bin_str,"011");
            break;
        case 4:
            strcat(instr_bin_str,"100");
            break;
        case 5:
            strcat(instr_bin_str,"101");
            break;
        case 6:
            strcat(instr_bin_str,"110");
            break;
        case 7:
            strcat(instr_bin_str,"111");
            break;
        default:
            return 4;
            break;
    }
    
    return 0;
}

/**
 * Converts binary string to their hexadecimal value
 * @param instr_bin_str character string to be converted
 * @return hexadecimal value
*/
unsigned short int str_to_bin (char* instr_bin_str)
{
    unsigned short int result = 0;
    for(int i=0;i<16;i++)
    {
        result *= 2;
        result += instr_bin_str[i] - '0';
        
    }
    return result;
}

/**
 * Writes the hexcode to an object file
 * @param filename output filename
 * @param program_bin hexvalues
 * @return succes/error code
*/
int write_obj_file(char* filename, unsigned short int program_bin[ROWS],unsigned short int N) 
{
    // printf("%s\n",filename);
    unsigned short int code = 0xCADE; 
    unsigned short int start = 0;
    
    FILE * fptr = fopen(filename,"wb");
    if(fptr == NULL ) return 6;

    fwrite(&code,sizeof(code),1,fptr);
    fwrite(&start,sizeof(start),1,fptr);
    fwrite(&N,sizeof(N),1,fptr);

    fwrite(program_bin,sizeof(unsigned short int),N,fptr);
    
    fclose(fptr);
    return 0;
}
