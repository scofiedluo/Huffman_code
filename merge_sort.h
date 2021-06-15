//merge_sort.c

//用来统计频率，返回一个链表头
//@param filename string 文件名
//@return listHead* 链表头
listHead* count_from_file(char filename[]);

//将统计结果排序。
//@param listHead* head 目标链表头结点
//@param bool mode true表示增序，false表示降序
void sort_list(listHead* head, bool mode);