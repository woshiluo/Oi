#include <cstdio>
using namespace std;

struct node{
    int next,data;
}a[110000];

int n,m;

int main(){
    int p,q;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        a[i].data=i; 
        a[i].next=i+1;
    }
    p=n;
    a[n].next=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m-1;j++){
            p=a[p].next;    
        }
        q=a[p].next;
        a[p].next=a[q].next; 
        printf("%d ",q);
    }
}
