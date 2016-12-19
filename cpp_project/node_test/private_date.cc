/*************************************************************************
	> File Name: private_date.c
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Fri 16 Dec 2016 04:14:13 AM PST
 ************************************************************************/

#include <string>
#include <functional>
#include <iostream>
#include "string.h"

struct PrivateData
{
  size_t m_hash;
  char m_pswd[100];
};

void doSmth(PrivateData& data)
{
  std::string s(data.m_pswd);
  std::hash<std::string> hash_fn;

  data.m_hash = hash_fn(s);
}

int funcPswd()
{
  PrivateData* data = new PrivateData();
  std::cin >> data->m_pswd;
  doSmth(*data);
  memset(data, 0, sizeof(PrivateData));
  delete data;
  return 1;
}

int main()
{
  funcPswd();
  return 0;
}
