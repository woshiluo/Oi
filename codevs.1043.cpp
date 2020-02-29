#include <iostream>
#include <cstdio>
using namespace std;

int n,x,y,c;
int a[20][20],f[20][20][20][20];

int main(){
    scanf("%d",&n);
    while(1){
        scanf("%d%d%d",&x,&y,&c);
        if(x==0&&y==0&&c==0) break;
        a[x][y]=c;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                for(int q=1;q<=n;q++){
                    f[i][j][k][q]=max(max(f[i-1][j][k-1][q],f[i][j-1][k][q-1]),max(f[i][j-1][k-1][q],f[i-1][j][k][q-1]))+a[k][q]+a[i][j];
                    if(i==k&&j==q) f[i][j][k][q]-=a[i][j];
                }
            }
        }   
    }
    printf("%d",f[n][n][n][n]);
}
