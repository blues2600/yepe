/**************************************************************************

                        ���PE������Ŀ¼��Ϣ

**************************************************************************/


#include			<stdio.h>

void print_data_dir(FILE* pFile,int dword_)
{
	printf_s("\n\n\n\t\tĿ¼\t\tRVA\t\tSIZE");
	printf_s("\n\t\t--------------------------------------------");

	fread(&dword_, 4, 1, pFile);					//����Ŀ¼
	printf_s("\n\t\t����Ŀ¼\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//����Ŀ¼
	printf_s("\n\t\t����Ŀ¼\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//��ԴĿ¼
	printf_s("\n\t\t��ԴĿ¼\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//�쳣Ŀ¼
	printf_s("\n\t\t�쳣Ŀ¼\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//֤��Ŀ¼
	printf_s("\n\t\t֤��Ŀ¼\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//��ַ�ض�λĿ¼
	printf_s("\n\t\t��ַ�ض�λ\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//����Ŀ¼
	printf_s("\n\t\t����Ŀ¼\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//Architecture
	printf_s("\n\t\tArchitecture\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//ȫ��ָ��Ŀ¼
	printf_s("\n\t\tȫ��ָ��\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//�̱߳��ش洢Ŀ¼
	printf_s("\n\t\t�̱߳��ش洢\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//��������Ŀ¼
	printf_s("\n\t\t��������\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//�󶨵���Ŀ¼
	printf_s("\n\t\t�󶨵���\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//IATĿ¼
	printf_s("\n\t\t�����ַIAT\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//�ӳٵ���������
	printf_s("\n\t\t�ӳٵ���\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//COM������
	printf_s("\n\t\tCOM������\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//����Ŀ¼
	printf_s("\n\t\t����Ŀ¼\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);
}