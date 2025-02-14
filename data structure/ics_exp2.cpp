#include <cstdint>
#include <iostream>
#include <fstream>
int main(){
    int n=100,p=256,q=123,f,f1,f2,temp1,temp2;
    f1=1;
    f2=1;
    if((--n)<=0){
        f=1;
    }
    while(n>0){
        temp1=f1;
        temp2=f2;
        while(temp1>0){
           temp1=temp1-q;
        }
        temp1=temp1+q;
        while(temp2>0){
           temp2=temp2-p;
        }
        temp2=temp2+p;
        f=temp1+temp2;
        f2=f1;
        f1=f;
        n--;
    }
    cout<<f<<endl;
    system("pause");
}