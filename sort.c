#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 1000

int* dataFromFile(char *argv[]);
int* dataFromInput(void);
void getNum(char* str, int *num);
void half(int head, int tail, int* parent, int* child);

int size = 0;

int main(int argc, char *argv[]) {
    int* num;

    if(argc == 2) {
        num = dataFromFile(argv);
    } else {
        num = dataFromInput();
    }

    int* child_num1;
    int* child_num2;
    int* merge_num;
    child_num1 = (int*)malloc(sizeof(int) * (size / 2));
    child_num2 = (int*)malloc(sizeof(int) * (size - size / 2));
    merge_num = (int*)malloc(sizeof(int) * size);
    half(0, size/2, num, child_num1);
    half(size/2, size, num, child_num2);

//test
printf("before:");
for(int i = 0; i < size; i++) {
printf("%d ", num[i]);
}

printf("\nchild_num1:");
for(int i = 0; i < size/2; i++) {
printf("%d:%d ", i+1, child_num1[i]);
}

printf("\nchild_num2:");
for(int i = 0; i < size - size / 2; i++) {
printf("%d:%d ", i+1, child_num2[i]);
}
printf("\n");
//

    return 0;
}

int* dataFromFile(char *argv[]){
/*
从文件中读取数据
输入：文件名
输出：存放数据的int数组
*/
    FILE *in;
    int ch;
    int i = 0;
    int last;
    char* str;

    if((in = fopen(argv[1], "r")) == NULL) {
        printf("Error! Couldn't open the file <%s>!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    fseek(in, 0L, SEEK_END);
    last = ftell(in);
    str = (char*)malloc(sizeof(char) * last);
    fseek(in, 0L, SEEK_SET);
    while((ch = getc(in)) != EOF){
        str[i] = ch;
        i++;
    }

    if(fclose(in) != 0){
        printf("Error in closing files:<%s>", argv[1]);
    }
    str[i-1] = '\n';
    str[i] = '\0';

    for(int i = 0; i < strlen(str); i++){
        if(str[i] >= '0' && str[i] <= '9') {
            continue;
        }
        size++;
    }

    int *num = (int*)malloc(sizeof(int) * size);
    getNum(str, num);
    return num;
}

int* dataFromInput(void) {
/*
从用户输入中读取数据
输入：无
输出：存放数据的int数组
*/
    printf("请输入一串数字，并用空格隔开，以回车结尾:\n");
    char str[MaxSize];
    fgets(str,MaxSize,stdin);

    for(int i = 0; i < strlen(str); i++){
        if(str[i] >= '0' && str[i] <= '9') {
            continue;
        }
        size++;
    }

    int *num = (int*)malloc(sizeof(int) * size);
    getNum(str, num);
    return num;
}

void getNum(char* str, int *num) {
/*
将字符串中数字部分转化为int型数据，剔除无关字符，
！仅在dataFromFile()函数和dataFromInput()函数中被调用
输入：一个字符串str，存储了用非数字字符分隔开的数据；
      一个存储数字的int数组用于存放结果
输出：无
*/
    int head, tail;
    head = tail = 0;
    char *tmp;
    int k = 0;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] < '0' || str[i] > '9') {
            head = tail;
            tail = i;
            int len = tail - head + 1;
            tmp = (char*)malloc(sizeof(char) * len);
            for(int j = 0;head < tail; j++,head++){
                tmp[j] = str[head];
            }
            tmp[len-1] = '\0';
            num[k] = atoi(tmp);
            tail++;
            k++;
        }
    }
}

void half(int head, int tail, int* parent, int* child) {
/*
从父数组中复制指定长度的元素至子数组
parameter:  head - 父数组的起始位置
            tail - 父数组的结束位置
            parent - 夫数组
            child - 子数组
输出：无
*/
    for(int i = 0; head < tail; i++, head++) {
        child[i] = parent[head];
    }
}






