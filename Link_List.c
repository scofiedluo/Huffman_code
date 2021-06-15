#include "Header.h"
#include"code_output.h"
#include"huffman.h"
#include"LINK_list.h"
#include"main.h"
#include"merge_sort.h"

tfListHead* createNullTfList(void);

listNode* append_list(listHead *head, char ch[]) {
	listNode* p;
	p = (listNode*)malloc(sizeof(listNode));
	if (NULL == p) {
		return NULL;
	}

	if (head->tail) {  //ԭ�ȵ����һ�����ָ���½��
		head->tail->next = p;
	}
	else
	{//���tailΪ�գ�˵��length=0
		head->next = p;
	}

	head->tail = p;  //����ͷ����Ϣ
	head->length++;

	p->next = NULL;  //��ʼ���ý����Ϣ
	memcpy(p->data.ch, ch, 2);
	//strcpy(p->data.ch, ch);
	p->data.cnt = 0;
	p->data.freq = 0;

	return p;  //�ɹ��򷵻ظý��ָ��
}

listHead* create_null_list(void) {
	listHead *head;
	head = (listHead*)malloc(sizeof(listHead));
	head->next = NULL;
	head->cnt = 0;
	head->curr = NULL;
	head->tail = NULL;
	head->length = 0;
	head->traverseTag = false;
	return head;
}

listData* foreach_list(listHead *head) {
	//�������Ϊ�㣬���ؿ�
	if (!head->length) {
		return NULL;
	}

	//�ж��Ƿ���ѭ�������С�
	listData *p;
	if (head->traverseTag) {
		//���p�ǿյ�˵��ѭ�����
		if (NULL == head->curr) {
			head->traverseTag = false;
			head->curr = head->next;
			return NULL;
		}
		p = &(head->curr->data);
		head->curr = head->curr->next;
		return p;
	}
	else {
		head->traverseTag = true;
		head->curr = head->next;
		return foreach_list(head);
	}
}

listHead * create_list_from_file(listHead * list_head, char list_filename[])
{

	if (NULL != list_head) {
		drop_list(list_head);
	}
	else {
		list_head = create_null_list();
	}
	FILE *fp;
	fp = fopen(list_filename, "rb");
	if (NULL == fp) {
		printf("�򿪽ڵ��ļ�ʧ�ܣ�������");
		return list_head;
	}

	char ch[2];
	int cnt;
	listNode *list_node;
	listData *data;

	while (true) {
		fread(ch, 2 * sizeof(char), 1, fp);
		fread(&cnt, sizeof(int), 1, fp);
		list_node = append_list(list_head, ch);
		list_node->data.cnt = cnt;
		list_head->cnt += cnt;
		if ('\0' == ch[0] && '\0' == ch[1]) {
			break;
		}
	}

	while (data = foreach_list(list_head)) {
		data->freq = (double)(data->cnt) / list_head->cnt;
	}

	return list_head;
}

void drop_list(listHead * list_head)
{
	listNode *p, *temp;
	if (NULL == list_head) {
		return;
	}
	p = list_head->next;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
		temp = NULL;
	}
	list_head->next = NULL;
	list_head->tail = NULL;
	list_head->curr = NULL;
	list_head->cnt = 0;
	list_head->length = 0;
	list_head->traverseTag = false;
}

tfListHead* create_tf_list(listHead *list_head, huffmanNode *huffman_head) {
	tfListHead *tf_list_head = NULL;
	tfListNode *tf_list_node = NULL;
	listData *data = NULL;
	unsigned char code_len;
	tf_list_head = createNullTfList();
	if (NULL == tf_list_head) {
		printf("����tf����ʧ��");
		return NULL;
	}
	while (data = foreach_list(list_head)) {
		tf_list_node = (tfListNode*)malloc(sizeof(tfListNode));
		if (NULL == tf_list_node) {
			printf("����tf����ʧ��");
			drop_tf_list(tf_list_head);
			return NULL;
		}
		if (NULL == tf_list_head->next) {
			tf_list_head->next = tf_list_node;
			tf_list_head->tail = tf_list_node;
		}
		else {
			tf_list_head->tail->next = tf_list_node;
			tf_list_head->tail = tf_list_node;
		}
		code_len = (unsigned char)get_char_code_len(huffman_head, data->ch);
		memcpy(tf_list_node->data.ch, data->ch, 2 * sizeof(char));
		memcpy(tf_list_node->data.code, G_code_array, MAX_CODE_LEN);
		tf_list_node->data.valid_len = code_len;
		tf_list_node->next = NULL;
	}
	return tf_list_head;
}

tfListData get_tf_node_data(tfListHead *tf_list_head, char ch[])
{
	tfListData data;
	tfListNode *tf_list_node = NULL;
	data.valid_len = 0;
	tf_list_node = tf_list_head->next;
	while (tf_list_node) {
		if (0 == memcmp(tf_list_node->data.ch, ch, sizeof(char) * 2)) {
			return tf_list_node->data;
		}
		tf_list_node = tf_list_node->next;
	}
	return data;
}


void drop_tf_list(tfListHead * list_head) {
	tfListNode *p, *temp;
	if (NULL == list_head) {
		return;
	}
	p = list_head->next;
	while (p) {
		temp = p;
		p = p->next;
		free(temp);
		temp = NULL;
	}
	list_head->next = NULL;
	list_head->tail = NULL;
	list_head->curr = NULL;
}

//����һ��tf������������ͷ
tfListHead* createNullTfList(void) {
	tfListHead *head;
	head = (tfListHead*)malloc(sizeof(tfListHead));
	if (NULL == head) {
		return head;
	}
	head->next = NULL;
	head->curr = NULL;
	head->tail = NULL;
	return head;
}

