#include <cstdio>
#include <cstring>
using namespace std;

struct que{
    int tu_col,money,x,y;
}q[110000];

int n,m,x,y,c;
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
int best[110][110],col[110][110];

void dfs(int x,int y,int tu_col,int money){
    for(int i=0;i<4;i++){
        int tx=x+dx[i];
        int ty=y+dy[i];

        if(tx<=0||ty<=0||tx>m||ty>m) continue;

        if(col[tx][ty]==0&&tu_col==0){
            if(money+2<best[tx][ty]){
                best[tx][ty]=money+2;
                dfs(tx,ty,col[x][y],money+2);
            }
        }
        else if(col[tx][ty]!=0&&col[tx][ty]!=(col[x][y]!=0?col[x][y]:tu_col)){
            if(money+1<best[tx][ty]){ 
                best[tx][ty]=money+1;
                dfs(tx,ty,0,money+1);
            }               
        }
        else if(col[tx][ty]!=0){
            if(money<best[tx][ty]){  
                best[tx][ty]=money;
                dfs(tx,ty,0,money);
            }   
        }
    }   
}

int main(){
    memset(best,0x3f,sizeof(best));
    scanf("%d%d",&m,&n);

    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&x,&y,&c);
        col[x][y]=c+1;
    }

    best[1][1]=0;
    dfs(1,1,0,0);
    if(best[m][m]<0x3f3f3f3f) printf("%d",best[m][m]);
    else printf("-1");
}
