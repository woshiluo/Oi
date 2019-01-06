#include <cstdio>
#include <cstring>
using namespace std;

struct node{
    int x,y,deep;
}dl[110000];

int n,m,k,x1,x2,y1,y2;
int a[1100][1100];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
bool x[1100][1100];

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%1d",&a[i][j]);
        }
    }
    scanf("%d",&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        node temp;
        temp.x=x1;
        temp.y=y1;
        temp.deep=0;
        memset(x,false,sizeof(x));
        memset(dl,0,sizeof(dl));
        dl[1]=temp;
        
        int l,r;
        l=r=1;
        bool y=true;
        while(l<=r){
            node fir=dl[l];
            for(int i=0;i<=3;i++){
                int tx=fir.x+dx[i];
                int ty=fir.y+dy[i];
                
                if(a[tx][ty]==1&&tx<=n&&tx>=0&&ty>=0&&ty<=m&& (!x[tx][ty]) ) {
                    node temp;
                    x[tx][ty]=true;
                    temp=dl[l];
                    temp.x=tx;
                    temp.y=ty;
                    temp.deep++;
                    dl[++r]=temp;
                    if(tx==x2&&ty==y2){
                        printf("%d\n",temp.deep); 
                        y=false;
                        break;
                    }
                }
            } 
            l++;
        }
        if(y) printf("Impossible\n");
    }
}
