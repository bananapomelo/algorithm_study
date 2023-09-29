/*
    希尔排序算法
*/
#include <stdio.h>

/*
    h_sorting:一次增量h排序
    @a:进行增量h排序的原始序列，数组名
    @n:原始序列元素个数
        a[0] a[1] a[2]......a[n-1]
    @h:增量h/间隔h
    返回值：
        无
*/
void h_sorting(int a[], int n, int h)
{
    int temp, j;
    for(int i=h; i<n; i++)
    {
        //如果需要插入的元素比有序区的都大则无需插入,只有比有序区小才插入
        if(a[i]<a[i-h])
        {
            temp = a[i];//获取待插入元素
            // j = i-h;//有序区的最大下标
            // do//找到插入位置
            // {
            //     a[j+h] = a[j];//往右边挪动
            //     j -= h;
            // } while (j>=0 && a[j]>temp);
            for(j=i-h; j>=0&&a[j]>temp; j = j-h)
            {
                a[j+h] = a[j];
            }
            a[j+h] = temp;
        }
    }
}

//对数组a，进行一个shell排序
//希尔早期提出增量序列为1 2 4 8 .... 2^k....
void shell_sort(int a[], int n)
{
    //增量序列
    int h[4] = {8,4,2,1};
    for(int i=0; i<4; i++)
    {
        h_sorting(a, n, h[i]);
    }
}

#define N 10

int main()
{
    int a[N];
    for(int i=0; i<N; i++)
    {
        scanf("%d", &a[i]);
    }

    shell_sort(a, N);

    for(int i=0; i<N; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}