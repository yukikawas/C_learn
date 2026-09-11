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



/*
===== C猜数字游戏 学习笔记 【第二个C程序】=====
1. 头文件
stdio.h  : printf / scanf / getchar 输入输出
stdlib.h : rand() 随机数、srand()设置随机种子
time.h   : time(NULL) 获取当前时间，用来做随机种子
> srand((unsigned)time(NULL)); 只需要在main调用一次，不要放到循环/play里面！

2. 随机数公式
rand() % 100 + 1  → 生成 [1,100] 的整数
rand()%n → 范围 0 ~ n-1

3. 输入缓冲区核心知识点（C特有，Python input自动处理）
scanf读取数字，会把【回车换行符 \n】残留在输入缓冲区
getchar() 会读到残留的\n，造成自动跳过输入！
标准安全清空缓冲区模板：
int tmp;
while ((tmp = getchar()) != '\n' && tmp != EOF);
⚠️ 变量必须用int，不能char，因为EOF = -1，char存不下！

4. scanf返回值ret
int ret = scanf("%d", &guess);
ret=1 ：成功读到1个整数
ret!=1：用户输入字母/符号，读取失败，需要清空缓冲区再继续

5. 数组作为函数参数
void printhistory(int history[], int count)
数组传参本质是传【首地址】，不是完整拷贝数组
函数内修改数组，外面原数组会跟着变（和普通变量传副本完全不同）

6. 传值 vs 传地址
普通int变量传递：传【副本】，函数内部修改不影响外部
数组：隐式传地址

7. const修饰
const int MAX_TRY 常量，运行期间不能修改

8. 循环
while(1) 死循环，靠break跳出；continue直接回到循环开头

9. 函数拆分思想
把一局游戏逻辑封装进play()，解耦，方便复用，结构化编程

10. 边界坑点
① getchar返回类型是int，不是char
② 非法输入不清空缓冲区会无限死循环
③ 判断y/n的时候，大小写兼容 ch == 'y' || ch == 'Y'

11. 数组越界保护
history[100]，最多存100次猜测，本项目MAX_TRY=10，安全
*/
/*
新增知识点：输入范围校验
if (guess < 1 || guess > 100)
- || 逻辑或，满足任意一个条件就成立
- continue：直接跳到while循环开头，后面代码不执行
当前逻辑：超出范围的数字，不消耗attempts次数，也不存入history历史数组
如果想要越界猜测也记录进历史，就把history赋值语句放到这个if判断前面

运算符优先级小提醒：
> < >= <= 高于 || &&
所以 guess <1 || guess>100 不用额外加括号

scanf返回值判断：
ret != 1 代表读取失败（输入字母符号），此时要清空缓冲区，防止死循环
*/
