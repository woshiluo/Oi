#include <cstdio>
#include <iostream>
using namespace std;

int n,x,y,v;
int a[20][20];
int f[20][20][20][20];

int main(){
    scanf("%d",&n);
    while(scanf("%d%d%d",&x,&y,&v)!=EOF){
        a[x][y]=v;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                for(int l=1;l<=n;l++){
                    f[i][j][k][l]=max(max(f[i-1][j][k-1][l],f[i][j-1][k-1][l]),max(f[i-1][j][k][l-1],f[i][j-1][k][l-1]))+a[i][j]+a[k][l];
                    if(i==k&&j==l) f[i][j][k][l]-=a[i][j];
                }
            }
        }
    }
    printf("%d",f[n][n][n][n]);
}
