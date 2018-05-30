#include <iostream>

using namespace std;

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