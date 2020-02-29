#include <cstdio>
#include <cstring>
using namespace std;

int n;
int a[110],sum[110];
int f[110][110];

int main(){
    memset(f,0x7f,sizeof(f));
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
        f[i][i+1]=a[i]+a[i+1];
        f[i][i]=0;
    }

    for(int i=2;i<n;i++){
        for(int j=1;j<=n-i;j++){
            for(int k=j;k<j+i;k++){
                if(f[j][k]+f[k+1][j+i]+sum[j+i]-sum[j-1]<f[j][j+i]) 
                    f[j][j+i]=f[j][k]+f[k+1][j+i]+sum[j+i]-sum[j-1];
            }
        }
    }
    printf("%d",f[1][n]);
}
