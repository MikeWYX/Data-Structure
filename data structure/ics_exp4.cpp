#include <iostream>
using namespace std;
int main(){
    int score[16]={95,100,0,50,45,40,80,65,70,75,35,20,25,15,10,90},result[16];
    int numa=0,numb=0,*ptr,*temp,size=0,temp2,min,curr,i,*minaddress;
    while(size<16){
        min=100;
        temp2=size;
        temp=&score[size];  
        while(temp2<16){
            curr=*temp;
            if(min>curr){
                min=curr;
                minaddress=temp;
            }
            temp++;
            temp2++;
        }
        *minaddress=*(score+size);
        score[size]=min;
        size++;
    }
    i=0;
    temp=&score[8];
    while(i<4){
        if(temp[i]>=75){
            numb++;
        }
        i++;
    }
    temp=&score[12];
    i=0;
    while(i<4){
        if(temp[i]>=85){
            numa++;
        }
        else if(temp[i]>=75)
            numb++;
        i++;
    }  
    for(i=0;i<16;i++){
        cout<<score[i]<<endl;
    }
    cout<<"numa ="<<numa<<endl;
    cout<<"numb ="<<numb<<endl;
    system("pause");
}