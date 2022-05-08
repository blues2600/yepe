/**************************************************************************

							** 说明 **

						* yxPE是一个PE头解析工具
						* 作者 yx
						* 创建日期 2022年4月26日

**************************************************************************/


#include			<stdio.h>
#include			<stdlib.h>
#include			<windows.h>

#define				PATH_MAX			256						//文件路径最大字节数

typedef unsigned long long ULONGLONG;

void TimetToFileTime(time_t t, LPFILETIME pft);					//时间戳转换
void print_data_dir(FILE* pFile, int dword_);					//输出PE数据目录
void print_section(FILE*, int, short int, char*);				//输出PE的section信息


int main(int argc, char* argv[])
{
	char			file_name[PATH_MAX] = { 0 };
	FILE*			pFile = NULL;
	char			section_name[9] = { '0' };
	short int		number_of_section = 0;
	fpos_t			pos = 0;									//内容指针
	int				e_lfanew = 0;								//dos头e_lfanew字段
	char			ascii_[3] = { '0' };						//将二进制数据作为字符串输出
	char			byte_ = 0;									//PE字段值，1个字节
	short int		word_ = 0;									//PE字段值，2个字节
	int				dword_ = 0;									//PE字段值，4个字节
	ULONGLONG		ulonglong_ = 0;								//PE字段值，unsigned long long
	short	int		machine = 0;								//PE运行平台


	// 处理命令行
	if (argc != 2) {
		printf("\n不正确的命令格式。\n");
		printf("\n命令格式参考:\n");
		printf("\tyxPE  FileName.exe\n");
		return 0;
	}
	else {
		if (strcpy_s(file_name, PATH_MAX - 1, argv[1])) {
			printf("\n未知错误，程序结束。\n");
			exit(1);
		}
	}

	// 打开文件
	errno_t err = fopen_s(&pFile, file_name, "rb");
	if (err) {
		printf_s("The file was not opened\n");
		return -1;
	}

	// 读取PE信息
	fread(ascii_, 1, 2, pFile);									//读取magic number
	ascii_[2] = 0;
	printf_s("\n文件 %s 的PE信息：\n", file_name);
	printf_s("\n\n%30s : Magic number", ascii_);

	pos = 0x3c;													//读取e_lfanew字段的值
	if (fsetpos(pFile, &pos) != 0) {
		perror("fsetpos error");
		return -1;
	}

	fread(&dword_, sizeof(int), 1, pFile);
	pos = dword_;												//移动到e_lfanew指向的位置
	if (fsetpos(pFile, &pos) != 0) {
		perror("fsetpos error");
		return -1;
	}

	fread(ascii_, 1, 2, pFile);									//读取PE签名
	ascii_[2] = 0;
	printf("\n%30s : PE签名", ascii_);

	fseek(pFile, 2L, SEEK_CUR);

	fread(&word_, sizeof(short int), 1, pFile);					//机器平台
	printf_s("\n%30hX : 机器平台", word_);
	machine = word_;


	fread(&word_, sizeof(short int), 1, pFile);					//节表数量
	printf_s("\n%30hd : 节表数量", word_);
	number_of_section = word_;

	fread(&dword_, sizeof(int), 1, pFile);						//编译时间 

	// 时间戳转换
	time_t		TimeDateStamp = (time_t)dword_;
	FILETIME	fileTime = { 0 };
	SYSTEMTIME	systemTime = { 0 };
	TimetToFileTime(TimeDateStamp, &fileTime);
	FileTimeToSystemTime(&fileTime, &systemTime);
	printf_s("\n\t\t\t编译于%hd年%hd月%hd日%hd:%02hd:%hd",
		systemTime.wYear, systemTime.wMonth,
		systemTime.wDay, systemTime.wHour,
		systemTime.wMinute, systemTime.wSecond);


	fseek(pFile, 8L, SEEK_CUR);

	fread(&word_, sizeof(short int), 1, pFile);					//选项头大小
	printf_s("\n%30hX : 选项头大小", word_);

	fread(&word_, sizeof(short int), 1, pFile);					//文件属性
	printf_s("\n%30hX : 文件特征", word_);


	/*		进入IMAGE_OPTIONAL_HEADER
			区分不同的体系结构和指令集		*/



	if (machine == 0xFFFF8664) {								// PE 是 x86 64bit

		fread(&word_, sizeof(short int), 1, pFile);				//magic
		switch (word_) {
		case 0x20b:
			printf_s("\n%30hX : PE32+", word_);
			break;
		case 0x10b:
			printf_s("\n%30hX : PE32", word_);
			break;
		default:
			printf_s("\n无法识别的文件类型。");
			break;
		}

		fread(&byte_, sizeof(char), 1, pFile);					//链接器
		printf_s("\n%30d : 链接器主版本", byte_);
		fseek(pFile, 1L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);					//代码节大小
		printf_s("\n%30X : 代码节大小", dword_);
		fseek(pFile, 8L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);					//入口点
		printf_s("\n%30X : 入口点", dword_);

		fread(&dword_, sizeof(int), 1, pFile);					//代码节起始地址
		printf_s("\n%30X : 代码节地址", dword_);

		fread(&ulonglong_, sizeof(unsigned long long), 1, pFile);	//进程基址
		printf_s("\n%30llX : 进程基址", ulonglong_);

		fread(&dword_, sizeof(int), 1, pFile);					//节数据内存对齐
		printf_s("\n%30X : 节数据内存对齐", dword_);

		fread(&dword_, sizeof(int), 1, pFile);					//文件对齐
		printf_s("\n%30X : 文件对齐", dword_);

		fread(&word_, sizeof(short int), 1, pFile);				//操作系统版本
		printf_s("\n%30d : 操作系统主版本", word_);
		fseek(pFile, 2L, SEEK_CUR);

		fread(&word_, sizeof(short int), 1, pFile);				//映像版本
		printf_s("\n%30d : 映像主版本", word_);
		fseek(pFile, 2L, SEEK_CUR);

		fread(&word_, sizeof(short int), 1, pFile);				//子系统版本
		printf_s("\n%30d : 子系统主版本", word_);
		fseek(pFile, 10L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);					//size of headers
		printf_s("\n%30X : PE头部大小", dword_);

		fread(&dword_, sizeof(int), 1, pFile);					//校验和
		printf_s("\n%30X : 校验和", dword_);

		fread(&word_, sizeof(short int), 1, pFile);				//子系统
		switch (word_) {
		case 2:
			printf_s("\n%30d : GUI子系统", word_);
			break;
		case 3:
			printf_s("\n%30d : CUI子系统)", word_);
		default:
			printf_s("\n%30d : 其他子系统", word_);
			break;
		}

		fread(&word_, sizeof(short int), 1, pFile);				//DLL特征
		printf_s("\n%30hX : DLL特征", word_);

		long k = sizeof(ULONGLONG) * 4 + 4;
		fseek(pFile, k, SEEK_CUR);

		fseek(pFile, 4L, SEEK_CUR);

		// 处理数据目录
		print_data_dir(pFile, dword_);

		// 处理section信息
		print_section(pFile, dword_, number_of_section, section_name);
	}

	else if (machine == 0x14c) {								//PE 是 x86 32bit
		fread(&word_, sizeof(short int), 1, pFile);				//magic
		switch (word_) {
		case 0x20b:
			printf_s("\n%30hX : PE32+", word_);
			break;
		case 0x10b:
			printf_s("\n%30hX : PE32", word_);
			break;
		default:
			printf_s("\n无法识别的文件类型。");
			break;
		}

		fread(&byte_, sizeof(char), 1, pFile);					//链接器
		printf_s("\n%30d : 链接器主版本", byte_);

		fseek(pFile, 1L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);					//代码节大小
		printf_s("\n%30X : 代码节大小", dword_);

		fseek(pFile, 8L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);					//入口点
		printf_s("\n%30X : 入口点", dword_);

		fread(&dword_, sizeof(int), 1, pFile);					//代码节地址
		printf_s("\n%30X : 代码节地址", dword_);

		fseek(pFile, 4L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);					//进程基址
		printf_s("\n%30X : 进程基址", dword_);

		fread(&dword_, sizeof(int), 1, pFile);					//节数据内存对齐
		printf_s("\n%30X : 节数据内存对齐", dword_);

		fread(&dword_, sizeof(int), 1, pFile);					//文件对齐
		printf_s("\n%30X : 文件对齐", dword_);

		fread(&word_, sizeof(short int), 1, pFile);				//操作系统主版本
		printf_s("\n%30X : 操作系统主版本", word_);

		fseek(pFile, 2L, SEEK_CUR);

		fread(&word_, sizeof(short int), 1, pFile);				//映像主版本
		printf_s("\n%30X : 映像主版本", word_);

		fseek(pFile, 2L, SEEK_CUR);

		fread(&word_, sizeof(short int), 1, pFile);				//子系统主版本
		printf_s("\n%30X : 子系统主版本", word_);

		fseek(pFile, 10L, SEEK_CUR);

		fread(&dword_, sizeof(int), 1, pFile);					//size of headers
		printf_s("\n%30X : PE头部大小", dword_);

		fread(&dword_, sizeof(int), 1, pFile);					//校验和
		printf_s("\n%30X : 校验和", dword_);

		fread(&word_, sizeof(short int), 1, pFile);				//子系统
		switch (word_) {
		case 2:
			printf_s("\n%30d : GUI子系统", word_);
			break;
		case 3:
			printf_s("\n%30d : CUI子系统", word_);
		default:
			printf_s("\n%30d : 其他子系统", word_);
			break;
		}

		fread(&word_, sizeof(short int), 1, pFile);				//DLL特征
		printf_s("\n%30hX : DLL特征", word_);

		fseek(pFile, 24L, SEEK_CUR);

		// 处理数据目录
		print_data_dir(pFile, dword_);

		// 处理section信息
		print_section(pFile, dword_, number_of_section, section_name);
	}
	else
		printf_s("\n无法识别的体系结构和指令集。");


	fclose(pFile);
	pFile = NULL;

	return 0;
}


