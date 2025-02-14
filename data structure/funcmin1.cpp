#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;
/**算法参数设置**/
//定义0-1串长度，可用于表示解的精度
#define SLEN 200

//定义0-1串整数部分长度
#define INTLEN 4

//定义进化最大代数
#define MAXGEN 100

//变异概率
#define MPROB 1.0/SLEN

//父群体与子群体大小，子代必须是偶数（通过交叉染色体生成后代时候，一次生成两个后代）
#define PSIZE 10
#define CSIZE 20
#define SIZE (PSIZE + CSIZE)

//一个解的定义
typedef struct {
	int x[SLEN];   //x:解的自变量，0-1串
	double y;      //y=f(x),要优化问题的目标函数值
} solution;

//定义一个解集/解数组：称之为群体population
solution pop[SIZE];     				//解集，父代和子代都存储在这里
solution *parent = pop;             	//当前代，也就是父代
solution *children = pop + PSIZE;   	//子代解集

//函数声明
//将0-1串x解码为实数*xo ,假定整数4bits，SLEN-4bits为小数部分长度

//将整数部分利用递归乘2将每一位算出
int decodeint(int count){
    if(!count)
        return 1;
    return(2*decodeint(count-1));
}

//将小数部分利用递归乘1/2将每一位算出
double decodefloat(int count){
    if(!count)
        return 1;
    return(0.5*decodefloat(count-1));
}

void decode(int *x, double &xo){
    int i;
    xo=0;
//整数部分换成10进制
    for(i=0;i<INTLEN;i++){
        if(!x[i])   //为0无需计算
            continue;
        xo+=decodeint((INTLEN-i-1));
    }
//小数部分换成10进制  
    for(i=INTLEN;i<SLEN;i++){
        if(!x[i])   //为0无需计算
            continue;
        xo+=decodefloat((i-INTLEN+1));
        }
}

//计算y=f(x) ,  0-1串x的长度 SLEN
double func1(int *x){
	double xo;
	decode(x,xo);  //将0-1串x解码成真正的解xo
	return (xo*xo-2*xo+2);	 //计算目标函数值
}

//计算一个群体的所有解的目标函数值y ，给出了函数指针，支持个函数的优化
void evaluate(solution *p, double ptrf(int *)){
        p->y=ptrf(p->x);
}

//算法初始化：分配两个解集所需的空间，随机生成currentPop中的解，并计算其y值
void initialize(){
    //srand((unsigned)time(NULL));
	for(int i=0;i<PSIZE;i++){	//初始化第一代父代 
		for(int j=0;j<SLEN;j++)  //对每个解的0-1串，随机生成
			parent[i].x[j] = rand()%2;
		evaluate(parent+i,func1);
	}
}

//从父代中选择两个解，通过杂交生成两个子代个体
//父代两个解通过PK选择出来（锦标选择）
void crossover(){ //交叉算子
	int  i,k=0,x1,x2,pos;
    //srand((unsigned)time(NULL));
	while (k < CSIZE){   //逐步生成子代，一次两个
        //随机选择两个父代个体
        x1=rand()%PSIZE;
        x2=rand()%PSIZE;
        //随机确定父代个体染色体交换位点
        pos=rand()%SLEN;
        //交换交叉位点前面的两个子串
        for(i=0;i<pos;i++){
            children[k].x[i]=parent[x1].x[i];
            children[k+1].x[i]=parent[x2].x[i];
        }
        for(i=pos;i<SLEN;i++){
            children[k].x[i]=parent[x2].x[i];
            children[k+1].x[i]=parent[x1].x[i];
        }
		k = k+2;
	}
}

//对子代中的个体进行变异：变异概率为mProb
//所谓变异就是x[j]的取值 0-1互换： 0 <--> 1
void mutate(){ //变异算子
	for(int i=0;i<CSIZE;++i)
		for(int j=0;j<SLEN;++j)
			if ((rand()%100000)/100000.0<MPROB)
				children[i].x[j] = 1 - children[i].x[j];
}

//从currentPop和offspring中选择下一代个体，有多种选择算法，但是通常都是先把两个群体中最好的保留下来 ，然后
//方法1：选择最好的PSIZE个为下一代（截断选择）
//方法2：给每个个体一个选择概率，y值小（好）的被选择的概率就高，然后依据此概率分布随机采样PSIZE个
//方法3：锦标选择，随机选择k个，相互pk，留下最好的放入下一代，依次选择PSIZE个 （不删除被选择了的）
void select(int k){ //选择算子 ：采用锦标选择
	double besty;   //锦标赛选出来的子代的y值
	int best,i,j,temp;       //锦标赛选择出来的子代下标
	solution tmp[PSIZE];
	for(i=0;i<PSIZE;i++){ //一个一个子代选择
        //todo: 从pop[2*psize]中用方法1或2或3选择一个适应度值（y值）好的
        temp=rand()%CSIZE;
        best=temp;
        besty=children[temp].y;
        for(j=1;j<k;j++){
            temp=rand()%CSIZE;
            if(besty>children[temp].y){
                best=temp;
                besty=children[temp].y;
            }
        }
		memcpy(&(tmp[i]),&(children[best]),sizeof(solution)); //选择出来的解，复制到临时解集中
	}
	memcpy(parent,tmp,sizeof(solution)*PSIZE);
}

//输出群体的信息
void printPop(solution *p,const char *str){
	printf("%s/解集信息如下: \n",str);
	for (int i=0;i<PSIZE;++i){
		printf("个体 %3d : y=%10.6lf=f(",i,p[i].y);
		for (int j=0;j<SLEN;++j)
			printf("%d",p[i].x[j]);
		printf(")\n");
	}
}

int main(){
	int seed = 991;
	srand(seed); //设置随机数种子，使得算法结果可以重现
	initialize();
	printf("第 %d 代 ",0);
	printPop(parent,"当前群体");

	for(int gen=1;gen<MAXGEN;gen++){
		crossover();
		mutate();
        for(int i=0;i<CSIZE;i++){
           evaluate(children+i,func1); 
        }
		select(2);
		//printf("第 %d 代 ",gen);
		//printPop(current,"当前群体");
	}
	printf("第 %d 代 ", MAXGEN);
	printPop(parent,"最终群体");
    system("pause");
	return 1;
}