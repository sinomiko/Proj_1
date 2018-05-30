#include <iostream>

using namespace std;

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
int getMedia(int* a, int* b, int alen,int blen, int start, int end)
{
	int m = ( alen + blen - 1 ) / 2;
	int p = ( start + end ) / 2;
	
	if(end >start)
	{
		return getMedia(b, a, blen, alen, 0, blen-1);
	}
	if(a[p] > b[c-p-1] && a[p] < b[c-p])
	{
			return a[p];
	}
	if(a[p] <b[c-p-1])
	{
		return getMedia(a, b, alen, blen, p+1, end);
	}
	
	return getMedia(a, b, alen, blen, start, p-1);
}

int main()
{
    trail();
    getchar();
    return 0;
}