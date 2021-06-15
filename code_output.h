//output.c

//美观地输出频率频度
//@param listHead* head目标链表的头结点
void print_freq(listHead *head);

//美观地输出哈夫曼树
//@param huffmanNode* head目标哈夫曼树的根节点
void print_huffman_tree(huffmanNode* head);

//将二进制的码流转换成十进制方便输出码本的编码
//@param int len 二进制码流的位数
//@param char *code 用来储存转换后的十进制0、1的数组
//@param char *bi_code 储存二进制码流的数组
void code_bi_to_dec(int len, bool *code, char *bi_code);

//输出一个字符的编码
//@param huffmanNode *huffman_head 
//@param char ch[]，字符长度为2
void print_one_char_code(huffmanNode *huffman_head, char ch[]);

//打印码本
//@param huffmanNode *huffman_head
//@param listHead *list_head
void print_codebook(huffmanNode *huffman_head, listHead *list_head);

//保存节点信息，格式为每个单元6字节=char字符*2+int频数*1，无分隔符。
//@param listHead *list_head
//@param char codebook_filename[] 保存到文件的位置
void save_list(listHead *list_head, char list_filename[]);

//空间优先模式得到二进制码流并且将码流输出到文件中去。
//@param huffmanNode *huffman_head
//@param char output_filename[] 压缩后输出的文件的文件名
//@param char input_filename[] 要压缩的文件名
void encode_and_save(huffmanNode *huffman_head, char output_filename[], char input_filename[]);

//时间优先模式得到二进制码流并且将码流输出到文件中去。
//@param tfListHead *tf_list_head
//@param char output_filename[] 压缩后输出的文件的文件名
//@param char input_filename[] 要压缩的文件名
void encode_and_save_tf(tfListHead *tf_list_head, char output_filename[], char input_filename[]);

//检查两个文本文件是否完全相同
//@param char file1_name[]
//@param char file2_name[]
bool file_compare(char file1_name[], char file2_name[]);