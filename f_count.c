#include "Header.h"
#include"code_output.h"
#include"huffman.h"
#include"LINK_list.h"
#include"main.h"
#include"merge_sort.h"

listNode* getMiddle(listNode* p);

listNode* mergeList(listNode* p1, listNode* p2, bool mode);

listNode* sortList(listNode* p, bool mode);

listHead* count_from_file(char filename[]) {
	listHead *head;
	listData *data;
	FILE *fp;
	bool duplicate_tag;  //���ж��ظ���ʱ����
	char ch[2];
	listNode *p;

	fp = fopen(filename, "r");
	if (NULL == fp) {
		return NULL;
	}
	head = create_null_list();
	while ((*ch = fgetc(fp)) != EOF) {
	
		if (ch[0] < 0) {
			ch[1] = fgetc(fp);
		}
		else {
			ch[1] = '\0';
		}
		duplicate_tag = false;
		//�ж��Ƿ��ظ�
		while (data = foreach_list(head)) {

			if (0 == memcmp(data->ch, ch, 2)) {
				data->cnt++;
				duplicate_tag = true;
				head->traverseTag = false;
				break;
			}
		}

		if (!duplicate_tag) {
			if (!(p = append_list(head, ch))) {
				//���ʧ�ܾ���ʾ���˳�����
				printf("ͳ�ƹ��̳��ִ�������������");
				exit(0);
			}
			else {
				p->data.cnt++;
			}
		}
		head->cnt++;
	}
	fclose(fp);

	//�������һ����ʾ�������ַ�
	ch[0] = '\0'; ch[1] = '\0';
	if (!(p = append_list(head, ch))) {
		printf("ͳ�ƹ��̳��ִ�������������");
		exit(0);
	}
	p->data.cnt = 0;
	head->length -= 1;

	//���ѭ������һ��Ƶ��
	while (data = foreach_list(head)) {
		data->freq = (double)data->cnt / head->cnt;
	}

	return head;
}