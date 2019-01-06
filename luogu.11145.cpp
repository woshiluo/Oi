#include <cstdio>
using namespace std;

struct node{
    int next,data;
}a[110000];

int n,m;

int main(){
    int p,q;
    scanf("%d%d",&n,&m);
    p=m;
    for(int i=1;i<=n-1;i++){
        for(int j=1;j<=m-1;j++){
            p=a[p].next;    
        }
        printf("%d ",a[q].next);
        a[p].next=a[q].next;
    }
}
