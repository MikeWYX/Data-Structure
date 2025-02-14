#include <iostream>
using namespace std;

#define MAX_STRLEN 256
typedef struct{
    char str[MAX_STRLEN];
    int length;
}StringType;

void initstring(StringType &s){     //初始化字符串
    char temp;
    s.length=0;
    cout<<"请输入字符串:"<<endl;
    while((temp=getchar())!='\n'){      //逐字符读入便于统计长度
        s.str[s.length++]=temp;
    }
    s.str[s.length]='\0';       //末尾添上结束标志
}

void clearstring(StringType &s){        //清为空串
    s.length=0;
    s.str[0]='\0';
}        

void getnext(StringType s,int *next){       //计算kmp算法的next数组
    int i,j;
    if(s.length==0){
        cout<<"s不存在"<<endl;
        return;
    } 
    next[0]=-1;
    for(i=1;i<s.length;i++){
        j=i-1;
        while(j!=0||next[j]!=-1){
            if(s.str[j]==s.str[next[j]]){
                break;
            }
            j=next[j];
        }
        next[i]=next[j]+1;
    }
}

int kmp(StringType s,StringType t){     //kmp匹配,返回值为在s中的位置
    int next[MAX_STRLEN],i=0,j=0;
    getnext(t,next);
    while((i<s.length)&&(j<t.length)){
        if(s.str[i]==t.str[j]){
            i++;
            j++;
        }
        else{
            if(j==-1){
                i++;
                j++;
            }
            else{
                j=next[j];   
            }
        }
    }
    if(j==t.length)
        return i-j;
    return -1;
}

void substring(StringType s,StringType &t,int pos,int length){      //从s第pos个字符起长为length的字串存入t
    for(t.length=0;t.length<length&&s.str[pos+t.length-1]!='\0';t.length++){        //若length位超过s则只取s有效部分
        t.str[t.length]=s.str[pos+t.length-1];
    }
    t.str[t.length]='\0';       //最后置结束符
    cout<<t.length<<endl;
}

void replace(StringType &s,StringType t,StringType v){      //将s中的t字串全部替换为v
    int pos,i,j;
    if(t.length<v.length){      //替换后s比原来长，字符需要后移
        while((pos=kmp(s,t))!=-1){
            for(i=s.length;i>=pos+t.length;i--){     //从后向前开始后移
                s.str[i+v.length-t.length]=s.str[i];
            }
            s.length=s.length+v.length-t.length;        //更新字符串s的长度
            for(i=pos;i<pos+v.length;i++){
                s.str[i]='*';
            }
            //cout<<s.str<<endl;
        }
        for(i=0,j=0;i<s.length;i++){
            if(s.str[i]=='*'){
                s.str[i]=v.str[j];
                j=(j+1)%v.length;
            }
        }
    }
    if(t.length>v.length){      //替换后s比原来短，字符需要前移
        while((pos=kmp(s,t))!=-1){
            for(i=pos+t.length;i<=s.length;i++){     //从前向后开始前移
                s.str[i+v.length-t.length]=s.str[i];
            }
            s.length=s.length+v.length-t.length;        //更新字符串s的长度
            for(i=pos;i<pos+v.length;i++){
                s.str[i]='*';
            }
            //cout<<s.str<<endl;
        }
        for(i=0,j=0;i<s.length;i++){
            if(s.str[i]=='*'){
                s.str[i]=v.str[j];
                j=(j+1)%v.length;
            }
        }
    }
    if(t.length==v.length){     //替换前后长度不变
        while((pos=kmp(s,t))!=-1){
            for(i=pos;i<pos+t.length;i++){
                s.str[i]='*';
            }  
            //cout<<s.str<<endl;       
        } 
        for(i=0,j=0;i<s.length;i++){
            if(s.str[i]=='*'){
                s.str[i]=v.str[j];
                j=(j+1)%v.length;
            }
        }  
    }
}

void cat(StringType &s,StringType t){       //将t连在s后并存入s
    if(s.length+t.length>MAX_STRLEN){
        cout<<"error";
        return;
    }
    for(int i=0;i<=t.length;i++){
        s.str[s.length+i]=t.str[i];
    }
    s.length+=t.length;     //修改s长度
}

void traverse(StringType s){        //遍历字符串
    cout<<s.str;
}

#define BLOCK_SIZE 4

typedef struct Blstrtype{       //块结点类型定义
    char data[BLOCK_SIZE];
    Blstrtype *next;
}BNODE;

typedef struct{     //块链串类型定义
    BNODE *head;        //头指针
    int Strlen;     //当前长度
}Blstring;

void traverse2(Blstring s);

void initblstring(Blstring &s){
    BNODE *current,*tempbnode;
    char temp;
    int i=0;
    s.head=new BNODE;
    current=s.head;
    s.Strlen=0;
    cout<<"请输入字符串:"<<endl;
    while((temp=getchar())!='\n'){
        if(i==BLOCK_SIZE){
           tempbnode=new BNODE;     //为新块结点开辟空间
           current->next=tempbnode;     
           current=tempbnode;       //current移到下一结点
           i=0;     //i归0
        }
        current->data[i++]=temp;        //块结点对应位置存入并后移一位
        s.Strlen++;
    }
    if(i==BLOCK_SIZE){
           tempbnode=new BNODE;     //为新块结点开辟空间
           current->next=tempbnode;     
           current=tempbnode;       //current移到下一结点
           i=0;     //i归0
    }
    current->data[i]='\0';      //置结束标志
    current->next=NULL;
}

void destroy(Blstring &s){
    BNODE *temp,*current;
    temp=s.head;
    while(!temp){
        current=temp;
        temp=temp->next;
        delete current;
    }
}

void clear(Blstring &s){
    s.Strlen=0;
    s.head->data[0]='\0';
    s.head->next=NULL;
}

int blstrlen(Blstring &s){
    return s.Strlen;
}

char locate(Blstring s,int loc){        //返回块链s中位置locate的data值
    int i=0;
    for(;loc>0;loc--){
        i++;
        if(i==BLOCK_SIZE){
            s.head=s.head->next;
            i=0;
        }
    }
    return s.head->data[i];
}

void getnext2(Blstring s,int *next){       //计算kmp算法的next数组
    int i,j;
    char temp1,temp2;
    if(s.Strlen==0){
        cout<<"s不存在"<<endl;
        return;
    } 
    next[0]=-1;
    for(i=1;i<s.Strlen;i++){
        j=i-1;
        while(j!=0||next[j]!=-1){
            temp1=locate(s,j);
            temp2=locate(s,next[j]);
            if(temp1==temp2){
                break;
            }
            j=next[j];
        }
        next[i]=next[j]+1;
    }
}

int kmp2(Blstring s,Blstring t){     //kmp匹配
    int next[MAX_STRLEN],i=0,j=0;
    getnext2(t,next);
    while(locate(s,i)!='\0'&&locate(t,j)!='\0'){
        if(locate(s,i)==locate(t,j)){
            i++;
            j++;
        }
        else{
            if(j==-1){
                i++;
                j++;
            }
            else{
                j=next[j];   
            }
        }
    }
    if(j==t.Strlen)
        return i-j;
    return -1;
}

void substring2(Blstring s,Blstring &t,int pos,int length){      //从s第pos个字符起长为length的字串存入t
    int i=0,j;
    BNODE *current,*tempbnode;
    if(pos>s.Strlen){
        cout<<"error"<<endl;
        return;
    }
    t.head=new BNODE;
    current=t.head;
    t.Strlen=length;
    for(pos=pos-1;pos>0;pos--){     //第pos个字符在第pos-1位，在块链串中找到该位置
        i++;
        if(i==BLOCK_SIZE){
            s.head=s.head->next;
            i=0;
        }
    }
    for(j=0;length>0&&s.head->data!='\0';length--){
        if(i==BLOCK_SIZE){
            s.head=s.head->next;
            i=0;
        }
        if(j==BLOCK_SIZE){
           tempbnode=new BNODE;     //为新块结点开辟空间
           current->next=tempbnode;     
           current=tempbnode;       //current移到下一结点
           j=0;     //j归0
        }
        current->data[j]=s.head->data[i];
        i++;
        j++;
    }
    if(j==BLOCK_SIZE){
           tempbnode=new BNODE;     //为新块结点开辟空间
           current->next=tempbnode;     
           current=tempbnode;       //current移到下一结点
           j=0;     //j归0
    }
    current->data[j]='\0';
    current->next=NULL;
}

void replace2(Blstring &s,Blstring t,Blstring v){      //将s中的t字串全部替换为v
    int pos,i,j,k,count,currentpos;
    char former,current;
    BNODE *temp1,*temp2,*temp3;
    if(t.Strlen<v.Strlen){      //替换后s比原来长，字符需要后移
        while((pos=kmp2(s,t))!=-1){
            for(i=0;i<v.Strlen-t.Strlen;i++){
                temp1=s.head;
                for(j=0,k=0;j<pos+t.Strlen+i;j++){       //移动至需后移的第一位
                    k++;
                    if(k==BLOCK_SIZE){
                        temp1=temp1->next;
                        k=0;     //k归0
                    }
                    //cout<<"k="<<k<<endl;
                }
                temp2=temp1;
                former=temp2->data[k];
                for(currentpos=pos+t.Strlen+i;currentpos<=s.Strlen;currentpos+=v.Strlen-t.Strlen){
                    for(count=0;count<v.Strlen-t.Strlen;count++){
                        k++;
                        if(k==BLOCK_SIZE){
                            if(temp2->next==NULL){
                                temp3=new BNODE;
                                temp3->data[0]='\0';
                                temp3->data[1]='\0';
                                temp3->data[2]='\0';
                                temp3->data[3]='\0';
                                temp3->next=NULL;
                                temp2->next=temp3;
                                temp2=temp3;
                                //cout<<"xinjian"<<endl;
                            }
                            else{
                                temp2=temp2->next;
                                //cout<<"houyi"<<endl;
                            }
                            k=0;     //k归0
                        }
                        //cout<<"k="<<k<<endl;
                    }
                    current=temp2->data[k];
                    //cout<<"current="<<current<<endl;
                    temp2->data[k]=former;
                    former=current;
                }
            }
            s.Strlen=s.Strlen+v.Strlen-t.Strlen;        //更新字符串s的长度
            for(i=0,j=0,temp1=s.head;i<pos;i++){
                j++;
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
            }
            for(i=0;i<v.Strlen;i++){
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
                temp1->data[j]='*';
                //cout<<"存入"<'<temp1->data[j]<<endl;
                j++;
            }
        }
        temp1=s.head;
        for(i=0,j=0;i<s.Strlen;){
            if(j==BLOCK_SIZE){
                temp1=temp1->next;
                j=0;     //j归0
            }
            if(temp1->data[j]=='*'){
                temp2=v.head;
                for(count=0,k=0;count<v.Strlen;count++){
                    temp1->data[j]=temp2->data[k];
                    k++;
                    j++;
                    if(j==BLOCK_SIZE){
                        temp1=temp1->next;
                        j=0;     //j归0
                    }
                    if(k==BLOCK_SIZE){
                        temp2=temp2->next;
                        k=0;     //k归0
                    }
                    i++;
                }
                continue;
            }
            j++;
            i++;
        }
    }
    if(t.Strlen>v.Strlen){      //替换后s比原来短，字符需要前移
        while((pos=kmp2(s,t))!=-1){
            for(i=0,j=0,temp1=s.head;i<pos+t.Strlen;i++){       //移动至需前移的第一位
                //cout<<"j="<<j<<endl;
                j++;
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
            }
            for(i=0,k=0,temp2=s.head;i<pos+v.Strlen;i++){       
                //cout<<"k="<<k<<endl;
                k++;
                if(k==BLOCK_SIZE){
                    temp2=temp2->next;
                    k=0;     //k归0
                }
            }
            for(count=pos+t.Strlen;count<=s.Strlen;count++){
                temp2->data[k]=temp1->data[j];
                k++;
                j++;
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
                if(k==BLOCK_SIZE){
                    temp2=temp2->next;
                    k=0;     //k归0
                }
            }
            s.Strlen=s.Strlen+v.Strlen-t.Strlen;        //更新字符串s的长度
            for(i=0,j=0,temp1=s.head;i<pos;i++){
                j++;
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
            }
            for(i=0;i<v.Strlen;i++){
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
                temp1->data[j]='*';
                //cout<<"存入"<<temp1->data[j]<<endl;
                j++;
            }  
            //traverse2(s); 
        }
        temp1=s.head;
        for(i=0,j=0;i<s.Strlen;){
            if(j==BLOCK_SIZE){
                temp1=temp1->next;
                j=0;     //j归0
            }
            if(temp1->data[j]=='*'){
                temp2=v.head;
                for(count=0,k=0;count<v.Strlen;count++){
                    temp1->data[j]=temp2->data[k];
                    k++;
                    j++;
                    if(j==BLOCK_SIZE){
                        temp1=temp1->next;
                        j=0;     //j归0
                    }
                    if(k==BLOCK_SIZE){
                        temp2=temp2->next;
                        k=0;     //k归0
                    }
                    i++;
                }
                continue;
            }
            j++;
            i++;
        }
    }

    if(t.Strlen==v.Strlen){     //替换前后长度不变
        while((pos=kmp2(s,t))!=-1){
            for(i=0,j=0,temp1=s.head;i<pos;i++){
                j++;
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
            }
            for(i=0;i<v.Strlen;i++){
                if(j==BLOCK_SIZE){
                    temp1=temp1->next;
                    j=0;     //j归0
                }
                temp1->data[j]='*';
                //cout<<"存入"<<temp1->data[j]<<endl;
                j++;
            }      
        }
        temp1=s.head;
        for(i=0,j=0;i<s.Strlen;){
            if(j==BLOCK_SIZE){
                temp1=temp1->next;
                j=0;     //j归0
            }
            if(temp1->data[j]=='*'){
                temp2=v.head;
                for(count=0,k=0;count<v.Strlen;count++){
                    temp1->data[j]=temp2->data[k];
                    k++;
                    j++;
                    if(j==BLOCK_SIZE){
                        temp1=temp1->next;
                        j=0;     //j归0
                    }
                    if(k==BLOCK_SIZE){
                        temp2=temp2->next;
                        k=0;     //k归0
                    }
                    i++;
                }
                continue;
            }
            j++;
            i++;
        }   
    }
}

void cat2(Blstring &s,Blstring t){
    int i,j,k;
    BNODE *current,*tempbnode;
    current=s.head;
    for(i=s.Strlen,j=0;i>0;i--,j++){     //在块链串s中移到'\0'位置
        if(j==BLOCK_SIZE){
            current=current->next;
            j=0;
        }
    }
    s.Strlen+=t.Strlen;
    for(i=t.Strlen,k=0;i>=0;i--,j++,k++){       //赋值同时将t中'\0'也赋给s
        if(j==BLOCK_SIZE){
            tempbnode=new BNODE;     //为新块结点开辟空间
            current->next=tempbnode;     
            current=tempbnode;       //current移到下一结点
            j=0;
        }
        if(k==BLOCK_SIZE){
            t.head=t.head->next;
            k=0;
        }
        current->data[j]=t.head->data[k];
    }
}

void traverse2(Blstring s){
    for(int i=0;s.Strlen>0;i++,s.Strlen--){
        if(i==BLOCK_SIZE){
            s.head=s.head->next;
            i=0;
        }
        cout<<s.head->data[i];
    }
    cout<<endl;
}

int main(){
    Blstring a,b,c;
    initblstring(a);
    initblstring(b);
    initblstring(c);
    int next[10];
    replace2(a,b,c);
    traverse2(a);
    system("pause");
}