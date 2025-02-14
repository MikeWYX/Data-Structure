#include <iostream>
using namespace std;
#define N 7
int main(){
    int i=0,max=0,count=1,temp,n=N;
    char str[N]="ZZZZzz";
    if(N==1){
        ;
    }
    temp=str[0];
    n--;
    do{
        i++;
        if(temp==str[i]){
            count++;
        }
        else{
            if(max<count){
                max=count;
            }
            count=1;
            temp=str[i];
        }
        n--;
    }
    while(n>0);
    cout<<"result="<<max;
    system("pause");
}
