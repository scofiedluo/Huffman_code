//output.c

//���۵����Ƶ��Ƶ��
//@param listHead* headĿ�������ͷ���
void print_freq(listHead *head);

//���۵������������
//@param huffmanNode* headĿ����������ĸ��ڵ�
void print_huffman_tree(huffmanNode* head);

//�������Ƶ�����ת����ʮ���Ʒ�������뱾�ı���
//@param int len ������������λ��
//@param char *code ��������ת�����ʮ����0��1������
//@param char *bi_code �������������������
void code_bi_to_dec(int len, bool *code, char *bi_code);

//���һ���ַ��ı���
//@param huffmanNode *huffman_head 
//@param char ch[]���ַ�����Ϊ2
void print_one_char_code(huffmanNode *huffman_head, char ch[]);

//��ӡ�뱾
//@param huffmanNode *huffman_head
//@param listHead *list_head
void print_codebook(huffmanNode *huffman_head, listHead *list_head);

//����ڵ���Ϣ����ʽΪÿ����Ԫ6�ֽ�=char�ַ�*2+intƵ��*1���޷ָ�����
//@param listHead *list_head
//@param char codebook_filename[] ���浽�ļ���λ��
void save_list(listHead *list_head, char list_filename[]);

//�ռ�����ģʽ�õ��������������ҽ�����������ļ���ȥ��
//@param huffmanNode *huffman_head
//@param char output_filename[] ѹ����������ļ����ļ���
//@param char input_filename[] Ҫѹ�����ļ���
void encode_and_save(huffmanNode *huffman_head, char output_filename[], char input_filename[]);

//ʱ������ģʽ�õ��������������ҽ�����������ļ���ȥ��
//@param tfListHead *tf_list_head
//@param char output_filename[] ѹ����������ļ����ļ���
//@param char input_filename[] Ҫѹ�����ļ���
void encode_and_save_tf(tfListHead *tf_list_head, char output_filename[], char input_filename[]);

//��������ı��ļ��Ƿ���ȫ��ͬ
//@param char file1_name[]
//@param char file2_name[]
bool file_compare(char file1_name[], char file2_name[]);