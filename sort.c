#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 1000

int* dataFromFile(char *argv[]);
int* dataFromInput(void);
void split(char* str, int *num);

int size = 0;

int main(int argc, char *argv[]) {
    int* num;

    if(argc == 2) {
        num = dataFromFile(argv);
    } else {
        num = dataFromInput();
    }

//test
printf("after:");
for(int i = 0; i < size; i++) {
printf("%d ", num[i]);
}
printf("\nhello");
printf("\nhello");
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
    split(str, num);
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
    split(str, num);
    return num;
}

void split(char* str, int *num) {
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







