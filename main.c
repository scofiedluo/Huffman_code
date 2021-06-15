#include "Header.h"
#include"code_output.h"
#include"huffman.h"
#include"LINK_list.h"
#include"main.h"
#include"merge_sort.h"
#define FILENAME_LEN_MAX 100

//打印帮助信息
void printHelp(void) {
	//TODO
	printf("该功能等待完善\n");
}

bool chooseMode(bool cls) {
	bool mode = true;
	char ch;
	if (cls) {
		system("cls");
	}
	rewind(stdin);
	scanf("%c", &ch);
	switch (ch)
	{
	case '1':
		return true;
	case '2':  
		return false;
	default:
		//printf("请输入“1”或“2”以选择模式");
		return chooseMode(false);
		break;
	}

}

int main(int argc, char *argv[]) {
	listHead *list_head = NULL;
	huffmanNode *huffman_head = NULL;
	tfListHead *tf_list_head = NULL;
	bool mode = true;  //true for 空间优先，false for 时间优先
	int func_tag = 1;
	int exit_tag;
	char input_filename[FILENAME_LEN_MAX] = "test.txt";
	char compressed_filename[FILENAME_LEN_MAX] = "compressed.dat";
	char target_filename[FILENAME_LEN_MAX] = "uncompressed.txt";
	char list_filename[FILENAME_LEN_MAX] = "list.tf";  //term frequency
	char temp[FILENAME_LEN_MAX] = "test.txt";


	while (true) {
		func_tag = chooseFunction(true);
		switch (func_tag)
		{
		case 1:  //	1.从文本文件统计词频
			system("cls");
			printf("请输入要统计词频的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
			printf("<(如：E:\\数据结构与算法实验\\Data_input.txt)%s>:", input_filename);

			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("文件路径不合法。\n请重新输入要统计词频的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(input_filename, temp, FILENAME_LEN_MAX);
			}
			list_head = count_from_file(input_filename);
			if (NULL == list_head) {
				printf("统计失败。");
				break;
			}
			else {
				sort_list(list_head, false);
				huffman_head = build_tree(list_head);
				if (NULL == huffman_head) {
					printf("建立哈夫曼树失败");
					break;
				}
				print_freq(list_head);
				drop_tf_list(tf_list_head);
				free(tf_list_head);
				tf_list_head = NULL;
			}
			break;
		case 2:  //2.打印树形（按层次遍历的方式）
			if (NULL == huffman_head) {
				printf("还没有建哈夫曼树哦，请通过统计词频来建立哈夫曼树\n");
				printf("或者通过读取.tf文件来建立哈夫曼树\n");
				break;
			}
			else {
				print_huffman_tree(huffman_head);
			}
			break;
		case 3:  //打印码本
			if (NULL == huffman_head) {
				printf("还没有建哈夫曼树哦，请通过统计词频来建立哈夫曼树\n");
				printf("或者通过读取.tf文件来建立哈夫曼树\n");
				break;
			}
			if (NULL == list_head) {
				printf("还没有给出词频链表哦，请通过统计词频来建立词频链表\n");
				printf("或者通过读取.tf文件来建立词频链表\n");
				break;
			}
			else {
				print_codebook(huffman_head, list_head);
			}
			break;
		case 4:  //压缩文件
			mode = chooseMode(true);
			if (NULL == huffman_head) {
				printf("还没有建哈夫曼树哦，请通过统计词频来建立哈夫曼树\n");
				printf("或者通过读取.tf文件来建立哈夫曼树\n");
				break;
			}
			if (NULL == list_head) {
				printf("还没有给出词频链表哦，请通过统计词频来建立词频链表\n");
				printf("或者通过读取.tf文件来建立词频链表\n");
				break;
			}
			printf("请输入要压缩的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", input_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("文件路径不合法。\n请重新输入要压缩的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(input_filename, temp, FILENAME_LEN_MAX);
			}

			printf("请输入要保存到的文件的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", compressed_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("文件路径不合法。\n请重新输入要保存到的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(compressed_filename, temp, FILENAME_LEN_MAX);
			}

			if (mode) {
				encode_and_save(huffman_head, compressed_filename, input_filename);
			}
			else {
				if (NULL == tf_list_head) {
					tf_list_head = create_tf_list(list_head, huffman_head);
				}
				encode_and_save_tf(tf_list_head, compressed_filename, input_filename);
			}
			printf("压缩成功");
			break;
		case 5:  //解压文件
			if (NULL == huffman_head) {
				printf("还没有建哈夫曼树哦，请通过统计词频来建立哈夫曼树\n");
				printf("或者通过读取.tf文件来建立哈夫曼树");
				break;
			}

			printf("请输入要解压缩的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", compressed_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("文件路径不合法。\n请重新输入要解压缩的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(compressed_filename, temp, FILENAME_LEN_MAX);
			}

			printf("请输入解压后输出的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", target_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("文件路径不合法。\n请重新输入解压后输出的文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(target_filename, temp, FILENAME_LEN_MAX);
			}

			decode_from_file(huffman_head, compressed_filename, target_filename);

			break;
		case 6:  //	保存频率信息
			if (NULL == list_head) {
				printf("还没有给出词频链表哦，请通过统计词频来建立词频链表\n");
				printf("或者通过读取.tf文件来建立词频链表\n");
				break;
			}

			printf("请输入要保存频率信息的文件名(路径)(%d字符以内且以.tf结尾)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", list_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp) || !filenameEndsWith(temp, "tf")) {
					printf("文件路径不合法。\n请重新输入要保存频率信息的文件名(路径)(%d字符以内且以.tf结尾)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(list_filename, temp, FILENAME_LEN_MAX);
			}

			save_list(list_head, list_filename);
			break;

		case 7:  //读取码本信息
			printf("请输入保存频率信息的文件名(路径)(%d字符以内且以.tf结尾)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", list_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp) || !filenameEndsWith(temp, "tf")) {
					printf("文件路径不合法。\n请重新输入保存频率信息的文件名(路径)(%d字符以内且以.tf结尾)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(list_filename, temp, FILENAME_LEN_MAX);
			}

			list_head = create_list_from_file(list_head, list_filename);
			if (NULL == list_head) {
				printf("统计词频失败");
				break;
			}
			drop_huffman_tree(huffman_head);
			huffman_head = build_tree(list_head);
			if (NULL == huffman_head) {
				printf("建立哈夫曼树失败");
				break;
			}
			print_freq(list_head);
			drop_tf_list(tf_list_head);
			free(tf_list_head);
			tf_list_head = NULL;
			break;
		case 8:  //printf("8.比较两文件是否相同\n\n");
			printf("请输入第一个文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", input_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("文件路径不合法。\n请重新输入第一个文件名(路径)(%d字符以内且以.tf结尾)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(input_filename, temp, FILENAME_LEN_MAX);
			}

			printf("请输入第二个文件名(路径)(%d字符以内)：\n", FILENAME_LEN_MAX);
			printf("<%s>:", target_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("文件路径不合法。\n请重新输入第二个文件名(路径)(%d字符以内且以.tf结尾)：\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(target_filename, temp, FILENAME_LEN_MAX);
			}

			if (file_compare(input_filename, target_filename)) {
				printf("\n两文件相同\n");
			}
			else {
				printf("\n两文件不相同\n");
			}
			break;
		case 9:  //printf("9.帮助\n\n");
			printHelp();
			break;
		case 0:
			return 0;
		default:
			break;
		}
		printf("输入0以退出，输入1以继续:");
		scanf("%d", &exit_tag);
		if (0 == exit_tag) {
			return 0;
		}
	}
	return 0;
}

bool isFilenameLegal(char filename[]) {
	//<>, / , \, | , , "", *, ?
	//放弃正则
	char exception[] = { "<>/|\"*?" };
	int i = 0;
	int j = 0;
	for (i = 0; filename[i] != '\0'; i++)
	{
		for (j = 0; exception[j] != '\0'; j++) {
			if (filename[i] == exception[j]) {
				return false;
			}
		}
	}
	return true;
}

bool filenameEndsWith(char filename[], char suffix[])
{
	int len_filename = strlen(filename);
	int len_suffix = strlen(suffix);
	filename += len_filename - len_suffix;
	if (0 == strncmp(filename, suffix, len_suffix))
		return true;
	else
		return false;
}


int chooseFunction(bool cls) {
	int func_tag;
	if (cls) {
		system("cls");
	}
	printf("*********************************************************************\n");
	printf("                请输入数字选择功能：\n\n");
	printf("1.从文本文件统计词频\n\n");
	printf("2.打印树形（按层次遍历的方式）\n\n");
	printf("3.打印码本\n\n");
	printf("4.压缩文件\n\n");
	printf("5.解压文件\n\n");
	printf("6.保存码本信息\n\n");
	printf("7.读取码本信息\n\n");
	printf("8.比较两文本文件是否相同\n\n");
	printf("9.帮助\n\n");
	printf("0.退出\n\n");
	printf("*********************************************************************\n");
	rewind(stdin);
	scanf("%d", &func_tag);

if (func_tag >= 0 && func_tag <= 9) {
	return func_tag;
}
else {
	printf("请输入数字0-9以选择功能\n");
	return chooseFunction(false);
}
}


