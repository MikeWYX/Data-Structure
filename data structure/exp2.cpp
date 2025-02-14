#include <iostream>
#include <math.h>
using namespace std;

typedef struct num{      //存储读入的高精度数
    int num[500];      //每一位大小
    int power[500];     //每一位次方
    int sign;       //正负性，1为正，-1为负
    int len;        //以字符串形式存储的长度('\0'的位置)
}coeff;

void read(coeff &x){        //写入高精度数
    char temp;      
    int i=-1,j,count=0;      //统计整数位次数
    x.sign=1;       //默认正数
    while((temp=getchar())!='\n'){      //整数部分写入
        if(temp=='-'){
            x.sign=-1;
            continue;
        }
        if(temp=='.'){
            x.num[j++]=temp;
            while((temp=getchar())!='\n'){      //小数部分写入
                x.power[j]=i--;
                x.num[j++]=temp;        //将读入数字存入，count仍可以继续使用
            }
            x.num[j]='\0';
            break;
        }
        x.num[count++]=temp;        //将读入数字存入，统计整数位数加1
        j=count;
    }
    x.num[j]='\0';      //若输入为整数小数部分的/0不会被执行
    x.len=j;
    for(i=0;count>0;count--,i++){
        x.power[i]=count-1;
    }
}

int check(coeff de){        //检测要转换的数字在转换过程中是否已除尽至0
    int i;
    for(i=0;de.num[i]!='.'&&de.num[i]!='\0';i++){
        if(de.num[i]!='0')
            return 0;       //有不为0的位数说明转换未结束
    }
    return 1;
}

int transform_int_bi(coeff de,coeff &bi){      //将十进制整数部分转化为二进制,并返回转换成的二进制整数位数
    int i=0,count=0,temp;
    while(1){
        if(de.num[i+1]=='.'||de.num[i+1]=='\0'){    //一轮除以2结束          
            bi.num[count++]=(de.num[i]-48)%2+48;       //将除以2最后余数存入，并统计二进制位数
            de.num[i]=(de.num[i]-48)/2+48;      //实现除以2取余的效果
            i=0;        //开始下一轮除以2
        }
        else{       //后面一位需加上该位余数
            de.num[i+1]+=10*(de.num[i]%2);
            de.num[i]=(de.num[i]-48)/2+48;      //实现除以2取余的效果
            i++;    //处理下一位
        }
        if(check(de)){      //全为0转换结束
            bi.num[count]='\0';
            break;
        }
    }
    for(i=0;i<count/2;i++){       //乘2倒序得到整数部分，这里进行颠倒
        temp=bi.num[i];
        bi.num[i]=bi.num[count-i-1];
        bi.num[count-i-1]=temp;
    }
    return count;   
}

void transform_float_bi(coeff de,coeff &bi,int i,int count){        //i表示de中小数点位置，count表示bi中整数位位数
    int n,j,k;
    bi.num[count]='.';      //补上小数点
    cout<<"请输入精度"<<endl;
    cin>>n;
    for(j=1;j<=n;j++){      //精度为n则需要循环n次
        de.num[i+1]=(de.num[i+1]-48)*2+48;      //先乘以2
        bi.num[count+j]=(de.num[i+1]>57?(de.num[i+1]-=10,49):48);     //小数部分乘2是否超过1仅取决于小数点后第一位，若超过即-10并将二进制结果当前位赋予1
        for(k=i+2;de.num[k]!='\0';k++){
            de.num[k]=(de.num[k]-48)*2+48;
            de.num[k-1]=(de.num[k]>57?(de.num[k]-=10,de.num[k-1]+1):de.num[k-1]);       //判断乘二后该为是否溢出，溢出则将溢出部分减去加到高一位上
        }
    }
    bi.num[count+n]='\0';       //最后加上结束符
    bi.len=count+n;
}

void transform_bi(coeff de,coeff &bi){      //将十进制数转换为二进制
    int i;
    for(i=0;de.num[i]!='\0';i++){
        if(de.num[i]=='.'){     //若包含小数点，需进行整数小数部分转换
            transform_float_bi(de,bi,i,transform_int_bi(de,bi));
            return;
        }
    }
    transform_int_bi(de,bi);        //不包含小数点只需整数转换
    bi.sign=(de.sign?1:0);      //正负性
}

void transform_de(coeff bi,coeff &de){     //将二进制转换为十进制
    int i,j,count=0,temp;
    //整数部分处理
    for(i=0;i<=bi.len;i++){
        de.num[i]=48;
    }
    for(i=0;i<=bi.power[0];i++){
        for(j=0;j<=bi.power[0];j++){
           de.num[j]=(de.num[j]-48)*2+48; 
        }
        de.num[0]+=bi.num[i]-48;
        for(j=0;j<=bi.power[0];j++){
            if(de.num[j]>=58){
                de.num[j+1]+=(de.num[j]-48)/10;
                de.num[j]=(de.num[j]-48)%10+48;
                if(count<=j)
                    count=j+1;      //count为整数最低位即小数点前一位
            }
        }
    }
    for(i=0;i<=count/2;i++){       
            temp=de.num[i];
            de.num[i]=de.num[count-i];
            de.num[count-i]=temp;
    }
    if(bi.num[bi.power[0]+1]=='.'){
        de.num[count+1]='.';
        for(i=bi.len-bi.power[0]-2;i>0;i--){        //i初始为小数位数
            de.num[count+1+i]+=(bi.num[bi.power[0]+1+i]-48);
            for(j=bi.len-bi.power[0]-2;j>0;j--){
               de.num[count+1+j]=(de.num[count+1+j]-48)*5+48;
            }
            for(j=bi.len-bi.power[0]-2;j>0;j--){
                if(de.num[count+1+j]>=58){
                    de.num[j+count]+=(de.num[count+1+j]-48)/10;
                    de.num[count+1+j]=(de.num[count+1+j]-48)%10+48;
                }
            }    
        }
    }
    de.len=count+bi.len-bi.power[0];
    de.num[de.len]='\0';
    de.sign=bi.sign;
}

int transform_int_n(coeff de,coeff &N,int n){      //将十进制整数部分转化为n进制,并返回转换成的n进制整数位数
    int i=0,count=0;
    char temp;
    while(1){
        if(de.num[i+1]=='.'||de.num[i+1]=='\0'){    //一轮除以n结束          
            N.num[count++]=(de.num[i]-48)%n+48;       //将除以n最后余数存入，并统计二进制位数
            de.num[i]=(de.num[i]-48)/n+48;      //实现除以n取余的效果
            i=0;        //开始下一轮除以2
        }
        else{       //后面一位需加上该位余数
            de.num[i+1]+=10*((de.num[i]-48)%n);
            de.num[i]=(de.num[i]-48)/n+48;      //实现除以n取余的效果
            i++;    //处理下一位
        }
        if(check(de)){      //全为0转换结束
            N.num[count]='\0';
            break;
        }
    }
    for(i=0;i<count/2;i++){     //乘n倒序得到整数部分，这里进行颠倒
        temp=N.num[i];
        N.num[i]=N.num[count-i-1];
        N.num[count-i-1]=temp;
    }
    N.sign=de.sign;      //正负性
    return count;   
}

void transform_float_n(coeff de,coeff &N,int i,int count,int n){        //i表示de中小数点位置，count表示N中整数位位数,n为进制
    int acc,j,len,add,temp,k;
    N.num[count]='.';      //补上小数点
    cout<<"请输入精度"<<endl;
    cin>>acc;
    for(len=0;de.num[i+len+1]!='\0';len++);     //遍历统计十进制小数部分位数
    for(j=1;j<=acc;j++){      //精度为n则需要循环n次
        add=temp=0;
        k=len;
        while(1){
            temp=((de.num[i+k]-48)*n+add)/10;       //临时存入乘法进位部分
            de.num[i+k]=((de.num[i+k]-48)*n+add)%10+48;       //计算当前位
            if(de.num[i+k-1]=='.'){        //若前一位为小数点则一次乘n结束将大于1部分存入N小数点后第j位中
                N.num[count+j]=temp+48;
                break;
            }
            add=temp;       //add存入进位值
            k--;        //计算前一位
        }
    }
    N.len=count+acc;
}

void transform_n(coeff de,coeff &N){
    int i,n;
    cout<<"请输入要转换的进制："<<endl;
    cin>>n;
    for(i=0;de.num[i]!='\0';i++){
        if(de.num[i]=='.'){     //若包含小数点，需进行整数小数部分转换
            transform_float_n(de,N,i,transform_int_n(de,N,n),n);
            return;
        }
    }
    transform_int_n(de,N,n);        //不包含小数点只需整数转换
}

int judge(coeff x,coeff y){     //比较x,y绝对值大小
    int i,j;
    for(i=0;x.power[i]=='0'||x.power[i]=='.';i++);      //i移动至x最高有效位
    for(j=0;y.power[j]=='0'||y.power[j]=='.';j++);      //j移动至y最高有效位
    if(x.power[i]>y.power[j]){      //比较最高有效位次数
        return 1;       //x>y
    }
    if(x.power[i]<y.power[j]){
        return -1;      //x<y
    }
    for(;x.num[i]!='\0'&&y.num[j]!='\0';i++,j++){
        if((x.num[i]-y.num[j])>0){
            return 1;       //x>y
        }
        if((x.num[i]-y.num[j])<0){
            return -1;      //x<y
        }
    }
    if(x.len>y.len){
        return 1;       //x>y
    }
    if(x.len==y.len){
        return 0;       //x=y
    }
    if(x.len<y.len){
        return -1;      //x<y
    }
}

void add(coeff x1,coeff x2,coeff &y){
    int powermax,lenmax,intlen1,intlen2,add,i,j,k;
    intlen1=x1.power[0];
    intlen2=x2.power[0];
    powermax=(x1.power[0]>x2.power[0]?x1.power[0]+1:x2.power[0]+1);     //加法位数最高为两加数最高位加1
    lenmax=powermax+((x1.len-intlen1)>(x2.len-intlen2)?(x1.len-intlen1):(x2.len-intlen2));
    if(lenmax>299){
        lenmax=299;
    }
    y.len=j=lenmax;
    y.num[j--]='\0';        //最后一位置结束标志，将j调为最小一位
    add=0;
    if(x1.sign==x2.sign){       //同号即视作简单加法
        //先小数部分加法
        if(x1.power[x1.len-1]<x2.power[x2.len-1]){      //x1最小位
            for(i=x1.len-1;x1.power[i]<x2.power[x2.len-1];i--,j--){        //循环结束时i为x1,x2权值相等位
                y.num[j]=x1.num[i];
                y.power[j]=powermax+1-j;
            }
            for(;j>powermax+1;i--,j--,x2.len--){     //循环结束j为小数点位
                y.num[j]=(x1.num[i]-48+x2.num[x2.len-1]-48+add)%10+48;
                y.power[j]=powermax+1-j;
                add=(x1.num[i]-48+x2.num[x2.len-1]-48+add)/10;
            }    
        }
        else{
            for(i=x2.len-1;x2.power[i]<x1.power[x1.len-1];i--,j--){        //循环结束时i为x1,x2权值相等位
                y.num[j]=x2.num[i];
                y.power[j]=powermax+1-j;
            }
            for(;j>powermax+1;i--,j--,x1.len--){     //循环结束j为小数点位
                y.num[j]=(x2.num[i]-48+x1.num[x1.len-1]-48+add)%10+48;
                y.power[j]=powermax+1-j;
                add=(x2.num[i]-48+x1.num[x1.len-1]-48+add)/10;
            }  
        }
        if(j<lenmax){
                    y.num[j--]='.';
                }
        for(;intlen1>=0&&intlen2>=0;intlen1--,intlen2--,j--){
            y.num[j]=(x1.num[intlen1]-48+x2.num[intlen2]-48+add)%10+48;
            y.power[j]=powermax-j;
            add=(x1.num[intlen1]-48+x2.num[intlen2]-48+add)/10;
        }
        for(;intlen1>=0;intlen1--,j--){
            y.num[j]=(x1.num[intlen1]-48+add)%10+48;
            y.power[j]=powermax-j;
            add=(x1.num[intlen1]-48+add)/10;
        }
        for(;intlen2>=0;intlen2--,j--){
            y.num[j]=(x2.num[intlen2]-48+add)%10+48;
            y.power[j]=powermax-j;
            add=(x2.num[intlen2]-48+add)/10;
        }
        y.num[j]=add+48; 
        y.power[j]=powermax-j; 
        y.sign=x1.sign;
    }
    else{       //x1x2不同号
        if(judge(x1,x2)==1){        //x1>x2
            y.sign=x1.sign;
            if(x1.power[x1.len-1]<=x2.power[x2.len-1]){      //x1最小位
                for(i=x1.len-1;x1.power[i]<x2.power[x2.len-1];i--,j--){        //循环结束时i为x1,x2权值相等位
                    y.num[j]=x1.num[i];
                    y.power[j]=powermax+1-j;
                }
                for(;j>powermax+1;i--,j--,x2.len--){     //循环结束j为小数点位
                    y.num[j]=(x1.num[i]-x2.num[x2.len-1]+add+10)%10+48;
                    y.power[j]=powermax+1-j;
                    add=(((x1.num[i]-x2.num[x2.len-1]+add)<0)?-1:0);
                }    
            }
            else{
                for(i=x2.len-1;x2.power[i]<x1.power[x1.len-1];i--,j--){        //循环结束时i为x1,x2权值相等位
                    y.num[j]=(48-x2.num[x2.len-1]+add+10)%10+48;
                    y.power[j]=powermax+1-j;
                    add=(((48-x2.num[x2.len-1]+add)<0)?-1:0);
                }
                for(;j>powermax+1;i--,j--,x1.len--){     //循环结束j为小数点位
                    y.num[j]=(x2.num[i]-x1.num[x1.len-1]+add+10)%10+48;
                    y.power[j]=powermax+1-j;
                    add=(((x1.num[x1.len-1]-x2.num[i]+add)<0)?-1:0);
                }  
            }
            //整数部分
            y.num[j--]='.';
            for(;intlen1>=0&&intlen2>=0;intlen1--,intlen2--,j--){
                y.num[j]=(x1.num[intlen1]-x2.num[intlen2]+add+10)%10+48;
                y.power[j]=powermax-j;
                add=(((x1.num[intlen1]-x2.num[intlen2]+add)<0)?-1:0);
            }
            for(;intlen1>=0;intlen1--,j--){
                y.num[j]=(x1.num[intlen1]-48+add)%10+48;
                y.power[j]=powermax-j;
                add=(((x1.num[intlen1]-48+add)<0)?-1:0);
            }
            y.num[j]=48; 
            y.power[j]=powermax-j; 
        }
        else{
            if(judge(x1,x2)==-1){        //x2>x1
                y.sign=x2.sign;
                if(x2.power[x2.len-1]<=x1.power[x1.len-1]){      //x1最小位
                    for(i=x2.len-1;x2.power[i]<x1.power[x1.len-1];i--,j--){        //循环结束时i为x1,x2权值相等位
                        y.num[j]=x2.num[i];
                        y.power[j]=powermax+1-j;
                    }
                    for(;j>powermax+1;i--,j--,x1.len--){     //循环结束j为小数点位
                        y.num[j]=(x2.num[i]-x1.num[x1.len-1]+add+10)%10+48;
                        y.power[j]=powermax+1-j;
                        add=(((x2.num[i]-x1.num[x1.len-1]+add)<0)?-1:0);
                    }    
                }
                else{
                    for(i=x1.len-1;x1.power[i]<x2.power[x2.len-1];i--,j--){        //循环结束时i为x1,x2权值相等位
                        y.num[j]=(48-x1.num[x1.len-1]+add+10)%10+48;
                        y.power[j]=powermax+1-j;
                        add=(((48-x1.num[x1.len-1]+add)<0)?-1:0);
                    }
                    for(;j>powermax+1;i--,j--,x2.len--){     //循环结束j为小数点位
                        y.num[j]=(x1.num[i]-x2.num[x2.len-1]+add+10)%10+48;
                        y.power[j]=powermax+1-j;
                        add=(((x2.num[x2.len-1]-x1.num[i]+add)<0)?-1:0);
                    }  
                }
                //整数部分
                if(j<lenmax){
                    y.num[j--]='.';
                }
                for(;intlen1>=0&&intlen2>=0;intlen1--,intlen2--,j--){
                    y.num[j]=(x2.num[intlen2]-x1.num[intlen1]+add+10)%10+48;
                    y.power[j]=powermax-j;
                    add=(((x2.num[intlen2]-x1.num[intlen1]+add)<0)?-1:0);
                }
                for(;intlen2>=0;intlen2--,j--){
                    y.num[j]=(x2.num[intlen2]-48+add)%10+48;
                    y.power[j]=powermax-j;
                    add=(((x2.num[intlen2]-48+add)<0)?-1:0);
                }
                y.num[j]=48; 
                y.power[j]=powermax-j; 
                y.sign=x2.sign;
            }
            if(judge(x1,x2)==0){
                y.num[0]=48;
                y.power[0]=0;
                y.num[1]='\0';
            }
        }
    }
}

void multiply(coeff x1,coeff x2,coeff &y){
    int powermax,lenmax,intlen1,intlen2,add,i,j,temp;
    intlen1=x1.power[0];
    intlen2=x2.power[0];
    powermax=intlen1+intlen2+1;     //加法位数最高为两加数最高位加1
    lenmax=x1.len+x2.len;       //最长情况为两整数相
    if(lenmax>299){
        lenmax=299;
    }
    y.len=lenmax;
    y.num[lenmax]='\0';
    for(i=0;i<powermax+1;i++){
        y.power[i]=powermax-i;
        y.num[i]=48;
    }
    if(i<lenmax){
        y.num[i]='.';
    }
    for(i=-1;(powermax+1-i)<lenmax;i--){
        y.num[powermax+1-i]=48;
        y.power[powermax+1-i]=i;
    }
    for(i=0;i<x1.len;i++){
        for(j=0;j<x2.len;j++){
            if(x1.num[i]=='.'||x1.num[i]=='0'||x2.num[j]=='.'||x2.num[j]=='0'){
                continue;
            }
            if((x1.power[i]+x2.power[j])>=0){
                if((x1.power[i]+x2.power[j])>=lenmax){
                    continue;
                }
                y.num[powermax-x1.power[i]-x2.power[j]]+=(x1.num[i]-48)*(x2.num[j]-48);
            }
            if((x1.power[i]+x2.power[j])<0){
                if((powermax-x1.power[i]-x2.power[j]+1)>=lenmax){
                    continue;
                }
                y.num[powermax-x1.power[i]-x2.power[j]+1]+=(x1.num[i]-48)*(x2.num[j]-48);
            }
        }
    }
    add=0;
    for(i=lenmax-1;i>=0;i--){
        if(i==powermax+1){
            continue;
        }
        temp=(y.num[i]-48+add)/10;
        y.num[i]=(y.num[i]-48+add)%10+48;
        add=temp;
    }
    y.sign=x1.sign*x2.sign;
}

void subtract(coeff x1,coeff x2,coeff &y){
    x2.sign=(-1)*x2.sign;
    add(x1,x2,y);
}

void print(coeff x){
    int i;
    if(x.sign==-1){
        cout<<"-";
    }
    for(i=0;x.num[i]=='0'&&(x.num[i+1]!='.'&&x.num[i+1]!='\0');i++);
    for(;i<x.len;i++){
        if(x.num[i]=='.'){
            cout<<'.';
            continue;
        }
        cout<<(x.num[i]-48)<<" ";
    }
}

void duoxiangshi(){
    coeff a[10],temp[100],x,result,temp1;
    int power[10],n,i,j;
    result.num[0]=48;
    result.power[0]=0;
    result.num[1]='\0';
    result.len=2;
    cout<<"请输入多项式项数："<<endl;
    cin>>n;
    getchar();
    for(i=0;i<n;i++){
        cout<<"请输入系数："<<endl;
        read(a[i]);
        cout<<"请输入次方"<<endl;
        cin>>power[i];
        getchar();
    }
    cout<<"请输入x大小:"<<endl;
    read(x);
    for(i=0;i<n;i++){
        if(a[i].num[0]=='0'&&a[i].num[1]=='\0'){
            continue;
        }
        temp[0]=a[i];
        temp1=result;
        if(power[i]==0){
            add(temp[0],temp1,result);
        }
        else{
            for(j=0;power[i]>0;power[i]--,j++){
                multiply(temp[j],x,temp[j+1]);
            }
            add(temp[j],temp1,result);
        }
    }
    cout<<"多项式值的为:"<<endl;
    if(result.sign==-1){
        cout<<"-";
    }
    print(result);
    cout<<endl;
}

int main(){
    coeff x1,x2,y,result;
    duoxiangshi();
    /*read(x2);
    transform_de(x2,y);
    print(y);*/
    system("pause");
}

