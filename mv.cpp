#include <iostream>  
#include <stdio.h>
using namespace std;  
#define N 2000005  
  
struct set  
{  
    int parent;  //��¼���ڵ�  
    int rank;    //��¼���ϵĽڵ���  
}elem[N];  
  
int MAX;  
  
void init()  
{  
    int i;  
    for(i=0;i<=N;i++)  
    {  
        elem[i].parent=i;  
        elem[i].rank=1;  
    }  
}  
  
int Find(int x)  
{  
    int root,temp;  
    temp=x;  
    while(x!=elem[x].parent)    //Ѱ�Ҹ��ڵ�  
        x=elem[x].parent;  
    root=x;  
    x=temp;  
    while (x!=elem[x].parent)   //ѹ��·����ȫ����ֵΪ���ڵ��ֵ  
    {  
        temp=elem[x].parent;  
        elem[x].parent=root;  
        x=temp;  
    }  
    return root;  
}  
  
void Union(int a,int b)   //�ϲ���������  
{  
    int x,y;  
    x=Find(a);  
    y=Find(b);  
    if(elem[x].rank>=elem[y].rank)  
    {  
        elem[y].parent=elem[x].parent;  
        elem[x].rank+=elem[y].rank;  
        if(MAX<elem[x].rank)  
            MAX=elem[x].rank;  
    }  
    else  
    {  
        elem[x].parent=elem[y].parent;  
        elem[y].rank+=elem[x].rank;  
        if(MAX<elem[y].rank)  
            MAX=elem[y].rank;  
    }  
}  
  
int main()  
{  
    int n;  //�й�ϵ�Ķ���  
    int a,b,x,y;  
    while (scanf("%d",&n)!=EOF)  
    {  
        init();  
        MAX=-1;  
        while (n--)  
        {  
            scanf("%d%d",&a,&b);  
            x=Find(a);  
            y=Find(b);  
            if(x!=y)      
                Union(a,b);//a��b����һ�����ϵģ��ϲ�����������  
        }  
        if(MAX!=-1)  
            printf("%d/n",MAX);   //�����󼯺ϵĽڵ���  
        else  
            printf("1/n");   //��ʱn=0��֤������û��ϵ����  
    }  
    return 0;  
}  
