#include<stdio.h>
struct tableVport {
int dz_id;
int dp_id;
int vport_id;

struct   tableVport *next;
};

static struct tableVport* new_table_vport()
{
    struct tableVport *table_vport = (struct tableVport *)malloc(sizeof(struct tableVport));
    if (!table_vport) {
//        LTT_LOG(ERROR,VNET,"new_table_vport failed\n");
        return NULL;
    }

    memset(table_vport, 0, sizeof(struct tableVport));
    return table_vport;
}

void main(void)
{
    struct tableVport* table_vport[16];
    int i = 0;
    for( ; i < 16; i++)
    {
        table_vport[i]=new_table_vport();
    }
}

