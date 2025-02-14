#include <iostream>
using namespace std;
int hanoi(int n){
    if(!n)
        return 0;
    return 2*hanoi(n-1)+1;
}

int main(){
    int n;
    cin>>n;
    cout<<hanoi(n)<<endl;
    //system("pause");
}