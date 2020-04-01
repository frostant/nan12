/*
  user: sky48
  language: c++
  for dream for young
*/
#include "my_shell.cpp"
#include "error.cpp" 
using namespace std;

extern f_node *current;

char *limit[40],limi[40][40];
void init(){
	current=new f_node();
	current->siz_son=2;
	current->node_son[0]=current->node_son[1]=current; 
	current->i_file=new File();
	strcpy(current->i_file->Dir_Name,"root");
	current->i_file->Dir_Ext[0]='_';
	
}

int main ()
{
	init(); 
	char command[40]; int error=0,siz=0;
	for(int i=0;i<40;i++) limit[i]=limi[i];
	while(1){
		printf("orz$"); siz=0; 
		scanf("%s",command); 
		while(getchar()!='\n'){
			scanf("%s",limit[siz++]); 
		}
		error=my_shell(command,siz,limit);
		if(error) puts_error(error);
		else puts("ok"); 
	}
	return 0;
}

