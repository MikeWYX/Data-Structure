#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

#define initstack(stack)    stack ## _stackbase_ptr=(stack *)malloc(sizeof(stack)*STACK_INIT_SIZE);\
                            if(stack ## _stackbase_ptr) {\
                            stack ## _stacktop_ptr = stack ## _stackbase_ptr;\
                            stack ## _stacksize=STACK_INIT_SIZE;\
                            }else exit(0)
//给栈分配空间，将指针初始化
#define stackempty(stack)   (stack ## _stacktop_ptr == stack ## _stackbase_ptr)?1:0
//判断栈是否为空，空栈值为1，否则值为0，可视作函数返回值
#define gettop(stack,e)   (stack ## _stacktop_ptr == stack ## _stackbase_ptr)?0:(e=*(stack ## _stacktop_ptr-1),1)
//判断能否取栈顶，能值为1并将栈顶赋值给e，否则值为0
#define clearstack(stack)    stack ## _stacktop_ptr = stack ## _stackbase_ptr
//清空栈即将指针调回初始状态
#define destroy(stack)  delete stack ## _stackbase_ptr
//销毁栈可直接将分配空间销毁
#define stacklength(stack)  (stack ## _stacktop_ptr - stack ## _stackbase_ptr)
//栈中元素个数即指针指向地址之差
#define pop(stack,e)    (stack ## _stacktop_ptr == stack ## _stackbase_ptr)?0:(e=*(--stack ## _stacktop_ptr),1)
//将栈顶元素出栈，栈空值为0，否则值为1且将出栈元素赋值给e并将栈顶指针地址-1
#define push(stack,e)   if((stack ## _stacktop_ptr - stack ## _stackbase_ptr) >= stack ## _stacksize){\
                        stack ## _stacksize+=STACKINCREMENT;\
                        stack ## _stackbase_ptr=(stack *)realloc(stack ## _stackbase_ptr,stack ## _stacksize);\
                        stack ## _stacktop_ptr = stack ## _stackbase_ptr + stack ## _stacksize-STACKINCREMENT;}\
                        if(! stack ## _stackbase_ptr)\
                            exit(0);\
                        *(stack ## _stacktop_ptr++)=e
//首先判断栈是否已满，已满则增加最大容量并重新分配更大容量，最后判断是否分配成功，成功则将e入栈并将栈顶指针地址加1

unsigned int_stacksize;
int *int_stacktop_ptr;
int *int_stackbase_ptr;

unsigned char_stacksize;
char *char_stacktop_ptr;
char *char_stackbase_ptr;

typedef struct node{
    int data[10];
    float x,y;
}tnode;
unsigned tnode_stacksize;
tnode *tnode_stacktop_ptr;
tnode *tnode_stackbase_ptr;

int main(){
    initstack(int);
    int x;
    if(pop(int,x))
        cout<<"出栈成功"<<x<<endl;
    else
        cout<<"栈空,不能出栈"<<endl;
    cout<<"栈中有"<<stacklength(int)<<"个元素"<<endl;
    if(stackempty(int))
        cout<<"栈空,无法取栈顶"<<endl;
    else 
        if(gettop(int,x))
            cout<<"栈顶元素是"<<x<<endl;
    push(int,3);
    cout<<"栈中有"<<stacklength(int)<<"个元素"<<endl;
    push(int,4);
    push(int,5);
    cout<<"栈中有"<<stacklength(int)<<"个元素"<<endl;
    if(pop(int,x))
        cout<<"出栈成功"<<x<<endl;
    else
        cout<<"栈空，无法出栈"<<endl;
    cout<<"栈中有"<<stacklength(int)<<"个元素"<<endl;
    if(stackempty(int))
        cout<<"栈空，无法取栈顶"<<endl;
    else 
        if(gettop(int,x))
            cout<<"栈顶元素是"<<x<<endl;
    clearstack(int);

    initstack(char);
    char y;
    if(pop(char,y))
        cout<<"出栈成功"<<y<<endl;
    else
        cout<<"栈空,不能出栈"<<endl;
    cout<<"栈中有"<<stacklength(char)<<"个元素"<<endl;
    if(stackempty(char))
        cout<<"栈空,无法取栈顶"<<endl;
    else 
        if(gettop(char,y))
            cout<<"栈顶元素是"<<y<<endl;
    push(char,'a');
    cout<<"栈中有"<<stacklength(char)<<"个元素"<<endl;
    push(char,'b');
    push(char,'c');
    cout<<"栈中有"<<stacklength(char)<<"个元素"<<endl;
    if(pop(char,y))
        cout<<"出栈成功"<<y<<endl;
    else
        cout<<"栈空，无法出栈"<<endl;
    cout<<"栈中有"<<stacklength(char)<<"个元素"<<endl;
    if(stackempty(char))
        cout<<"栈空，无法取栈顶"<<endl;
    else 
        if(gettop(char,y))
            cout<<"栈顶元素是"<<y<<endl;
    clearstack(char);

    initstack(tnode);
    tnode z;
    int i;
    if(pop(tnode,z)){
        cout<<"出栈成功"<<z.x<<endl<<z.y<<endl;
        for(i=0;i<10;i++)
            cout<<z.data[i]<<" ";
    }
    else
        cout<<"栈空,不能出栈"<<endl;
    cout<<"栈中有"<<stacklength(tnode)<<"个元素"<<endl;
    if(stackempty(tnode))
        cout<<"栈空,无法取栈顶"<<endl;
    else {
        if(gettop(tnode,z)){
            cout<<"出栈成功"<<z.x<<endl<<z.y<<endl;
            for(i=0;i<10;i++)
                cout<<z.data[i]<<" ";
        }
    }
    for(i=0;i<10;i++)
        z.data[i]=1;
    z.x=1.1;
    z.y=2.2;
    push(tnode,z);
    cout<<"栈中有"<<stacklength(tnode)<<"个元素"<<endl;
    for(i=0;i<10;i++)
        z.data[i]=2;
    z.x=3.3;
    z.y=4.4;
    push(tnode,z);
    for(i=0;i<10;i++)
        z.data[i]=3;
    z.x=5.5;
    z.y=6.6;
    push(tnode,z);
    cout<<"栈中有"<<stacklength(tnode)<<"个元素"<<endl;
    if(pop(tnode,z)){
         cout<<"出栈成功"<<z.x<<endl<<z.y<<endl;
            for(i=0;i<10;i++)
                cout<<z.data[i]<<" ";
    }
    else
        cout<<"栈空，无法出栈"<<endl;
    cout<<"栈中有"<<stacklength(tnode)<<"个元素"<<endl;
    if(stackempty(tnode))
        cout<<"栈空，无法取栈顶"<<endl;
    else {
        if(gettop(tnode,z)){
            cout<<"栈顶元素是"<<z.x<<endl<<z.y<<endl;
            for(i=0;i<10;i++)
                cout<<z.data[i]<<" ";
        }
    }
    clearstack(tnode);
}