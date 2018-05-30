#include <iostream>
#include <stdio.h>
using namespace std;

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

int main()
{
    int ar1[] = { 1, 12, 15, 26, 38 };
    int ar2[] = { 2, 13, 17, 30, 45 };

    int n1 = sizeof(ar1) / sizeof(ar1[0]);
    int n2 = sizeof(ar2) / sizeof(ar2[0]);
//     if (n1 == n2)
//         printf("Median is %lf", getMedian(ar1, ar2, n1));
//     else
//         printf("Doesn't work for arrays of unequal size");

    printf("%d\n", find_median(ar1, ar2, n1, n2, 0, n1-1));
    getchar();
    return 0;
}