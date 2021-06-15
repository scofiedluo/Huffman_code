#pragma once
#ifndef HEADER_H

#define HEADER_H

#define MAX_CODE_LEN 3

//在这里引用标准头文件
#include<stdio.h>
#include <string.h>  //memcpy
#include<stdlib.h>
#include<stdbool.h>

#endif

//数据结构定义部分

//链表结点内的数据的定义
typedef struct listData
{
	char ch[2];
	int cnt;		//频数
	double freq;	// 频率
}listData;

//链表结点的定义、单向链表
typedef struct listNode
{
	listData data;
	struct listNode *next;
}listNode;

//链表头，不包含数据，只用来包含链表信息
typedef struct listHead
{
	int length;  //除头结点外结点个数，也就是不同字符的个数
	int cnt;   //字符数，即所有结点的cnt的和，也就是文件长度
	bool traverseTag;  //判断是否在遍历的过程中
	listNode *next;
	listNode *curr;
	listNode *tail;
}listHead;

typedef struct tfListData
{
	char ch[2];
	unsigned char valid_len;
	unsigned char code[MAX_CODE_LEN];
}tfListData;

typedef struct tfListNode
{
	tfListData data;
	struct tfListNode *next;
}tfListNode;

typedef struct tfListHead
{
	tfListNode *next;
	tfListNode *curr;
	tfListNode *tail;
}tfListHead;


//哈夫曼树的结点
typedef struct huffmanNode
{
	int val;
	//bool leafTag;
	struct huffmanNode *lChild;
	struct huffmanNode *rChild;
}huffmanNode;

//临时储存代码的数组
unsigned char G_code_array[MAX_CODE_LEN];


