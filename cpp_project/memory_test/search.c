#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include <unistd.h>
typedef enum __bool { false = 0, true = 1, } bool;

void * memmem(const void *l, size_t l_len, const void *s, size_t s_len, bool * flag)
{
    register char *cur, *last;
    const char *cl = (const char *)l;
    const char *cs = (const char *)s;

    /* we need something to compare */
    if (l_len == 0 || s_len == 0)
        return NULL;

    /* "s" must be smaller or equal to "l" */
    if (l_len < s_len)
        return NULL;

     /* special case where s_len == 1 */
    if (s_len == 1)
        return memchr(l, (int)*cs, l_len);
    /* the last position where its possible to find "s" in "l" */
    last = (char *)cl + l_len - s_len;

    for (cur = (char *)cl; cur <= last; cur++){
        putchar(cur[0]);
        if (cur[0] == cs[0] && memcmp(cur, cs, s_len) == 0){
            *flag = false;
            return cur;
        }
    }
    return NULL;
}


int main(int argc, char * argv)
{
    const unsigned char* const str = "qwer,tgnat#";
    unsigned char *  mark;
    bool flag = true;
    mark = memmem(str, strlen(str), "tgnat#", strlen("tgnat#"), &flag);
    if(!mark)
    mark = memmem(str, strlen(str), "tgnat>", strlen("tgnat>"), &flag);
    if(!mark)
        printf("not found \n");
    else
        printf("found \n");
    printf("flag: %d \n", flag);
    return 1;
}

