#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int n,cnt;
int f[1000][1000],a[11000],sum[1100];

int main(){

    memset(f,0,sizeof(f));
    
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }



    for(int i = 2 ; i <= n ; i++){
        for(int j = 1 ; j <= 2*n-i ;j++){
            for(int k = j+1; k < j+i ; k++){
                f[j][j+2] = max(f[j][k]+f[k+2][j+2]+a[j]*a[k]*a[j+2],f[j][j+2]);
            }
        }
    }  
    int max=0;
    for(int i=1;i<=n;i++) if(f[i][i+n]>max) max=f[i][i+n];
    printf("%d",max);
}
