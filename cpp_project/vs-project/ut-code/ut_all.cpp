#include<stdio.h>
#include<string.h>
#include <iostream>
#include <vector>
#include<string.h>
using namespace std;
void makeNext(const char P[],int next[])
{
    int q,k;
    int m = strlen(P);
    next[0] = 0;
    for (q = 1,k = 0; q < m; ++q)
    {
        while(k > 0 && P[q] != P[k])
            k = next[k-1];
        if (P[q] == P[k])
        {
            k++;
        }
        next[q] = k;
    }
}

int kmp(const char T[],const char P[],int next[])
{
    int n,m;
    int i,q;
    n = strlen(T);
    m = strlen(P);
    makeNext(P,next);
    for (i = 0,q = 0; i < n; ++i)
    {
        while(q > 0 && P[q] != T[i])
            q = next[q-1];
        if (P[q] == T[i])
        {
            q++;
        }
        if (q == m)
        {
            printf("Pattern occurs with shift:%d\n",(i-m+1));
        }
    } 
    return 0;
}

template<typename T>
void print(T value){
    cout << value << endl;
}
/*
template<typename T, typename ... Args>
void print(T value, Args .... args){
    cout << value << endl;
    print(args...);
}*/
static inline size_t
round_up_pow2m1_size(size_t v)
{
    v |= (v >> 1);

    v |= (v >> 2);

    v |= (v >> 4);

    v |= (v >> 8);
 
    v |= (v >> 16);

    if (sizeof(v) == 8) {
        v |= (v >> 32);
    }
    return v;
}

static inline size_t
round_up_pow2_size(const size_t v)
{
    return round_up_pow2m1_size(v - 1) + 1;
}

int check_fragment(int fragment_packet)
{
    if((fragment_packet & 0x70)>0){
        if(fragment_packet>>7 == 0){
            int send_frag = (fragment_packet & 0x70 )>>4;
            if((fragment_packet & 0x0f) < send_frag ){
                fragment_packet |= (fragment_packet &0x0f)+1;
                goto clean;
            }else{
                fragment_packet = 0;
                cout<<"fragment ok"<<endl;
            }
        }
    }
 clean:
    return fragment_packet;
}

unsigned int calc_frag_pkts_num( int pktlen, int version, unsigned int mtu)
{
    uint16_t max_data_len;
    if(version==4){
        max_data_len = mtu - 20;
    }else{
        max_data_len = mtu - 48;
    }
    max_data_len &= ~0x07;
    cout<<"max_data_len:"<<max_data_len<<endl;
    return ((pktlen + max_data_len - 1) / max_data_len -1 );
}

void test_frag()
{
    int pkt_len = 1447;
    int ip_version = 6;
    int mtu = 1500;
    int extra_frag = calc_frag_pkts_num(pkt_len,ip_version,mtu);
    cout<<"pkt_len:"<<pkt_len<<" ip_version:"<<ip_version<<" mtu:"<<mtu<<" extra fragment packet:"<<extra_frag<<endl;
    
    int frag_flag = extra_frag << 4;
    cout<<"frag_flag:"<<frag_flag<<endl;
    
    cout<<"========================"<<endl;
	int result=check_fragment(frag_flag);
	cout<<"result:"<<result<<endl;
    result=check_fragment(result);
	cout<<"result:"<<result<<endl;
    result=check_fragment(result);
	cout<<"result:"<<result<<endl;
    
    int lol = 1 << 7;
    cout<<"LOL:"<<lol<<endl;
}
/*
int len( char* ptr){
    cout<<"before:"<<static_cast<void *>(ptr)<<endl;
    *ptr++;
    cout<<"out"<<*ptr<<endl;
    cout<<"end:"<<static_cast<void *>(ptr)<<endl;
    return 0;
}*/
int main()
{
    /*
    int i;
    int next[20]={0};
    char T[] = "ababxabcdabdbababcadfdsss";
    char P[] = "abcdabd";
    printf("%s\n",T);
    printf("%s\n",P );
    // makeNext(P,next);
    kmp(T,P,next);
    for (i = 0; i < strlen(P); ++i)
    {
        printf("%d ",next[i]);
    }
    printf("\n");
*/
    /*
    int a=1024*8*8,b=45,c=61;
    printf("a=%d b=%d c=%d \n",a,b,c);
    a=round_up_pow2_size(a);
    b=round_up_pow2_size(b);
    c=round_up_pow2_size(c);
    printf("a=%d b=%d c=%d \n",a,b,c);
    */
    /*
    unsigned int a;
    a=(1<<31);
    if((a*2)<1024)
        printf("error \n");
     */
    /*
    char *a=new char[20];
    char *p="hello world";
    memcpy(a,p,12);
    cout<<a<<endl;
    cout<<static_cast<long long>(*p)<<endl;
    cout<<static_cast<long long>(p[3])<<endl;
    cout<<sizeof(*p)<<endl;
    cout<<"AAA:"<<static_cast<void *>(a)<<endl;
    
    len(a+1);
    
    cout<<"BBB:"<<static_cast<void *>(a)<<endl;
    */
    /*
    unsigned long a=0x01;
    unsigned long b=a<<7;
    cout<<"size out:"<<sizeof(unsigned long)<<endl;
    printf("b=%04x",b);
    */
    /*
    unsigned long a=9;
    unsigned long b=4;
    cout<<"size out:"<<(a+b-1)/b<<endl;
    */
    test_frag();
    return 0;
}