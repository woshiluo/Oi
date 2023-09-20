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

int main(){
    memset(best,0x3f,sizeof(best));
    scanf("%d%d",&m,&n);

    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&x,&y,&c);
        col[x][y]=c+1;
    }

    q[1].x=q[1].y=1;
    q[1].money=q[1].tu_col=0;

    int h,t;
    h=t=1;
    
    best[1][1]=0;

    while(h<=t){
        que now;
        now=q[h];

        for(int i=0;i<4;i++){
            que temp=q[h];
            temp.x+=dx[i];
            temp.y+=dy[i];
            
            if(temp.x<=0||temp.y<=0||temp.x>m||temp.y>m) continue;

            if(col[temp.x][temp.y]==0&&temp.tu_col==0){
                if(temp.money+2<best[temp.x][temp.y]){
                    temp.money+=2;
                    temp.tu_col=col[now.x][now.y];
                    q[++t]=temp;
                    best[temp.x][temp.y]=temp.money;
                }
            }
            else if(col[temp.x][temp.y]!=0&&col[temp.x][temp.y]!=(col[now.x][now.y]!=0?col[now.x][now.y]:temp.tu_col)){
                 if(temp.money+1<best[temp.x][temp.y]){
                    temp.money+=1;
                    temp.tu_col=0;
                    q[++t]=temp;
                    best[temp.x][temp.y]=temp.money;
                }               
            }
            else if(col[temp.x][temp.y]!=0){
                if(temp.money<best[temp.x][temp.y]){
                    temp.tu_col=0;
                    q[++t]=temp;
                    best[temp.x][temp.y]=temp.money;
                }   
            }
        }
        h++;
    }
    if(best[m][m]<0x3f3f3f3f) printf("%d",best[m][m]);
    else printf("-1");
}
