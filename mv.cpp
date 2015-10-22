#include <iostream>  
#include <stdio.h>
using namespace std;  
#define N 2000005  
  
struct set  
{  
    int parent;  //记录父节点  
    int rank;    //记录集合的节点数  
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
    while(x!=elem[x].parent)    //寻找根节点  
        x=elem[x].parent;  
    root=x;  
    x=temp;  
    while (x!=elem[x].parent)   //压缩路径，全部赋值为根节点的值  
    {  
        temp=elem[x].parent;  
        elem[x].parent=root;  
        x=temp;  
    }  
    return root;  
}  
  
void Union(int a,int b)   //合并两个集合  
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
    int n;  //有关系的对数  
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
                Union(a,b);//a和b不是一个集合的，合并这两个集合  
        }  
        if(MAX!=-1)  
            printf("%d/n",MAX);   //输出最大集合的节点数  
        else  
            printf("1/n");   //此时n=0，证明都是没关系的人  
    }  
    return 0;  
}  
