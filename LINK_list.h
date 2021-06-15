//list.c

//创建一个新的空链表，返回链表头
listHead* create_null_list(void);

//从list创建一个tf_list
//@param listHead *list_head 排序好了的链表的头结点
//@param huffmanNode *huffman_head 哈夫曼根节点
tfListHead* create_tf_list(listHead *list_head, huffmanNode *huffman_head);

//向链表末尾增加一个结点，返回1表示成功，0表示未成功
//参数head为目标链表的头结点，参数ch为要插入的字符变量
listNode* append_list(listHead *head, char ch[]);


//循环链表每一个结点，返回结点的data指针,循环完毕或长度为空时返回NULL
//注意如果在foreach的过程中break了，需要将head->traverseTag置为假
//参数head为目标链表的头结点。
listData* foreach_list(listHead *head);

//读取储存了list的文件并重新构建链表。
//@param listHead* list_head 旧的链表的头指针，主要用来释放旧的链表。nullable
//@param char list_filename[] list文件路径
//@param listHead* 返回链表头指针
listHead* create_list_from_file(listHead* list_head, char list_filename[]);

//查找一个字符对应的tf节点data数据
//@param tfListHead *tf_list_head
//@param char ch[] 
//@return tfListData
tfListData get_tf_node_data(tfListHead *tf_list_head, char ch[]);

//删除链表：删除除头结点外的其他节点，注意预防野指针
//@param listHead* list_head
void drop_list(listHead* list_head);

//删除链表：删除除头结点外的其他节点，注意预防野指针
void drop_tf_list(tfListHead * list_head);