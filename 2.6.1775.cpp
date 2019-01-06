#include <cstdio>
using namespace std;

int t,m;
int time[110],pri[110],f[1100];

int main(){
    scanf("%d%d",&t,&m);
    for(int i=1;i<=m;i++) scanf("%d%d",&time[i],&pri[i]);
    for(int i=1;i<=m;i++){
        for(int j=t;j>=time[i];j--){
            if(f[j]<f[ j-time[i] ]+pri[i]){
                f[j]=f[ j-time[i] ]+pri[i];
            }
        }
    }
    printf("%d",f[t]);
}
