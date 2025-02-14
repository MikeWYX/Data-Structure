#include <iostream>
using namespace std;
#define elemtype int

typedef struct lnode{
    elemtype data;//结点的值域
    lnode *next;//结点的指针域
}linknode,*linklist;

void initlist(linklist &L){//初始化链表
    L=new linknode;
    L->next=NULL;
}

int listlength(linklist L){//计算链表长度
    int count=0;//计数
    while(L->next){//遍历链表，终止条件为最后一个结点指针域为空
        L=L->next;
        count++;
    }
    return count;
}

int listempty(linklist L){//判断链表是否为空，即头节点指针域是否指向有效结点
    return (L->next==NULL)?0:1;
}

void getelem(linklist L,int i,elemtype &e){//将链表中第n个元素赋值给e
    int count=1;//记录指针移动次数
    if(i<1){
        cout<<"input error";//说明i非法
        return;
    }
    while(count<i){
        if(!L->next)
            return;//说明i非法，超过链表长度
        L=L->next;
        count++;
    }
    e=L->data;
}

void clearlist(linklist &L){//将链表置空
    linknode *temp1,*temp2;
    temp1=L->next;
    L->next=NULL;//空链表头节点指针域为空
    for(;!temp1->next;temp1=temp2){//两个指针遍历链表一前一后指向相邻结点
        temp2=temp1->next;
        delete(temp1);
    }
}

void destroylist(linklist &L){//完全销毁链表
    clearlist(L);
    delete(L);//删去后续结点后删去头节点
}

linknode *locateelem(linklist L,elemtype e){//在链表中找到值域为data的结点并将指向它的指针返回
    while(L->next){//遍历链表
        L=L->next;
        if(L->data==e){//若循环结束仍然未结束函数，说明e不存在，报错
            return L;
        }
    }
    cout<<"e doesn't exist";
    return NULL;
}

linknode *priorelem(linklist L,linknode *cur){//在链表中寻找给定结点的前驱，以指针形式返回
    linknode *temp=L->next;
    while(temp){//遍历链表
        if(temp==cur)//temp为L的下一个结点，将temp一一与cur比较
            return L;
        temp=temp->next;
        L=L->next;
    }
    cout<<"input error";//若没找到说明输入结点不存在
    return NULL;
}

linknode *nextelem(linklist L,linknode *cur){//在链表中寻找给定结点的后继，以指针形式返回
    if(!cur){//判断结点是否合法
    cout<<"input error";
    return NULL;  
    }
    return cur->next;
}

void insertelem(linklist &L,int n,elemtype e){//在链表第n-1个结点后插入值域为e的结点
    int i;
    linknode *temp1,*temp2;
    temp1=new linknode;
    temp1->data=e;
    temp2=L;
    if(n<1){//判断n是否合法
        cout<<"input error";
        return;
    }
    for(i=1;i<n;i++){
        if(!temp2){//判断插入位置是否超过链表长度
            cout<<"input error";
            return;    
        }
        temp2=temp2->next;     
    }
    temp1->next=temp2->next;//指针移动结束时L指向第n-1个结点
    temp2->next=temp1;
}

int deleteelem(linklist &L,int n,elemtype &e){//删去链表中第n个元素
    int i;
    linknode *temp1=L,*temp2;
    if(n>listlength(L)||n<1){//判断n是否合法
    cout<<"input error";
    return 0;   
    }
    for(i=1;i<n;i++)//将temp1移动到删去结点的前驱
        temp1=temp1->next;
    temp2=temp1->next;
    temp1->next=temp2->next;//将被删去结点的前驱指针域重新定向
    e=temp2->data;
    delete(temp2);
    return 1;
}

void printlinknode(linknode *e){//打印结点的
    cout<<e->data;
}

void add2(linknode *e){//使结点e的值域加2
    e->data+=2;
}

void debuglinknode(linknode *p){//输出节点的地址及其值域
    cout<<"linknode_addr=value"<<endl;
    cout<<p<<"="<<p->data<<endl;
}

void listtraverse(linklist L,void(*ptrfunc)(linknode *ptr)){//遍历链表，并对每个节点用*ptrfunc所指向函数进行处理
    cout<<"链表长度为"<<listlength(L)<<endl;
    while(L->next){
        L=L->next;
        (*ptrfunc)(L);
    }
    cout<<endl;
}

int main(){
    void(*ptrfunc)(linknode *p)=debuglinknode;
    linklist first;
    initlist(first);
    listtraverse(first,ptrfunc);
    insertelem(first,1,2);
    insertelem(first,1,3);
    insertelem(first,1,4);
    insertelem(first,1,5);
    listtraverse(first,ptrfunc);
    insertelem(first,1,6);
    insertelem(first,1,7);
    insertelem(first,1,8);
    insertelem(first,1,9);
    listtraverse(first,ptrfunc);
    insertelem(first,1,666);
    insertelem(first,1,777);
    insertelem(first,1,888);
    insertelem(first,1,999);
    listtraverse(first,ptrfunc);
    
    elemtype ei;
    cout<<"取数据之前"<<ei<<endl;
    getelem(first,10,ei);
    cout<<"读取的数据为"<<ei<<endl;

    linknode *q;
    q=locateelem(first,888);
    if(!q)
        cout<<"没有找到对应节点"<<endl;
    else{
        q=priorelem(first,q);
        cout<<"找到节点的前驱为"<<q->data;
        cout<<"找到的节点为"<<q->next->data<<endl;
        if(q->next->next)
            cout<<"找到的节点的后继为"<<nextelem(first,nextelem(first,q))->data;
    }

    cout<<"删除前的值为"<<ei<<endl;
    if(deleteelem(first,15,ei)>0)
        cout<<"删除的值为"<<ei<<endl;
    else
        cout<<"删除失败"<<endl;
    listtraverse(first,ptrfunc);

    cout<<"删除前的值为"<<ei<<endl;
    if(deleteelem(first,10,ei)>0)
        cout<<"删除的值为"<<ei<<endl;
    else
        cout<<"删除失败"<<endl;

    cout<<"删除前的值为"<<ei<<endl;
    if(deleteelem(first,6,ei)>0)
        cout<<"删除的值为"<<ei<<endl;
    else
        cout<<"删除失败"<<endl;
    listtraverse(first,ptrfunc);

    ptrfunc=add2;
    cout<<"每个元素准备加2"<<endl;
    listtraverse(first,ptrfunc);
    cout<<"完成+2后,新链表:"<<endl;
    listtraverse(first,printlinknode);
}