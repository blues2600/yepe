/**************************************************************************

						输出PE的section信息

**************************************************************************/

#include			<stdio.h>

void print_section(FILE* pFile, int dword_, short int number_of_section, char* section_name)
{
	printf_s("\n\n\n\t\t节\t\tRVA\t\tSizeOfRawData");
	printf_s("\n\t\t---------------------------------------------");

	for (short int i = 0; i < number_of_section; i++) {

		memset(section_name, '\0', 9);

		fread(section_name, 8, 1, pFile);					//节名称
		printf_s("\n%20s", section_name);

		fseek(pFile, 4L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);				//节地址
		printf_s("\t  %10X", dword_);

		fread(&dword_, sizeof(int), 1, pFile);				//SizeOfRawData
		printf_s("\t\t%X", dword_);

		int k = sizeof(int) * 5;
		fseek(pFile, k, SEEK_CUR);
	}

	printf_s("\n\n");
}