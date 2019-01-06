#include <cstdio>
#include <iostream>
using namespace std;

int n;
int a[1100][1100];
int f[1100][1100];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            scanf("%d",&a[i][j]);
    
            f[i][j]=a[i][j];
        }
    }
    if(n==1) {
        printf("%d",a[1][1]);
        return 0;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++){
            if(i-1>0){
                if(j-1>0&&j<i) f[i][j]=max(f[i-1][j-1]+a[i][j],f[i-1][j]+a[i][j]);
                else if(j-1>0&&j>=i) f[i][j]=f[i-1][j-1]+a[i][j];
                else if(j-1<=0&&j<i) f[i][j]=f[i-1][j]+a[i][j];
            }
        }

    int Max=-1;
    for(int i=1;i<=n;i++) if(f[n][i]>Max) Max=f[n][i];
    printf("%d",Max);
}
