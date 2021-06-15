#include "Header.h"
#include"code_output.h"
#include"huffman.h"
#include"LINK_list.h"
#include"main.h"
#include"merge_sort.h"

listNode* getMiddle(listNode* p);

listNode* mergeList(listNode* p1, listNode* p2, bool mode);

listNode* sortList(listNode* p, bool mode);

void sort_list(listHead* head, bool mode) 
{
	head->next = sortList(head->next, mode);
	while (head->tail->next)
	{
		head->tail = head->tail->next;
	}
}

//���ظ�������м��㣬�����ż������㣬�����м�ƫ��Ľ��
//@param listNode p �������һ����ͷ��㡣
//@return listNode

listNode* getMiddle(listNode* p)
{
	if (!(p && p->next)) return p;

	listNode *fast;
	listNode *slow;
	slow = p;
	fast = p->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

//�ϲ���������õ��������غϲ��������ĵ�һ�����
//@param listNode p1
//@param listNode p2
//@param bool mode true��ʾ����false��ʾ����
//@return listNode*

listNode* mergeList(listNode * p1, listNode * p2, bool mode)
{
	if (NULL == p1) return p2;
	if (NULL == p2) return p1;

	listNode* p;
	listNode* head;

	
	if (p1->data.cnt < p2->data.cnt) {
		head = mode ? p1 : p2;
		mode ? (p1 = p1->next) : (p2 = p2->next);
	}
	else
	{
		head = mode ? p2 : p1;
		mode ? (p2 = p2->next) : (p1 = p1->next);
	}
	p = head;
	while (p1 && p2)
	{
		if (p1->data.cnt < p2->data.cnt) 
		{
			p->next = mode ? p1 : p2;
			mode ? (p1 = p1->next) : (p2 = p2->next);
		}
		else 
		{
			p->next = mode ? p2 : p1;
			mode ? (p2 = p2->next) : (p1 = p1->next);
		}
		p = p->next;
	}
	while (p2) {
		p->next = p2;
		p = p->next;
		p2 = p2->next;
	}
	while (p1) {
		p->next = p1;
		p = p->next;
		p1 = p1->next;
	}
	return head;
}

//�鲢���򣬷�������õ�����ĵ�һ�����
//@param listNode p �����һ����ͷ���
//@param bool mode true��ʾ����false��ʾ����
//@return listNode* 
listNode* sortList(listNode * p, bool mode)
{
	if (!(p && p->next)) return p;  // ���ؿջ������Ψһ�Ľ��

	listNode* middle = getMiddle(p);
	listNode* latter_part;
	if (middle) {
		latter_part = middle->next;
		middle->next = NULL;
	}
	return mergeList(sortList(p, mode), sortList(latter_part, mode), mode);
}
