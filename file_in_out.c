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

	printf("������Ҫ��ȡ��Դ�ļ�·�����磺E:\\���ݽṹ���㷨ʵ��\\Data_input.txt����\n");
	scanf("%s", sourceName);
	in = fopen(sourceName, "r+");
	if (in == NULL)                                    //�ж�Դ�ļ��Ƿ��
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

	printf("������Ҫд���Դ�ļ�·�����磺E:\\���ݽṹ���㷨ʵ��\\Data_output.txt����\n");
	scanf("%s", StatisticName);
	out = fopen(StatisticName, "w+");
	if (out == NULL)                                        //�ж�Ŀ���ļ��Ƿ��
	{
		printf("Cannot open this file\n");
		exit(0);
	}
	printf("\n");
	return out;
}

void read_write(int *in, int *out)
{

	printf("��ѡ��д��Ŀ���ļ������ݵ���Դ��\nͨ����ȡ���ļ�д��������1��ͨ������̨����������2:\n");      //ѡ���ļ���д����Դ
	int way_num;
	scanf("%d", &way_num);
	char ch;

	switch (way_num)
	{
	case 1:
		//ͨ��Դ�ļ�����ļ����ݵ��ļ��ʹ���
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
		printf("������Ҫд��Ŀ���ļ������ݣ�\n");              //ͨ������̨���������д��Ŀ���ļ�
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

