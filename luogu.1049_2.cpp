#include <cstdio>
using namespace std;

int v,n,a[110],f[110];
bool x[110];
int max,cnt;

void dfs(int deep){
    if(v-deep==0) {max=0;return ;}
    if(f[deep]==0) f[deep]=max;
    else if(max>f[deep]) return ;
    if(v-deep<max) {
        max=v-deep;
        f[deep]=max;
    }
    for(int i=1;i<=n;i++){
        if(!x[i]&&deep+a[i]<=v){
            x[i]=true;
            dfs(deep+a[i]);
            x[i]=false;
        }
    }
}

int main(){
    scanf("%d%d",&v,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    max=0x7fffffff;
    dfs(0);
    printf("%d",max);
}
