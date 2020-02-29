#include <cstdio>
using namespace std;

int t,m;
int medic[1100],time[1100];
int f[1100],g[1100];

int max(int a,int b){
    if(a>b) return a;
    else return b;
}

int main(){
    scanf("%d%d",&t,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&time[i],&medic[i]);

    for(int i=1;i<=m;i++){
        for(int j=t;j>=time[i];j--){
            f[j]=max(f[j-time[i]]+medic[i],f[j]);   
        }
    }

    printf("%d",f[t]);
}
