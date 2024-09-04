#include<bits/stdc++.h>
using namespace std;
int n,A,B,C,D,tou,wei,ans=0;
const int dx[4]={-1,-1,1,1};
const int dy[4]={-1,1,-1,1};
bool vis[510][510][2];
pair<int,int>que[1000010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int main()
{
    n=read();
    A=read();B=read();C=read();D=read();
    vis[1][1][0]=vis[1][1][1]=1;
    que[tou=wei=1]={1,1};
    que[++wei]={-1,-1};
    while(tou<=wei){
        int x=que[tou].first,y=que[tou].second,t=0;
        tou++;
        // cout<<x<<' '<<y<<'\n';
        if(x<0)x=-x,y=-y,t=1;
        if(t==0){
            for(int i=0;i<4;i++){
                int xx,yy;
                xx=(x+A*dx[i]);yy=(y+B*dy[i]);
                // cout<<x<<' '<<y<<' '<<xx<<' '<<yy<<' '<<t<<'\n';
                if(1<=xx&&xx<=n&&1<=yy&&yy<=n){
                    if(!vis[xx][yy][t^1]){
                        que[++wei]={-xx,-yy};
                        vis[xx][yy][t^1]=1;
                    }
                }
                xx=(x+B*dx[i]);yy=(y+A*dy[i]);
                if(1<=xx&&xx<=n&&1<=yy&&yy<=n){
                    if(!vis[xx][yy][t^1]){
                        que[++wei]={-xx,-yy};
                        vis[xx][yy][t^1]=1;
                    }
                }
            }
        }else{
            for(int i=0;i<4;i++){
                int xx,yy;
                xx=(x+C*dx[i]);yy=(y+D*dy[i]);
                if(1<=xx&&xx<=n&&1<=yy&&yy<=n){
                    if(!vis[xx][yy][t^1]){
                        que[++wei]={xx,yy};
                        vis[xx][yy][t^1]=1;
                    }
                }
                xx=(x+D*dx[i]);yy=(y+C*dy[i]);
                if(1<=xx&&xx<=n&&1<=yy&&yy<=n){
                    if(!vis[xx][yy][t^1]){
                        que[++wei]={xx,yy};
                        vis[xx][yy][t^1]=1;
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(vis[i][j][0]||vis[i][j][1])
        ans++;
    cout<<ans<<'\n';
}