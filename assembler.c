
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv)
{

	if(argc<2)
	{
		printf("error1: ussage: %s <assembly_file.asm> \n",argv[0]);
		return 0;
	}
	char* filename = argv[1] ;					// name of ASM file
	char  program [ROWS][COLS] ; 			// ASM file line-by-line
	char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
	unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)

	for(int i=0;i<ROWS;i++)
	{
		for(int j=0;j<COLS;j++)program[i][j]='\0';
		for(int j=0;j<17;j++) program_bin_str[i][j]='\0';
		program_bin[i] = 0;
	}

	if(read_asm_file(filename,program)==2)printf("error 2:read_asmfile() failed\n");
	
	unsigned short int line=0;
	while(program[line][0]!='\0')
	{
		if(parse_instruction(program[line],program_bin_str[line])==3)
		{
			printf("error 3: parse_instruction failed\n");
			break;
		}
		line++;
	}

	for(int i=0;i<line;i++) {
		program_bin[i] = str_to_bin(program_bin_str[i]);
		// printf("0x%X\t",program_bin[i]);
	}
	int N=strlen(filename);

	filename[N-3]='o';
	filename[N-2]='b';
	filename[N-1]='j';

	if(write_obj_file(filename,program_bin,line)==6)
	{
		printf("error 6: object file not found\n");
	}
	printf("\nFile Succesfully assembled. Use following command to view the contents \n>hexdump %s\n\n",filename);

	return 0;
}
