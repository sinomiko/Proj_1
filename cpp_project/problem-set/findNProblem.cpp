#include <iostream>
#include <stdio.h>
using namespace std;

double getMedian(int arr1[], int arr2[], int n)

{
    int i = 0, j = 0; //�ֱ��� arr1�� arr2�ĵ�ǰ�±�
    int m1 = -1, m2 = -1; //����������λ��. ������2n�����϶���������λ��
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

/* ������A��B��������λ�� */
int find_median(int *A, int *B, int m, int n, int s, int t)
{
    int  p, c;

    c = (m + n - 1) / 2;  /* �ж��ٸ���С������λ�� */
    p = (s + t) / 2;

    /* �������λ������A�У��ʹ�����B�� */
    if (s > t) {
        return find_median(B, A, n, m, 0, n - 1);
    }

    /* ����A����p����С��A[p], ���ҽ�������B����c-p����С��A[p], A[p]������λ�� */
    if (A[p] >= B[c - p - 1] && A[p] <= B[c - p]) {
        return A[p];
    }

    /* A[p]̫С�ˣ�������A����һ������������� */
    if (A[p] < B[c - p - 1]) {
        return find_median(A, B, m, n, p + 1, t);
    }

    /* A[p]̫���ˣ�������A����һ����С�������� */
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