/*
  user: sky48
  language: c++
  for dream for young
*/

#include<iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

struct File {
  	char Dir_Name[8]; 
	char Dir_Ext[3];
	char Dir_Attr[1];
	char Keep_Bit[10];
	char Dir_WrtTime[2];
	char Dir_WrtDate[2];
	char Dir_FstClus[2];
	char Dir_FileSiz[4];
	// 32 bit   set dir's ext[0]='_'
};

struct f_node {
	File *i_file;
	f_node *node_son[15];// 0 is node_self, 1 is node_fa;
	unsigned int siz_son; 
	// file tree
}*current;
