#include <iostream>
//https://www.cnblogs.com/steven_oyj/archive/2010/05/22/1741376.html
/*
1、概念
      回溯算法实际上一个类似枚举的搜索尝试过程，主要是在搜索尝试过程中寻找问题的解，当发现已不满足求解条件时，就“回溯”返回，尝试别的路径。

   回溯法是一种选优搜索法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并不优或达不到目标，就退回一步重新选择，这种走不通就退回再走的技术为回溯法，而满足回溯条件的某个状态的点称为“回溯点”。

     许多复杂的，规模较大的问题都可以使用回溯法，有“通用解题方法”的美称。

2、基本思想
   在包含问题的所有解的解空间树中，按照深度优先搜索的策略，从根结点出发深度探索解空间树。当探索到某一结点时，要先判断该结点是否包含问题的解，如果包含，就从该结点出发继续探索下去，如果该结点不包含问题的解，则逐层向其祖先结点回溯。（其实回溯法就是对隐式图的深度优先搜索算法）。

       若用回溯法求问题的所有解时，要回溯到根，且根结点的所有可行的子树都要已被搜索遍才结束。

       而若使用回溯法求任一个解时，只要搜索到问题的一个解就可以结束。

3、用回溯法解题的一般步骤：
    （1）针对所给问题，确定问题的解空间：

            首先应明确定义问题的解空间，问题的解空间应至少包含问题的一个（最优）解。

    （2）确定结点的扩展搜索规则

    （3）以深度优先方式搜索解空间，并在搜索过程中用剪枝函数避免无效搜索。

4、算法框架
 （1）问题框架

设问题的解是一个n维向量(a1,a2,………,an),约束条件是ai(i=1,2,3,…..,n)之间满足某种条件，记为f(ai)。
	  
（2）非递归回溯框架
 int a[n],i;
 初始化数组a[];
 i = 1;
 while (i>0(有路可走)   and  (未达到目标))  // 还未回溯到头
 {
     if(i > n)                                              // 搜索到叶结点
     {   
           搜索到一个解，输出；
     }
     else                                                   // 处理第i个元素
     { 
           a[i]第一个可能的值；
           while(a[i]在不满足约束条件且在搜索空间内)
           {
               a[i]下一个可能的值；
           }
           if(a[i]在搜索空间内)
          {
               标识占用的资源；
               i = i+1;                              // 扩展下一个结点
          }
          else 
         {
               清理所占的状态空间；            // 回溯
               i = i –1; 
          }
 }
  
（3）递归的算法框架
回溯法是对解空间的深度优先搜索，在一般情况下使用递归函数来实现回溯法比较简单，其中i为搜索的深度，框架如下

int a[n];
try(int i)
{
    if(i>n)
       输出结果;
     else
    {
       for(j = 下界; j <= 上界; j=j+1)  // 枚举i所有可能的路径
       {
           if(fun(j))                 // 满足限界函数和约束条件
             {
                a[i] = j;
              ...                         // 其他操作
                try(i+1);
              回溯前的清理工作（如a[i]置空值等）;
              }
         }
     }
}
*/
//八皇后问题
using namespace std;
#define  NUM 8
int a[NUM][NUM] = { 0 };
int sum = 0;

bool check(int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        if (a[i][c])
        {
            return false;
        }
    }

    for (int i = r, j = c; i >= 0 && j >= 0; i--, j--)
    {
        if (a[i][j])
        {
            return false;
        }
    }
    for (int i = r, j = c; i >= 0 && j < 8; i--, j++)
    {
        if (a[i][j])
        {
            return false;
        }
    }
    return true;
}

/*输出摆放结果*/
void print()
{
    cout << "solution: " << ++sum << endl;
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            if (a[i][j])
            {
                cout << "⊙ ";
            }
            else
            {
                cout << "× ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Queue(int r)
{
    if (r == NUM)
    {
        print();
        return;
    }
    for (int c = 0; c < NUM; c++)
    {
        if (check(r, c))
        {
            //
            a[r][c] = 1;
            Queue(r + 1);
            a[r][c] = 0;
            //
        }
    }
}


#include <stdio.h>
/*
https://blog.csdn.net/yangliuy/article/details/7194199
求两个等长有序数组的中位数的logN算法 分治法
题目：有两个长为n的非递减数组A和B，把B接在A的后面变成长为2n的数组C。设计算法求C的中位数（第n小数）。

思路：O(n)的算法很容易找到，关键是用二分的思想设计logn算法。这题关键是用好a和b数组中脚标和为定值的元素的大小关系。
            直观想法是：如果中位数在数组a中，
			那么若a[m]<b[n-m-2]，此时比a[m]小的数最多只有n-2个，即a[m]不可能为第n小数，
			偏小更新左界;若a[m]> b [n-m-1],此时比a[m]小的数至少有n个，a[m]不可能为第n小数，偏大更新右界;
			若a[m]介于b[n-m-2]与b [n-m-1]则a[m]恰好为第n小数。 中位数在数组b中的情况类似。
*/
int findNthNumber(int a[], int b[], int n){  
    int l = 0, r = n -1;  
    int m;  
    while(l <= r){  
        m = (l + r) / 2;  
        if(m == n - 1 || a[m] < b[n - m -2]){  
            //此时比a[m]小的数最多只有n-2个，即a[m]不可能为第n小数，偏小更新左界  
            l = m + 1;  
        }  
        else if (a[m] < b [n - m - 1]){  
            //此时比a[m]小的数恰好有n-1个，a[m]就是第n小数，返回  
            return a[m];  
        }  
        else r = m - 1;//此时比a[m]小的数至少有n个，即a[m]不可能为第n小数，偏大更新右界  
    }  
    //中位数在b数组中的情况，和上面类似  
    l = 0, r = n -1;  
    while(l <= r){  
        m = (l + r) / 2;  
        if(m == n - 1 || b[m] < a[n - m -2]){  
            l = m + 1;  
        }  
        else if (b[m] < a [n - m - 1]){  
            return b[m];  
        }  
        else r = m - 1;  
    }  
}  

//也可以取a[m]与b[n-m-2]中较大的一个，然后与a[m+1]和b[n-m-1]作比较，简化后的代码如下
int findNthNumber(int a[], int b[], int n){  
    int l = 0, r = n -1;  
    int m, tmp;  
    while(l <= r){  
        m = (l + r) / 2;  
        tmp = (a[m] < b [n - m - 2] ? b[n - m - 2] : a[m]);  
        //tmp取a[m]与b[n-m-2]中较大的一个，然后与a[m+1]和b[n-m-1]作比较  
        if(tmp > b [n - m - 1]){  
            r = m - 1;  
        }  
        else if(tmp > a [m + 1]){  
            l = m + 1;  
        }  
        else return tmp;  
    }  
}  

double getMedian(int arr1[], int arr2[], int n)

{
    int i = 0, j = 0; //分别是 arr1， arr2的当前下标
    int m1 = -1, m2 = -1; //保存两个中位数. 由于是2n个，肯定有两个中位数
    for (int cnt = 0; cnt <= n; cnt++)

    {
        if (i < n && (arr1[i] < arr2[j] || j >= n))

        {
            m1 = m2;
            m2 = arr1[i++];
        }

        else

        {
            m1 = m2;
            m2 = arr2[j++];
        }
    }
    return (m1 + m2) / 2.0;
}

/* 从数组A和B中找下中位数 */
int find_median(int *A, int *B, int m, int n, int s, int t)
{
    int  p, c;

    c = (m + n - 1) / 2;  /* 有多少个数小于下中位数 */
    p = (s + t) / 2;

    /* 如果下中位数不在A中，就从数组B找 */
    if (s > t) {
        return find_median(B, A, n, m, 0, n - 1);
    }

    /* 数组A中有p个数小于A[p], 当且仅当数组B中有c-p个数小于A[p], A[p]才是中位数 */
    if (A[p] >= B[c - p - 1] && A[p] <= B[c - p]) {
        return A[p];
    }

    /* A[p]太小了，从数组A中找一个更大的数尝试 */
    if (A[p] < B[c - p - 1]) {
        return find_median(A, B, m, n, p + 1, t);
    }

    /* A[p]太大了，从数组A中找一个更小的数尝试 */
    return find_median(A, B, m, n, s, p - 1);
}
/**
 *  \brief Brief description
 *  
 *  \return Return description
 *  
 *  \details More details
 *  
 *  
 */
 const int N = 8;//皇后的个数
int positon[N];//存放皇后的位置
int solCount = 0;//记录有多少种摆法

              /*判断第row行放置的位置是否满足要求*/
bool valid(int row)
{
    for (int i = 0; i < row; ++i)
    {
        // 如果和前面放好位置的不在同一列，也不在对角线上，则返回true，否则返回false
        if (positon[i] == positon[row] || abs(positon[i] - positon[row]) == abs(i - row))
            return false;
    }
    return true;
}

/*输出摆放结果*/
void print()
{
    cout << "这是第" << ++solCount << "种摆法：" << '\n';
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (positon[i] == j)
                cout << "⊙ ";
            else
                cout << "× ";
        }
        cout << '\n';
    }
    cout << endl;
}

/*回溯法搜索摆放位置*/
void trail(int row = 0)
{
    // 如果摆完完N行，则输出结果
    if (N == row)
    {
        print();
        return;
    }
    for (int column = 0; column < N; ++column)
    {
        positon[row] = column;// 放置在第row行第column列
                              // 如果满足条件，则进行下一行
        if (valid(row)) trail(row + 1);
        // 如果不满足条件，则进行下一次循环，即回溯回去在第row行重新寻找摆放的位置
    }
}
/**
输出字符串的全排列
 */
 #include <stdio.h>  

void swap2(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
/* 打印字符串的全排列*/
void permute(char *str, int i, int n)
{
    int j;
    if (i == n)
        printf("%s\n", str);
    else
    {
        for (j = i; j <= n; j++)
        {
            swap2((str + i), (str + j));
            permute(str, i + 1, n);
            swap2((str + i), (str + j)); //回溯  
        }
    }
}

int main()
{
	/*****八皇后********/
	Queue(0);
    /******查找中位数N*******/
	int ar1[] = { 1, 12, 15, 26, 38 };
    int ar2[] = { 2, 13, 17, 30, 45 };

    int n1 = sizeof(ar1) / sizeof(ar1[0]);
    int n2 = sizeof(ar2) / sizeof(ar2[0]);

    printf("%d\n", find_median(ar1, ar2, n1, n2, 0, n1-1));
	
	/*****全排列********/
	char str[] = "ABC";
    int len = sizeof(str) / sizeof(char) - 2;
    permute(str, 0, len);
	
    getchar();
    return 0;
}
