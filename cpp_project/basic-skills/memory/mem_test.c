#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Table{
int id;

char* name;
}Table;

static Table* new_table()
{
    Table *table = (Table *)malloc(sizeof(Table));
    if (!table) {
        printf("new_table_vport failed\n");
        return NULL;
    }

    memset(table, 0, sizeof(Table));
    table->id=1;

    table->name=(char*)malloc(sizeof(char)*10);
    memcpy(table->name,"hello",strlen("hello"));
    return table;
}

Table new_table2()
{
    Table table;
    table.id=2;

    table.name=(char*)malloc(sizeof(char)*10);
    memcpy(table.name,"world",strlen("world"));
    return table;
}

void main(void)
{
    Table* table1=new_table();
    printf("============================");
    printf("%s \n",table1->name);
    char* iptr = table1->name;
    printf("============================");
    printf("%s \n",iptr);
    free(table1->name);
    free(table1);
    printf("============================");
    printf("%s \n",iptr);
    printf("============================");
    printf("\n"); 

    Table table2=new_table2();
    printf("++++++++++++++++++++++++++++");
    printf("%s \n",table2.name);
    char* iptr2 = table2.name;
    printf("++++++++++++++++++++++++++++");
    printf("%s \n",iptr2);    
}

