/**************************************************************************

                        输出PE的数据目录信息

**************************************************************************/


#include			<stdio.h>

void print_data_dir(FILE* pFile,int dword_)
{
	printf_s("\n\n\n\t\t目录\t\tRVA\t\tSIZE");
	printf_s("\n\t\t--------------------------------------------");

	fread(&dword_, 4, 1, pFile);					//导出目录
	printf_s("\n\t\t导出目录\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//导入目录
	printf_s("\n\t\t导入目录\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//资源目录
	printf_s("\n\t\t资源目录\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//异常目录
	printf_s("\n\t\t异常目录\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//证书目录
	printf_s("\n\t\t证书目录\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//基址重定位目录
	printf_s("\n\t\t基址重定位\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//调试目录
	printf_s("\n\t\t调试目录\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//Architecture
	printf_s("\n\t\tArchitecture\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//全局指针目录
	printf_s("\n\t\t全局指针\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//线程本地存储目录
	printf_s("\n\t\t线程本地存储\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//加载配置目录
	printf_s("\n\t\t加载配置\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//绑定导入目录
	printf_s("\n\t\t绑定导入\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//IAT目录
	printf_s("\n\t\t导入地址IAT\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//延迟导入描述符
	printf_s("\n\t\t延迟导入\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//COM描述符
	printf_s("\n\t\tCOM描述符\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);

	fread(&dword_, 4, 1, pFile);					//保留目录
	printf_s("\n\t\t保留目录\t%X", dword_);
	fread(&dword_, 4, 1, pFile);
	printf_s("\t\t%X", dword_);
}