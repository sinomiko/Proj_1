#include <iostream>

using namespace std;

const int N = 8;//�ʺ�ĸ���
int positon[N];//��Żʺ��λ��
int solCount = 0;//��¼�ж����ְڷ�

              /*�жϵ�row�з��õ�λ���Ƿ�����Ҫ��*/
bool valid(int row)
{
    for (int i = 0; i < row; ++i)
    {
        // �����ǰ��ź�λ�õĲ���ͬһ�У�Ҳ���ڶԽ����ϣ��򷵻�true�����򷵻�false
        if (positon[i] == positon[row] || abs(positon[i] - positon[row]) == abs(i - row))
            return false;
    }
    return true;
}

/*����ڷŽ��*/
void print()
{
    cout << "���ǵ�" << ++solCount << "�ְڷ���" << '\n';
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (positon[i] == j)
                cout << "�� ";
            else
                cout << "�� ";
        }
        cout << '\n';
    }
    cout << endl;
}

/*���ݷ������ڷ�λ��*/
void trail(int row = 0)
{
    // ���������N�У���������
    if (N == row)
    {
        print();
        return;
    }
    for (int column = 0; column < N; ++column)
    {
        positon[row] = column;// �����ڵ�row�е�column��
                              // ��������������������һ��
        if (valid(row)) trail(row + 1);
        // ����������������������һ��ѭ���������ݻ�ȥ�ڵ�row������Ѱ�Ұڷŵ�λ��
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