#include <cstdio>
#include <iostream>
using namespace std;

int n,m;
int f[11000];

int dfs(int p){
    if(f[p]==p) return p;
    else return f[p]=dfs(f[p]);
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++){
        int z,x,y;
        scanf("%d%d%d",&z,&x,&y);
        if(z==1) f[dfs(x)]=dfs(y);
        else {
            if(dfs(x)==dfs(y)) printf("Y\n");
            else printf("N\n");
        }
    }
}
