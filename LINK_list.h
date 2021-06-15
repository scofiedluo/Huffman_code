//list.c

//����һ���µĿ�������������ͷ
listHead* create_null_list(void);

//��list����һ��tf_list
//@param listHead *list_head ������˵������ͷ���
//@param huffmanNode *huffman_head ���������ڵ�
tfListHead* create_tf_list(listHead *list_head, huffmanNode *huffman_head);

//������ĩβ����һ����㣬����1��ʾ�ɹ���0��ʾδ�ɹ�
//����headΪĿ�������ͷ��㣬����chΪҪ������ַ�����
listNode* append_list(listHead *head, char ch[]);


//ѭ������ÿһ����㣬���ؽ���dataָ��,ѭ����ϻ򳤶�Ϊ��ʱ����NULL
//ע�������foreach�Ĺ�����break�ˣ���Ҫ��head->traverseTag��Ϊ��
//����headΪĿ�������ͷ��㡣
listData* foreach_list(listHead *head);

//��ȡ������list���ļ������¹�������
//@param listHead* list_head �ɵ������ͷָ�룬��Ҫ�����ͷžɵ�����nullable
//@param char list_filename[] list�ļ�·��
//@param listHead* ��������ͷָ��
listHead* create_list_from_file(listHead* list_head, char list_filename[]);

//����һ���ַ���Ӧ��tf�ڵ�data����
//@param tfListHead *tf_list_head
//@param char ch[] 
//@return tfListData
tfListData get_tf_node_data(tfListHead *tf_list_head, char ch[]);

//ɾ������ɾ����ͷ�����������ڵ㣬ע��Ԥ��Ұָ��
//@param listHead* list_head
void drop_list(listHead* list_head);

//ɾ������ɾ����ͷ�����������ڵ㣬ע��Ԥ��Ұָ��
void drop_tf_list(tfListHead * list_head);