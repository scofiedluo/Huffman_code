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
	bool duplicate_tag;  //在判断重复的时候用
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
		//判断是否重复
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
				//如果失败就提示并退出程序
				printf("统计过程出现错误，请重新运行");
				exit(0);
			}
			else {
				p->data.cnt++;
			}
		}
		head->cnt++;
	}
	fclose(fp);

	//最后增加一个表示结束的字符
	ch[0] = '\0'; ch[1] = '\0';
	if (!(p = append_list(head, ch))) {
		printf("统计过程出现错误，请重新运行");
		exit(0);
	}
	p->data.cnt = 0;
	head->length -= 1;

	//最后循环，改一下频率
	while (data = foreach_list(head)) {
		data->freq = (double)data->cnt / head->cnt;
	}

	return head;
}