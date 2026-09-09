/**
 * @file c_snippets.c
 * @brief C语言学习代码片段库（猜数字项目配套）
 * 用途：备忘、查阅、复制代码，附带知识点注释
 * 作者：学习笔记
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ====================== 片段1：清空输入缓冲区（高频！）======================
/*
 * 知识点：
 * getchar()每次读取1个字符，包含回车'\n'；返回int，因为EOF=-1
 * ch必须是int类型，不能char ch，否则EOF会出错
 * 作用：吃掉缓冲区残留字符，直到换行或者EOF，解决scanf残留回车bug
 */
void snippet_clear_buf(void)
{
    int ch;
    while( (ch = getchar()) != '\n' && ch != EOF );
}

// ====================== 片段2：安全读取整数（带非法输入处理）======================
/*
 * 返回值：读取成功返回读到的整数；读取失败返回-1
 * ret = scanf("%d", &var)：返回成功读到的变量个数
 * 读失败时，缓冲区残留垃圾字符，必须调用清空缓冲区函数
 */
int snippet_read_int(void)
{
    int num;
    int ret = scanf("%d", &num);
    if(ret != 1)
    {
        printf("输入不是合法整数！\n");
        snippet_clear_buf();
        return -1;
    }
    return num;
}

// ====================== 片段3：读取单个y/n字符（防止读到回车）======================
/*
 * 返回读到的字符（小写）
 * 要点：读字符之前先清空缓冲区，避免读到上次残留的'\n'
 */
char snippet_read_yesno(void)
{
    char opt;
    snippet_clear_buf();
    opt = getchar();
    // 转小写，统一判断
    if(opt >= 'A' && opt <= 'Z')
    {
        opt = opt + ('a' - 'A');
    }
    return opt;
}

// ====================== 片段4：随机数初始化 1~N ======================
/*
 * 重点：srand((unsigned)time(NULL)); 整个程序【只调用一次】！放在main最开头
 * rand() % range + offset
 * rand()%100 +1 → 1~100
 */
void snippet_rand_test(void)
{
    // srand((unsigned)time(NULL)); // main里面调用一次就够，不要放这里！
    int secret = rand() % 100 + 1;
    printf("随机数1~100 = %d\n", secret);
}

// ====================== 片段5：swap交换两个整数（指针传参）======================
/*
 * 普通变量传参是值拷贝，函数内部修改不会影响外部变量
 * 想要修改外部变量，传地址 &变量，形参用 int *p
 */
void snippet_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ====================== 片段6：动态内存 malloc / free ======================
/*
 * malloc 在堆上申请内存；用完必须free归还内存
 * malloc可能申请失败返回NULL，一定要判断
 * sizeof(int) 获取单个int占用字节
 */
void snippet_malloc_test(void)
{
    int count = 10;
    int *arr = (int *)malloc(count * sizeof(int));
    if(arr == NULL)
    {
        printf("内存申请失败\n");
        return;
    }
    // 使用数组 arr[0] ~ arr[9]
    arr[0] = 100;
    printf("arr[0]=%d\n", arr[0]);

    free(arr);
    arr = NULL; // 置空，防止野指针
}

// ====================== 片段7：数组作为函数参数（退化指针）======================
/*
 * 函数形参写 int history[] 等价于 int *history
 * 在函数内部 sizeof(history) 得到的是指针大小，不是数组长度！
 * 所以必须额外传入count，代表有效数据个数
 */
void snippet_print_array(int history[], int count)
{
    printf("sizeof history in function = %zu\n", sizeof(history));
    for(int i = 0; i < count; i++)
    {
        printf("%d ", history[i]);
    }
    printf("\n");
}

// ====================== 测试入口：main，可以单独运行测试各个片段 ======================
int main(void)
{
    srand((unsigned)time(NULL)); // 随机种子只初始化一次！

    printf("===== 测试读取整数 =====\n");
    int n = snippet_read_int();
    printf("读到数字：%d\n", n);

    printf("===== 测试y/n输入 =====\n");
    printf("输入 y or n：");
    char ch = snippet_read_yesno();
    printf("your choice: %c\n", ch);

    printf("===== 测试swap =====\n");
    int x=10,y=20;
    snippet_swap(&x,&y);
    printf("x=%d,y=%d\n",x,y);

    printf("===== 测试动态内存 =====\n");
    snippet_malloc_test();

    printf("===== 测试数组打印 =====\n");
    int arr[] = {1,2,3,4,5};
    int arr_len = sizeof(arr)/sizeof(arr[0]); // 只有原始数组在当前作用域才能算长度
    snippet_print_array(arr, arr_len);

    return 0;
}
