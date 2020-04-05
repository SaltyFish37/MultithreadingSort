#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define MaxSize 1000

typedef struct {
    int* num;
    int first;
    int mid;
    int last;
    int* merge_num;
}paras;

int* dataFromFile(char *argv[]);
int* dataFromInput(void);
void getNum(char* str, int *num);
void QuickSort(int R[],int s,int t);
int partition(int R[],int s,int t);
void merge(int num[], int first, int mid, int last, int merge_num[]);
void *runnerL(void* arg);
void *runnerR(void* arg);
void multiThreading(paras* args);

int size = 0;

int main(int argc, char *argv[]) {
    int* num;
    paras args;

    if(argc == 2) {
        num = dataFromFile(argv);
    } else {
        num = dataFromInput();
    }

    printf("before(%d):", size);
    for(int i = 0; i < size; i++) {
        printf("%d ", num[i]);
    }

    int* merge_num;
    merge_num = (int*)malloc(sizeof(int) * size);
    args.num = num;
    args.first = 0;
    args.mid = size/2 - 1;
    args.last = size-1;
    args.merge_num = merge_num;

    multiThreading(&args);

    printf("\nafter(%d):", size);
    for(int i = 0; i < size; i++) {
        printf("%d ", args.merge_num[i]);
    }
    printf("\n");

    free(num);
    free(merge_num);
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

    int j = 0;
    char calc[strlen(str)];
    strcpy(calc, str);
    for(int i = 0; i < strlen(calc); i++) {
        if ((calc[i] < '0' || calc[i] > '9') && calc[i] != '-') {
            if (calc[i-1] < '0' || calc[i-1] > '9') {
                calc[i] = ' ';
                continue;
            }
            size++;
            for(; j <= i; j++) {
                calc[j] = ' ';
            }
        }
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

    int j = 0;
    char calc[strlen(str)];
    strcpy(calc, str);
    for(int i = 0; i < strlen(calc); i++) {
        if ((calc[i] < '0' || calc[i] > '9') && calc[i] != '-') {
            if (calc[i-1] < '0' || calc[i-1] > '9') {
                calc[i] = ' ';
                continue;
            }
            size++;
            for(; j <= i; j++) {
                calc[j] = ' ';
            }
        }
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
    int k = 0, j = 0;
    for(int i = 0; i < strlen(str); i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '-') {
            if (str[i-1] < '0' || str[i-1] > '9') {
                str[i] = ' ';
                continue;
            }
            num[k] = atoi(str);
            k++;
            for(; j <= i; j++) {
                str[j] = ' ';
            }
        }
    }
}

int partition(int R[],int s,int t) {
/*
设定一个分界值，通过该分界值将数组分成左右两部分
parameter: R：待划分数组
           s：数组中的起始位置
           t：数组中的结束位置
输出：划分出的中点
*/
	int i = s,j = t;
	int tmp = R[i];
	while (i<j) {	
        while (j>i && R[j] >= tmp)
			j--;
		R[i]=R[j];
		while (i<j && R[i] <= tmp)
			i++;
		R[j]=R[i];
	}
	R[i]=tmp;
	return i;
}
void QuickSort(int R[],int s,int t) {
/*
对R[s..t]的元素进行快速排序
parameter: R：待排序数组
           s：数组中的起始位置
           t：数组中的结束位置
输出：无
*/
    int i;
	int tmp;
	if (s<t) {	
		i=partition(R,s,t);
		QuickSort(R,s,i-1);
		QuickSort(R,i+1,t);
	}
}

void merge(int num[], int first, int mid, int last, int merge_num[]) {
/*
将排好序的数组合并
parameter: num：原数组，前一半和后一半已分别排好序
           first：起始位置
           mid：中间位置（与快排相一致）
           last：结束位置
           merge_num：存放结果的数组
输出：无
*/
	int i = first, j = mid + 1;
	int m = mid,   n = last;
	int k = 0;
	
	while (i <= m && j <= n)
	{
		if (num[i] <= num[j])
			merge_num[k++] = num[i++];
		else
			merge_num[k++] = num[j++];
	}
	
	while (i <= m)
		merge_num[k++] = num[i++];
	
	while (j <= n)
		merge_num[k++] = num[j++];
}

void *runnerL(void* arg) {
/*
子线程，将参数转换并传给快排函数
*/
    paras* args = (paras*)arg;
	QuickSort((*args).num, (*args).first, (*args).mid);
}
void *runnerR(void* arg) {
/*
子线程，将参数转换并传给快排函数
*/
    paras* args = (paras*)arg;
	QuickSort((*args).num, (*args).mid, (*args).last);
}
void multiThreading(paras* args) {
/*
创建子线程,用快排分别对数组的前一半和后一半进行排序
*/
	pthread_t child_1;
	pthread_t child_2;
	pthread_create(&child_1,NULL,runnerL,args);
	pthread_create(&child_2,NULL,runnerR,args);
	pthread_join(child_1,NULL);
	pthread_join(child_2,NULL);
	merge((*args).num, (*args).first, (*args).mid, (*args).last, (*args).merge_num);
}

