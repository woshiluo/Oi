#include <iostream>
#include <cstdio>
using namespace std;

int temp;
int a[1100];
int b[1100];
int dp[50][50][50][50];
int x;

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++){
        scanf("%d",&temp);
        b[temp]++;
    }

    dp[0][0][0][0]=a[1];

    for(int i=0;i<=b[1];i++){
        for(int j=0;j<=b[2];j++){
            for(int k=0;k<=b[3];k++){
                for(int l=0;l<=b[4];l++){
                    x = 1*i+2*j+3*k+4*l+1;
                    if(i!=0)dp[i][j][k][l] = max(dp[i-1][j][k][l] + a[x],dp[i][j][k][l]);
                    if(j!=0)dp[i][j][k][l] = max(dp[i][j-1][k][l] + a[x],dp[i][j][k][l]);
                    if(k!=0)dp[i][j][k][l] = max(dp[i][j][k-1][l] + a[x],dp[i][j][k][l]);
                    if(l!=0)dp[i][j][k][l] = max(dp[i][j][k][l-1] + a[x],dp[i][j][k][l]);
                }
            }
        }
    }
    printf("%d",dp[ b[1] ][ b[2] ][ b[3] ][ b[4] ]);
}
