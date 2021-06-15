#include "Header.h"
#include"code_output.h"
#include"huffman.h"
#include"LINK_list.h"
#include"main.h"
#include"merge_sort.h"
//记录每个结点指针的森林结点
typedef struct forestNode
{
	huffmanNode* pNode;
	struct forestNode* next;
}forestNode;

//储存节点指针的栈
typedef struct stackNode {
	huffmanNode* p;
	struct stackNode *next;
} treeStackNode;

typedef struct stackHead {
	treeStackNode *next;
}treeStackHead;

//用来辅助做二进制运算 in output.c
extern unsigned char bi_array[8];

forestNode* preBuildTree(listHead* head);
huffmanNode* createHuffmanNode(forestNode* p1, forestNode* p2);
forestNode* createForestNode(huffmanNode* p_huffman);
void deleteLastTwoForestNode(forestNode* prev, forestNode* p1);
forestNode* insertForestNode(forestNode* head, forestNode* p);
void pushStack(treeStackHead* stack_head, huffmanNode* p);
treeStackHead* createStack(void);
treeStackNode popStack(treeStackHead* stack_head);

huffmanNode* build_tree(listHead* head)
{
	if (NULL == head->next || NULL == head->next->next)
	{
		printf("该文件仅有一种字符或没有字符，拒绝建立哈夫曼编码\n");
		return NULL;
	}
	//p1,p2找权重最小的两个结点，p存新结点。prev_p1存p1的前驱
	forestNode *p1_forest, *p2_forest, *p_forest, *prev_p1_forest;
	forestNode *p_forest_head;        //定义森林的头节点
	huffmanNode *p_huffman;
	p_forest_head = preBuildTree(head);
	//到最后森林里应该只有一个结点
	while (p_forest_head->next) 
	{
		p1_forest = p_forest_head;
		p2_forest = p_forest_head->next;
		prev_p1_forest = NULL;

		//找权重最小的两个结点，因为已经排序好，所以只需要找最后两个结点即可
		while (p2_forest->next)
		{
			if (NULL == p2_forest->next->next) 
			{
				prev_p1_forest = p1_forest;
			}
			p1_forest = p1_forest->next;
			p2_forest = p2_forest->next;
		}

		p_huffman = createHuffmanNode(p1_forest, p2_forest);
		p_forest = createForestNode(p_huffman);
		deleteLastTwoForestNode(prev_p1_forest, p1_forest);
		if (NULL == prev_p1_forest)
		{
			p_forest_head = NULL;
		}
		p_forest_head = insertForestNode(p_forest_head, p_forest);
	}
	return p_forest_head->pNode;
}

//销毁
void drop_huffman_tree(huffmanNode * huffman_head)
{
	if (NULL == huffman_head) {
		return;
	}
	if (NULL == huffman_head->rChild) {  //右子树为空说明是叶子结点
		free(huffman_head);
	}
	else {
		drop_huffman_tree(huffman_head->lChild);
		drop_huffman_tree(huffman_head->rChild);
		free(huffman_head);
	}
}

int get_char_code_len(huffmanNode* huffman_head, char ch[])                      //得到每种字符的编码长度
{
	// 避免多次开辟栈头结点浪费时间
	static treeStackHead* stack_head = NULL;
	treeStackNode stack_node;
	huffmanNode* curr;
	listNode* p_list_node;
	unsigned char ch_temp;
	int len = 0;  //编码长度（二进制位数）
	if (NULL == stack_head) {
		stack_head = createStack();
	}
	curr = huffman_head;
	while (curr) {
		if (NULL == curr->rChild)
		{  //这说明curr指向叶子结点
			p_list_node = (listNode*)curr->lChild;
			if (memcmp(p_list_node->data.ch, ch, 2) == 0)
			{  //说明匹配上了
				return len;
			}
			else 
			{  //如果没有匹配上，则回退，或回退+弹出。
				ch_temp = 1;
				while (ch_temp)
				{  //如果最后一位为1，则一直回退，不弹出
					ch_temp = G_code_array[(len - 1) / 8] & bi_array[len % 8];
					len--;
				}
				//现在最后一位是0,接下来弹出一个。
				stack_node = popStack(stack_head);
				if (stack_node.p) {
					curr = stack_node.p;
				}
				else 
				{
					return 0;  //说明没找到
				}
				len++;
				G_code_array[(len - 1) / 8] = G_code_array[(len - 1) / 8] | bi_array[len % 8];
			}
		}
		else {  //如果curr不是指向叶子结点。
			pushStack(stack_head, curr->rChild);
			curr = curr->lChild;
			len++;
			//把最后一位赋0
			G_code_array[(len - 1) / 8] = G_code_array[(len - 1) / 8] & ~bi_array[len % 8];
		}
	} //end while
	//free(stack_head);
	return 0;
}

void decode_from_file(huffmanNode * huffman_head, char encoded_filename[], char decoded_filename[])     //从文件中进行huaffman编码
{
	FILE *fp_encoded, *fp_decoded;
	huffmanNode *curr;
	listNode *list_node;
	int i;
	char ch;
	char ch_temp;
	fp_encoded = fopen(encoded_filename, "rb");
	fp_decoded = fopen(decoded_filename, "w");
	if (NULL == fp_encoded || NULL == fp_decoded)
	{
		printf("文件打开失败");
		return;
	}
	curr = huffman_head;
	//在读取二进制文件时，有可能会读到0000 0000 ，从而返回EOF造成文件提前终止
	//while ((ch = fgetc(fp_encoded)) != EOF) {
	while (1) {
		ch = fgetc(fp_encoded);
		for (i = 1; i <= 8; i++)
		{
			ch_temp = ch & bi_array[i % 8];
			if (ch_temp)
			{
				curr = curr->rChild;
			}
			else 
			{
				curr = curr->lChild;
			}
			if (NULL == curr->rChild) 
			{
				list_node = (listNode*)curr->lChild;
				if (list_node->data.ch[0] < 0) {
					fwrite(list_node->data.ch, 2, 1, fp_decoded);
					printf("%c%c", list_node->data.ch[0], list_node->data.ch[1]);
				}
				else 
				{
					if ('\0' == list_node->data.ch[0]) 
					{
						fclose(fp_encoded);
						fclose(fp_decoded);
						printf("\n");
						return;
					}
					else {
						fwrite(list_node->data.ch, 1, 1, fp_decoded);
						printf("%c", list_node->data.ch[0]);
					}
				}
				curr = huffman_head;
			}
		}
	}

}


//向head指向的这个森林中插入一个p指针指向的节点,降序
//@param forestNode* head
//@param forestNode* p
//@return forestNode* 插入后的节点的头
forestNode* insertForestNode(forestNode* head, forestNode* p) 
{
	if (head == NULL) 
	{
		return p;
	}
	forestNode* prev;
	forestNode* curr;
	prev = head;
	curr = head;
	while (NULL != curr && curr->pNode->val > p->pNode->val)
	{
		prev = curr;
		curr = curr->next;
	}

	//如果prev和curr相同。就说明p节点应该插在头结点前面
	if (prev == curr) {
		head = p;
	}
	else {
		prev->next = p;
	}
	p->next = curr;
	return head;
}

//创建一个指向该huffman结点的森林结点
//@param huffmanNode* p_huffman 
//@return forestNode* 
forestNode* createForestNode(huffmanNode* p_huffman) {
	forestNode *p_forest;
	p_forest = (forestNode*)malloc(sizeof(forestNode));
	if (!p_forest) {
		printf("建立哈夫曼过程中分配临时内存失败");
		exit(0);
	}
	p_forest->pNode = p_huffman;
	p_forest->next = NULL;
	return p_forest;
}

//删除prev后的两个forest的节点。
//@param forestNode* pre 要删除的两个节点的前面一个
//@param forestNode* p1 要删除的第一个节点
void deleteLastTwoForestNode(forestNode* prev, forestNode* p1) {
	if (NULL != prev) {
		prev->next = NULL;
	}
	free(p1->next);
	free(p1);
}

//由两个森林结点创建一个新的huffman结点，应满足p2对应的val小于等于p1对应的val
//@param forestNode p1
//@param forestNode p2
//@return huffmanNode* 
huffmanNode* createHuffmanNode(forestNode * p1, forestNode * p2)
{
	huffmanNode* p_huffman;

	p_huffman = (huffmanNode*)malloc(sizeof(huffmanNode));
	if (!p_huffman) {
		printf("建立哈夫曼过程中分配临时内存失败");
		exit(0);
	}
	p_huffman->lChild = p1->pNode;
	p_huffman->rChild = p2->pNode;
	//p_huffman->leafTag = false;
	p_huffman->val = p1->pNode->val + p2->pNode->val;
	return p_huffman;
}

//将原链表的listNode结点变成huffmanNode(huffman结点）构成的森林
//@param listNode* 
//@return forestNode* 
forestNode* preBuildTree(listHead * head)
{
	listNode *p = head->next;
	forestNode *p_forest_head;
	forestNode *p_forest;
	huffmanNode *p_huffman;
	p_forest = (forestNode*)malloc(sizeof(forestNode));
	p_forest_head = p_forest;
	while (p)
	{
		p_huffman = (huffmanNode*)malloc(sizeof(huffmanNode));
		if (!p_forest || !p_huffman)
		{
			printf("建立哈夫曼过程中分配临时内存失败");
			exit(0);
		}

		//初始化huffman结点
		p_huffman->rChild = NULL;
		p_huffman->lChild = p;  //这里p和lChild指向数据的类型并不一致，但指针本质都是一个int，使用它时再进行一下强制转换即可。
		//p_huffman->leafTag = true;  通过判断右节点是否为空即可得知它是不是叶子结点
		p_huffman->val = p->data.cnt;

		//初始化forest结点
		p_forest->pNode = p_huffman;
		p_forest->next = NULL;

		if (p->next)
		{
			p_forest->next = (forestNode*)malloc(sizeof(forestNode));
		}
		p_forest = p_forest->next;
		p = p->next;
	}
	return p_forest_head;
}

/*                栈的相关操作          */
//将一个HuffmanNode压入栈尾
//@param treeStackHead* stack_head 栈的头指针。
//@param huffmanNode* p_huffman_node 要压入的Huffman节点的指针
void pushStack(treeStackHead* stack_head, huffmanNode* p_huffman_node) 
{
	treeStackNode *p_node;
	p_node = malloc(sizeof(treeStackNode));
	if (!p_node)
	{
		printf("开辟栈空间失败");
		exit(0);
	}
	p_node->p = p_huffman_node;
	p_node->next = stack_head->next;
	stack_head->next = p_node;
}


//创建一个空的栈，即new一个空的栈,
//@return treeStackHead* 返回头结点指针
treeStackHead* createStack(void) 
{
	treeStackHead* stack_head;
	stack_head = malloc(sizeof(treeStackHead));
	if (!stack_head) {
		printf("开辟栈头结点失败");
		exit(0);
	}
	stack_head->next = NULL;
	return stack_head;
}

//从栈中弹出一个元素
treeStackNode popStack(treeStackHead* stack_head) 
{
	treeStackNode stack_node;
	treeStackNode* temp;
	if (NULL == stack_head->next) {
		stack_node.next = NULL;
		stack_node.p = NULL;
		return stack_node;
	}
	temp = stack_head->next;
	stack_node = *temp;
	stack_head->next = stack_head->next->next;
	free(temp);
	return stack_node;
}
