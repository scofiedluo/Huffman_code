#include "Header.h"
#include"code_output.h"
#include"huffman.h"
#include"LINK_list.h"
#include"main.h"
#include"merge_sort.h"
//int main()
FILE *in_open()
{
	FILE *in;
	char sourceName[100];

	printf("请输入要读取的源文件路径（如：E:\\数据结构与算法实验\\Data_input.txt）：\n");
	scanf("%s", sourceName);
	in = fopen(sourceName, "r+");
	if (in == NULL)                                    //判断源文件是否打开
	{
		printf("Cannot open this file\n");
		exit(0);
	}
	printf("\n");
	return in;
}

FILE *out_open()
{
	FILE *out;
	char StatisticName[100];

	printf("请输入要写入的源文件路径（如：E:\\数据结构与算法实验\\Data_output.txt）：\n");
	scanf("%s", StatisticName);
	out = fopen(StatisticName, "w+");
	if (out == NULL)                                        //判断目标文件是否打开
	{
		printf("Cannot open this file\n");
		exit(0);
	}
	printf("\n");
	return out;
}

void read_write(int *in, int *out)
{

	printf("请选择写入目标文件的内容的来源：\n通过读取的文件写入请输入1，通过控制台输入请输入2:\n");      //选择文件的写入来源
	int way_num;
	scanf("%d", &way_num);
	char ch;

	switch (way_num)
	{
	case 1:
		//通过源文件输出文件内容到文件和窗口
		ch = fgetc(in);
		while (ch != EOF)
		{
			//putchar(ch);
			fputc(ch, out);
			printf("\n");
			printf("%c", &ch);
			ch = fgetc(in);
		}
		break;
	case 2:
		printf("请输入要写入目标文件的内容：\n");              //通过控制台输入的内容写到目标文件
		char con_in[100];
		scanf("%s", con_in);
		fputs(con_in, out);
		break;
	}
	printf("\n");

	fclose(in);
	fclose(out);
	//return 0;
}

