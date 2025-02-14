#include <cstdint>
#include <iostream>
#include <fstream>

#define MAXLEN 100
#ifndef LENGTH
#define LENGTH 3
#endif

int16_t lab1(int16_t a, int16_t b) {
    // initialize
    int16_t temp,mask=1,count=0;
    // calculation
    if(!b){
        return 0;
    }
    while(b>0){
        temp=a & mask;
        if(temp){
            count++;
        }
        mask+=mask;
        b--;
    }
    // return value
    return count;
}
int16_t lab2(int16_t p, int16_t q, int16_t n) {
    // initialize
    int16_t f,f1,f2,temp1,temp2;
    f1=1;
    f2=1;
    // calculation
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
    // return value
    return f;
}
int16_t lab3(int16_t n, char s[]) {
    // initialize
    int i=0,max=0,count=1,temp;
    // calculation
    if(n==1){
        return 1;
    }
    temp=s[0];
    n--;
    do{
        i++;
        if(temp==s[i]){
            count++;
        }
        else{
            if(max<count){
                max=count;
            }
            count=1;
            temp=s[i];
        }
        n--;
    }
    while(n>0);
    if(max<count){
        max=count;
    }
    // return value
    return max;
}
void lab4(int16_t score[], int16_t *a, int16_t *b) {
    // initialize
    int16_t *temp,size=0,temp2,min,curr,i,*minaddress;
    *a=0;
    *b=0;
    // calculation
    while(size<16){
        min=100;
        temp2=size;
        temp=&score[size];  
        while(temp2<16){
            curr=*temp;
            if(min>=curr){
                min=curr;
                minaddress=temp;
            }
            temp++;
            temp2++;
        }
        *minaddress=score[size];
        score[size]=min;
        size++;
    }
    i=0;
    temp=&score[8];
    while(i<4){
        if(temp[i]>=75){
            (*b)++;
        }
        i++;
    }
    temp=&score[12];
    i=0;
    while(i<4){
        if(temp[i]>=85){
            (*a)++;
        }
        else if(temp[i]>=75)
            (*b)++;
        i++;
    }  
    // return value
}
int main() {
    std::fstream file;
    file.open("D:\\数据结构\\lab6\\test.txt", std::ios::in);
    if(!file){
        std::cout << "fail" << std::endl;
    }
    // lab1
    int16_t a = 0, b = 0;
    for (int i = 0; i < LENGTH; ++i) {
        file >> a >> b;
        std::cout << lab1(a, b) << std::endl;
    }
    // lab2
    int16_t p = 0, q = 0, n = 0;
    for (int i = 0; i < LENGTH; ++i) {
        file >> p >> q >> n;
        std::cout << lab2(p, q, n) << std::endl;
    }
    // lab3
    char s[MAXLEN];
    for (int i = 0; i < LENGTH; ++i) {
        file >> n >> s;
        std::cout << lab3(n, s) << std::endl;
    }
    // lab4
    int16_t score[16];
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < 16; ++j) {
            file >> score[j];
        }
        lab4(score, &a, &b);
        for (int j = 0; j < 16; ++j) {
            std::cout << score[j] << " ";
        }
        std::cout << std::endl << a << " " << b << std::endl;
    }
    file.close();
    system("pause");
    return 0;
}
