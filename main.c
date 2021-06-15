#include "Header.h"
#include"code_output.h"
#include"huffman.h"
#include"LINK_list.h"
#include"main.h"
#include"merge_sort.h"
#define FILENAME_LEN_MAX 100

//��ӡ������Ϣ
void printHelp(void) {
	//TODO
	printf("�ù��ܵȴ�����\n");
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
		//printf("�����롰1����2����ѡ��ģʽ");
		return chooseMode(false);
		break;
	}

}

int main(int argc, char *argv[]) {
	listHead *list_head = NULL;
	huffmanNode *huffman_head = NULL;
	tfListHead *tf_list_head = NULL;
	bool mode = true;  //true for �ռ����ȣ�false for ʱ������
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
		case 1:  //	1.���ı��ļ�ͳ�ƴ�Ƶ
			system("cls");
			printf("������Ҫͳ�ƴ�Ƶ���ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
			printf("<(�磺E:\\���ݽṹ���㷨ʵ��\\Data_input.txt)%s>:", input_filename);

			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("�ļ�·�����Ϸ���\n����������Ҫͳ�ƴ�Ƶ���ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(input_filename, temp, FILENAME_LEN_MAX);
			}
			list_head = count_from_file(input_filename);
			if (NULL == list_head) {
				printf("ͳ��ʧ�ܡ�");
				break;
			}
			else {
				sort_list(list_head, false);
				huffman_head = build_tree(list_head);
				if (NULL == huffman_head) {
					printf("������������ʧ��");
					break;
				}
				print_freq(list_head);
				drop_tf_list(tf_list_head);
				free(tf_list_head);
				tf_list_head = NULL;
			}
			break;
		case 2:  //2.��ӡ���Σ�����α����ķ�ʽ��
			if (NULL == huffman_head) {
				printf("��û�н���������Ŷ����ͨ��ͳ�ƴ�Ƶ��������������\n");
				printf("����ͨ����ȡ.tf�ļ���������������\n");
				break;
			}
			else {
				print_huffman_tree(huffman_head);
			}
			break;
		case 3:  //��ӡ�뱾
			if (NULL == huffman_head) {
				printf("��û�н���������Ŷ����ͨ��ͳ�ƴ�Ƶ��������������\n");
				printf("����ͨ����ȡ.tf�ļ���������������\n");
				break;
			}
			if (NULL == list_head) {
				printf("��û�и�����Ƶ����Ŷ����ͨ��ͳ�ƴ�Ƶ��������Ƶ����\n");
				printf("����ͨ����ȡ.tf�ļ���������Ƶ����\n");
				break;
			}
			else {
				print_codebook(huffman_head, list_head);
			}
			break;
		case 4:  //ѹ���ļ�
			mode = chooseMode(true);
			if (NULL == huffman_head) {
				printf("��û�н���������Ŷ����ͨ��ͳ�ƴ�Ƶ��������������\n");
				printf("����ͨ����ȡ.tf�ļ���������������\n");
				break;
			}
			if (NULL == list_head) {
				printf("��û�и�����Ƶ����Ŷ����ͨ��ͳ�ƴ�Ƶ��������Ƶ����\n");
				printf("����ͨ����ȡ.tf�ļ���������Ƶ����\n");
				break;
			}
			printf("������Ҫѹ�����ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", input_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("�ļ�·�����Ϸ���\n����������Ҫѹ�����ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(input_filename, temp, FILENAME_LEN_MAX);
			}

			printf("������Ҫ���浽���ļ����ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", compressed_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("�ļ�·�����Ϸ���\n����������Ҫ���浽���ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
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
			printf("ѹ���ɹ�");
			break;
		case 5:  //��ѹ�ļ�
			if (NULL == huffman_head) {
				printf("��û�н���������Ŷ����ͨ��ͳ�ƴ�Ƶ��������������\n");
				printf("����ͨ����ȡ.tf�ļ���������������");
				break;
			}

			printf("������Ҫ��ѹ�����ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", compressed_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("�ļ�·�����Ϸ���\n����������Ҫ��ѹ�����ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(compressed_filename, temp, FILENAME_LEN_MAX);
			}

			printf("�������ѹ��������ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", target_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("�ļ�·�����Ϸ���\n�����������ѹ��������ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(target_filename, temp, FILENAME_LEN_MAX);
			}

			decode_from_file(huffman_head, compressed_filename, target_filename);

			break;
		case 6:  //	����Ƶ����Ϣ
			if (NULL == list_head) {
				printf("��û�и�����Ƶ����Ŷ����ͨ��ͳ�ƴ�Ƶ��������Ƶ����\n");
				printf("����ͨ����ȡ.tf�ļ���������Ƶ����\n");
				break;
			}

			printf("������Ҫ����Ƶ����Ϣ���ļ���(·��)(%d�ַ���������.tf��β)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", list_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp) || !filenameEndsWith(temp, "tf")) {
					printf("�ļ�·�����Ϸ���\n����������Ҫ����Ƶ����Ϣ���ļ���(·��)(%d�ַ���������.tf��β)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(list_filename, temp, FILENAME_LEN_MAX);
			}

			save_list(list_head, list_filename);
			break;

		case 7:  //��ȡ�뱾��Ϣ
			printf("�����뱣��Ƶ����Ϣ���ļ���(·��)(%d�ַ���������.tf��β)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", list_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp) || !filenameEndsWith(temp, "tf")) {
					printf("�ļ�·�����Ϸ���\n���������뱣��Ƶ����Ϣ���ļ���(·��)(%d�ַ���������.tf��β)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(list_filename, temp, FILENAME_LEN_MAX);
			}

			list_head = create_list_from_file(list_head, list_filename);
			if (NULL == list_head) {
				printf("ͳ�ƴ�Ƶʧ��");
				break;
			}
			drop_huffman_tree(huffman_head);
			huffman_head = build_tree(list_head);
			if (NULL == huffman_head) {
				printf("������������ʧ��");
				break;
			}
			print_freq(list_head);
			drop_tf_list(tf_list_head);
			free(tf_list_head);
			tf_list_head = NULL;
			break;
		case 8:  //printf("8.�Ƚ����ļ��Ƿ���ͬ\n\n");
			printf("�������һ���ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", input_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("�ļ�·�����Ϸ���\n�����������һ���ļ���(·��)(%d�ַ���������.tf��β)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(input_filename, temp, FILENAME_LEN_MAX);
			}

			printf("������ڶ����ļ���(·��)(%d�ַ�����)��\n", FILENAME_LEN_MAX);
			printf("<%s>:", target_filename);
			rewind(stdin);
			scanf("%c", temp);
			if ('\n' != temp[0]) {
				scanf("%s", &temp[1]);
				while (!isFilenameLegal(temp)) {
					printf("�ļ�·�����Ϸ���\n����������ڶ����ļ���(·��)(%d�ַ���������.tf��β)��\n", FILENAME_LEN_MAX);
					scanf("%s", temp);
				}
				memcpy(target_filename, temp, FILENAME_LEN_MAX);
			}

			if (file_compare(input_filename, target_filename)) {
				printf("\n���ļ���ͬ\n");
			}
			else {
				printf("\n���ļ�����ͬ\n");
			}
			break;
		case 9:  //printf("9.����\n\n");
			printHelp();
			break;
		case 0:
			return 0;
		default:
			break;
		}
		printf("����0���˳�������1�Լ���:");
		scanf("%d", &exit_tag);
		if (0 == exit_tag) {
			return 0;
		}
	}
	return 0;
}

bool isFilenameLegal(char filename[]) {
	//<>, / , \, | , , "", *, ?
	//��������
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
	printf("                ����������ѡ���ܣ�\n\n");
	printf("1.���ı��ļ�ͳ�ƴ�Ƶ\n\n");
	printf("2.��ӡ���Σ�����α����ķ�ʽ��\n\n");
	printf("3.��ӡ�뱾\n\n");
	printf("4.ѹ���ļ�\n\n");
	printf("5.��ѹ�ļ�\n\n");
	printf("6.�����뱾��Ϣ\n\n");
	printf("7.��ȡ�뱾��Ϣ\n\n");
	printf("8.�Ƚ����ı��ļ��Ƿ���ͬ\n\n");
	printf("9.����\n\n");
	printf("0.�˳�\n\n");
	printf("*********************************************************************\n");
	rewind(stdin);
	scanf("%d", &func_tag);

if (func_tag >= 0 && func_tag <= 9) {
	return func_tag;
}
else {
	printf("����������0-9��ѡ����\n");
	return chooseFunction(false);
}
}


