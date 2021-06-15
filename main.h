//main.c

//检查文件名是否合法
//@param char filename[]
//@return bool 是否合法
bool isFilenameLegal(char filename[]);

//检查文件名后缀
//@param char filename[]
//@param char suffix[] 
//@return bool 文件后缀为suffix，则返回true
bool filenameEndsWith(char filename[], char suffix[]);