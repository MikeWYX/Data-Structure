#include <iostream>
using namespace std;

int power(int n,int k, int q){
    int m = n % q;
    int temp = 1,index = 0;
    int a[k];
    a[0] = m;
    while(temp<=k/2){
        m = m * m;
		m = m % q; 
		//cout<<m<<endl;
        a[++index] = m; //a[i] = m^(2^i)
        temp = temp * 2;
		//cout<<temp<<endl;
    }
    k = k - temp;
    while(k > 0){
        temp = temp / 2;
        index--;
        if(k >= temp){
            k = k - temp;
            m *= a[index];
			m = m % q;
			//cout<<m<<endl;
        }
    }
	return m;
}

int main(){
    cout<<power(5,5,53)<<endl;
}
