#include <cstdio>
using namespace std;

long long dx[8]={+2,+2,-2,-2,+1,+1,-1,-1};
long long dy[8]={+1,-1,+1,-1,+2,-2,+2,-2};
long long f[20][20],n,m,x,y;

int main(){ 
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=x;i<=n;i++){
        for(int j=y;j<=m;j++){
            for(int k=0;k<8;k++){
                long long tx,ty;
                tx+=dx[k]+i;
                ty+=dy[k]+j;

            }
        }
    } 
}
