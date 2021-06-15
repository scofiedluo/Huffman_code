

//��ʱ������������
unsigned char G_code_array[MAX_CODE_LEN];

//��ͳ�ƽ��������������
//@param listHead* head
//@return huffmanNode* �����������ָ��
huffmanNode* build_tree(listHead* head);

//ɾ��һ��������������ɾ�����нڵ㣬�������ڵ�.
//@param huffmanNode* huffman_head
void drop_huffman_tree(huffmanNode* huffman_head);

//��һ���ַ����õ����ַ���Ӧ���������ǰ��λ��
//@param huffmanNode* huffman_head ���ڵ�
//@param char ch[] char�ĳ��ȹ̶�Ϊ2
//@return int ���ظñ��볤�ȡ�
int get_char_code_len(huffmanNode* huffman_head, char ch[]);

//��ѹ������ļ����룬��������ļ���ȥ��
//@param huffmanNode *huffman_head
//@param char encoded_filename[] ѹ���ļ�������������������ļ�
//@param char decoded_filename[] ������ļ���
void decode_from_file(huffmanNode* huffman_head, char encoded_filename[], char decoded_filename[]);
