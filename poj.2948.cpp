#include <cstdio>
#include <iostream>
using namespace std;

int n,m,temp;
int bl[510][510],yr[510][510];
int d[510][510];

int main(){
    while(1){
        scanf("%d%d",&n,&m);
        if(n==0&&m==0) break;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%d",&temp);
                yr[i][j]=yr[i][j-1]+temp;
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                scanf("%d",&temp);
                bl[i][j]=bl[i-1][j]+temp;
            }
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                d[i][j]=max(d[i-1][j]+yr[i][j],d[i][j-1]+bl[i][j]);
            }
        }
        printf("%d\n",d[n][m]);
    }
}
