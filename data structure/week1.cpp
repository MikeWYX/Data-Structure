#include <iostream>
using namespace std;
int main()
{
    int a[] = {};
    int max, temp, i, num;                // max记录最后最大值，temp记录能找到的正数和子序列,num表示temp所记子序列元素个数
    max = a[0] + a[1], temp = 0, num = 0; //初始化
    for (i = 1; i < n - 1; i++)
    { //若所给数组最大子列和为负数，则该种情况下为两数相加所得，先算出两数相加情况下的最大和
        if ((a[i] + a[i + 1]) > max)
            max = a[i] + a[i + 1];
    }
    for (i = 1; i < n - 2; i++)
    { //前面漏算了两正一负组成最大值的结果
        if ((a[i] + a[i + 1] + a[i + 2]) > max)
            max = a[i] + a[i + 1] + a[i + 2];
    }
    for (i = 0; i < n; i++)
    {                 //若不为上述情况则应尽量找连起来的正数和，记录每次正数和的结果
        if (num >= 2) // num保证和最大值比较时子序列长度符合要求
            if (temp > max)
                max = temp;
        if ((temp + a[i]) > 0)
        {
            temp = temp + a[i];
            num++;
        }
        else
        {
            temp = num = 0;
        }
    }
    if (num >= 2) //最后一次算上a[n]少比较一次在这里补上
        if (temp > max)
            max = temp;
}