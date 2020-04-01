#include "fs.h"
using namespace std;


extern f_node *current;

void move_current(int son_id){
    current=current->node_son[son_id]; 
}

int subf_cd(f_node *tim,char *ch_arr,int lef,int rig,int typ){ //lef to rig-1
    char buf[8],*f_ptr; int now=lef;
    if(now>=rig) return 0;
    while(now<rig){
        if(ch_arr[now]=='/'){ now++; break;} 
        buf[now-lef]=ch_arr[now];
        now++;
    }
    for(int i=0;i<tim->siz_son;i++){
        if(tim->node_son[i]->i_file->Dir_Ext[0]!='_') continue; 
        f_ptr=tim->node_son[i]->i_file->Dir_Name;

        if(!strcmp(f_ptr,buf) || (!strcmp(buf,".") && !i) 
                || (!strcmp(buf,"..") && i==1)){
            cout<<"$"<<buf<<endl;
            if(typ) return subf_cd(tim->node_son[i],ch_arr,now,rig,typ);
            move_current(i); subf_cd(tim->node_son[i],ch_arr,now,rig,typ); 
            return 0; 
        }
    }
    cout<<"typ="<<typ<<endl; 
    printf("no find this dir.\n");
    return 1; 
}

int func_cd(char *limv){
    char *tmp=limv;int len=strlen(tmp);
    if(tmp[0]=='/') return -1;
    int error=subf_cd(current,tmp,0,len,1); 
    if(error) return error;
    subf_cd(current,tmp,0,len,0);
    return 0;
}

int func_ls(){
    File *tim; 
    for(int i=2;i<current->siz_son;i++){
        tim=current->node_son[i]->i_file;
        if(tim->Dir_Ext[0]=='_') 
            printf("%s ",tim->Dir_Name);
        else 
            printf("%s.%s ",tim->Dir_Name,tim->Dir_Ext);
    }
    puts(""); 
    return 0; 
}

void current_new_dir(f_node *&x,char *limv){
    File *tim;
    x->node_son[x->siz_son]=new f_node();
    x->node_son[x->siz_son]->siz_son=2; 
    x->node_son[x->siz_son]->node_son[0]=x->node_son[x->siz_son];
    x->node_son[x->siz_son]->node_son[1]=x; 
    x->node_son[x->siz_son]->i_file=new File();
    tim=x->node_son[x->siz_son]->i_file;
    x->siz_son++;
    strcpy(tim->Dir_Name,limv);
    tim->Dir_Ext[0]='_'; 
    // tim->... = ...
}

int func_mkdir(char *limv){
    File *tim; 
    for(int i=2;i<current->siz_son;i++){
        tim=current->node_son[i]->i_file;
        if(tim->Dir_Ext[0]=='-' && !strcmp(limv,tim->Dir_Name)){
            printf("this dir is already exist.\n");
            return 1; 
        }
    }
    current_new_dir(current,limv); 
    return 0;
}

void current_new_file(f_node *&x,char *limv){
    File *tim;
    x->node_son[x->siz_son]=new f_node();
    x->node_son[x->siz_son]->siz_son=0; 
    x->node_son[x->siz_son]->i_file=new File();
    tim=x->node_son[x->siz_son]->i_file;
    x->siz_son++;
    int div=0, len=strlen(limv);
    while(div<len) if(limv[div++]=='.') break; 
    strncpy(tim->Dir_Name,limv,div-1);  
    for(int i=div;i<len;i++)
        tim->Dir_Ext[i-div]=limv[i]; 
    // tim->... = ...
}

int func_touch(char *limv){
    File *tim; char Full_name[20];
    for(int i=2;i<current->siz_son;i++){
        tim=current->node_son[i]->i_file;
        strcpy(Full_name,tim->Dir_Name);
        strcat(Full_name,".");
        strcat(Full_name,tim->Dir_Ext); 
        if(!strcmp(limv,Full_name)){
            printf("this dir is already exist.\n");
            return 1; 
        }
    }
    current_new_file(current,limv); 
    return 0; 
}

int my_shell(char *command,int limc,char *limv[]){
    if(!strcmp(command,"cd")){
        if(limc!=1) return -1; 
        return func_cd(limv[0]);
    }
    if(!strcmp(command,"ls")){
        if(limc!=0) return -1; 
        return func_ls();
    } 
    if(!strcmp(command,"mkdir")){
        if(limc!=1) return -1; 
        return func_mkdir(limv[0]); 
    }
    if(!strcmp(command,"touch")){
        if(limc!=1) return -1; 
        return func_touch(limv[0]); 
    }
    return -1;

    return 0;/**/
}


