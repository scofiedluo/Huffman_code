#pragma once
#ifndef HEADER_H

#define HEADER_H

#define MAX_CODE_LEN 3

//���������ñ�׼ͷ�ļ�
#include<stdio.h>
#include <string.h>  //memcpy
#include<stdlib.h>
#include<stdbool.h>

#endif

//���ݽṹ���岿��

//�������ڵ����ݵĶ���
typedef struct listData
{
	char ch[2];
	int cnt;		//Ƶ��
	double freq;	// Ƶ��
}listData;

//������Ķ��塢��������
typedef struct listNode
{
	listData data;
	struct listNode *next;
}listNode;

//����ͷ�����������ݣ�ֻ��������������Ϣ
typedef struct listHead
{
	int length;  //��ͷ������������Ҳ���ǲ�ͬ�ַ��ĸ���
	int cnt;   //�ַ����������н���cnt�ĺͣ�Ҳ�����ļ�����
	bool traverseTag;  //�ж��Ƿ��ڱ����Ĺ�����
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


//���������Ľ��
typedef struct huffmanNode
{
	int val;
	//bool leafTag;
	struct huffmanNode *lChild;
	struct huffmanNode *rChild;
}huffmanNode;

//��ʱ������������
unsigned char G_code_array[MAX_CODE_LEN];


