#include <cstdio>
#include <cstdlib>

int n;
int a[100];

void dfs(int dep,int sum){
    if(dep>n){
        if(sum%360==0){
            printf("YES"); 
            exit(0);
        } 
        return ;
    }
    dfs(dep+1,sum+a[dep]);
    dfs(dep+1,sum-a[dep]);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    dfs(1,0);
    printf("NO");
}
