#include <bits/stdc++.h>
using namespace std;
const int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int n,m,K;
int nex[1010][1010][5],a[1010][1010];
int dis[1010][1010][5];
struct Node
{
    int X,Y,st;
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int sx,sy,ex,ey;
    cin>>n>>m>>K>>sx>>sy>>ex>>ey;
    for (int i=1;i<=n;i++)  
      for (int j=1;j<=m;j++)
        cin>>a[i][j];
    for (int j=1;j<=m;j++) {
        for (int i=1;i<=n;i++) 
          if (a[i][j]==1) nex[i][j][0]=i;
            else nex[i][j][0]=nex[i-1][j][0];
        nex[n+1][j][1]=n+1;
        for (int i=n;i>=1;i--) 
          if (a[i][j]==1) nex[i][j][1]=i;
            else nex[i][j][1]=nex[i+1][j][1];
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++)
          if (a[i][j]==1) nex[i][j][2]=j;
            else nex[i][j][2]=nex[i][j-1][2];
        nex[i][m+1][3]=m+1;
        for (int j=m;j>=1;j--) 
          if (a[i][j]==1) nex[i][j][3]=j;
            else nex[i][j][3]=nex[i][j+1][3];
    }
    deque<Node> q;
    q.push_back({sx,sy,4});
    for (int i=1;i<=n;i++)
      for (int j=1;j<=m;j++)
        for (int k=0;k<=4;k++)
          dis[i][j][k]=1e9;
    dis[sx][sy][4]=0;
    int ans=1e9;
    while (q.size()) {
        Node p=q.front();
        q.pop_front();
        int x=p.X,y=p.Y;
        int v=dis[x][y][p.st];
        if (p.st==4) {
            if (x-nex[x][y][0]>K) {
                if (v+1<dis[x-K][y][0]) {
                    dis[x-K][y][0]=v+1;
                    if (ex>=x-K&&ex<=x&&ey==y) ans=min(ans,v+1);
                    q.push_back({x-K,y,0});
                }
            }
            else {
                int xx=nex[x][y][0]+1,yy=y;
                if (v+1<dis[xx][yy][4]) {
                    dis[xx][yy][4]=v+1;
                    if (ex>=xx&&ex<=x&&ey==y) ans=min(ans,v+1);
                    q.push_back({xx,yy,4});
                }
            }
            if (nex[x][y][1]-x>K) {
                if (v+1<dis[x+K][y][1]) {
                    dis[x+K][y][1]=v+1;
                    if (ex>=x&&ex<=x+K&&ey==y) ans=min(ans,v+1);
                    q.push_back({x+K,y,1});
                }
            }
            else {
                int xx=nex[x][y][1]-1,yy=y;
                if (v+1<dis[xx][yy][4]) {
                    dis[xx][yy][4]=v+1;
                    if (ex>=x&&ex<=xx&&ey==y) ans=min(ans,v+1);
                    q.push_back({xx,yy,4});
                }
            }
            if (y-nex[x][y][2]>K) {
                if (v+1<dis[x][y-K][2]) {
                    dis[x][y-K][2]=v+1;
                    if (ey>=y-K&&ey<=y&&ex==x) ans=min(ans,v+1);
                    q.push_back({x,y-K,2});
                }
            } 
            else {
                int xx=x,yy=nex[x][y][2]+1;
                if (v+1<dis[xx][yy][4]) {
                    dis[xx][yy][4]=v+1;
                    if (ey>=yy&&ey<=y&&ex==x) ans=min(ans,v+1);
                    q.push_back({xx,yy,4});
                }
            }
            if (nex[x][y][3]-y>K) {
                if (v+1<dis[x][y+K][3]) {
                    dis[x][y+K][3]=v+1;
                    if (ey>=y&&ey<=y+K&&ex==x) ans=min(ans,v+1);
                    q.push_back({x,y+K,3});
                }
            } 
            else {
                int xx=x,yy=nex[x][y][3]-1;
                if (v+1<dis[xx][yy][4]) {
                    dis[xx][yy][4]=v+1;
                    if (ey>=y&&ey<=yy&&ex==x) ans=min(ans,v+1);
                    q.push_back({xx,yy,4});
                }
            }
        }
        else {
            if (v<dis[x][y][4]) {
                dis[x][y][4]=v;
                q.push_front({x,y,4});
            }
            int xx=x+dx[p.st],yy=y+dy[p.st];
            if (xx>=1&&xx<=n&&yy>=1&&yy<=m&&a[xx][yy]==0&&v<dis[xx][yy][p.st]) {
                dis[xx][yy][p.st]=v;
                q.push_front({xx,yy,p.st});
            }
        }
    }
    ans=min(ans,dis[ex][ey][4]);
    if (ans==1e9) cout<<-1;
      else cout<<ans;
    return 0;
}