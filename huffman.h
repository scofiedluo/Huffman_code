

//临时储存代码的数组
unsigned char G_code_array[MAX_CODE_LEN];

//由统计结果建立哈夫曼树
//@param listHead* head
//@return huffmanNode* 返回树根结点指针
huffmanNode* build_tree(listHead* head);

//删除一个哈夫曼树，将删掉所有节点，包括根节点.
//@param huffmanNode* huffman_head
void drop_huffman_tree(huffmanNode* huffman_head);

//给一个字符，得到该字符对应编码数组的前几位。
//@param huffmanNode* huffman_head 根节点
//@param char ch[] char的长度固定为2
//@return int 返回该编码长度。
int get_char_code_len(huffmanNode* huffman_head, char ch[]);

//将压缩后的文件解码，并输出到文件中去。
//@param huffmanNode *huffman_head
//@param char encoded_filename[] 压缩文件，储存二进制码流的文件
//@param char decoded_filename[] 输出的文件名
void decode_from_file(huffmanNode* huffman_head, char encoded_filename[], char decoded_filename[]);
