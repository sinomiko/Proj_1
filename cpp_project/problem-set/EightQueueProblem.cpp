#include <iostream>
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

int main(void)
{
    Queue(0);
    getchar();
    return 0;
}