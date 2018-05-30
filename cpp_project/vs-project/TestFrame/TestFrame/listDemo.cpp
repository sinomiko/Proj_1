#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
	unsigned int id;
	char citizen_id[19];
	char name[32];
	char address[128];
	unsigned int balance; // 余额

	Account* next; 
};

// -1, 表示输入有误。0，表示输入正确。
// 1, 表示中断输入
int input(Account* acc)
{
	char buf[128];

	// 输入ID
	printf("ID: ");
	gets(buf);
	acc->id = atoi(buf); //a to i
	if(acc->id == 0)
	{
		return 1;
	}

	// 输入身份证号
	printf("身份证号: ");
	gets(acc->citizen_id);

	// 有效性检测
	if(strlen(acc->citizen_id) != 4)
	{
		printf("请输入18位的身份证号!\n");
		return -1;
	}

	// 输入名称
	printf("名称: ");
	gets(acc->name);

	printf("地址: ");
	gets(acc->address);

	printf("余额: ");
	gets(buf);
	acc->balance = atoi(buf); //a to i

	return 0;
}

Account m_head = {0}; // 有头链表的头节点

void add(const Account* acc)
{
	// 创建一个对象
	Account* pnew = (Account*)malloc(sizeof(Account));
	*pnew = *acc; // 拷贝数据s

	// 把新节点添加到链表中
	pnew->next = m_head.next;
	m_head.next = pnew;
}

Account* find(const char* name)
{
	Account* p = m_head.next;
	while(p)
	{
		if( strcmp (name, p->name) == 0 )
		{
			return p;
		}
		p = p->next;
	}

	return NULL;
}

int main()
{
	// 接收用户输入, 保存到链表
	while(1)
	{
		Account acc;
		int ret = input(&acc);
		if(ret == 1)
		{
			break;
		}
		else if(input(&acc) < 0)
		{
			printf("**** 错误的输入 ****!\n");
		}
		else
		{
			add(&acc);
			printf(" 加入节点 !!! \n");
		}
	}

	// 查找
	char buf[128];
	printf("输入要查找名字: ");
	gets(buf);
	Account* p = find(buf);
	if(p != NULL)
	{
		printf("找到帐户\n");
		printf("ID: %d, 名字: %s \n", p->id, p->name);
	}
	else
	{
		printf("无此帐户!\n");
	}
	return 0;
}