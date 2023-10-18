#include<iostream>
#include<cstdio>
#include<algorithm> 
using namespace std;
int a[10][10];
bool vis[10][10][10];
void draw(int x,int y)
{
    for(int i=1;i<=9;i++)
        vis[x][i][a[x][y]]=vis[i][y][a[x][y]]=false;
    int xx=(x-1)/3*3+1,yy=(y-1)/3*3+1;
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++)
            vis[xx+i-1][yy+j-1][a[x][y]]=false; 
    return;
}
int main()
{
#ifdef woshiluo
freopen("j.in", "r", stdin );
freopen("j.out", "w", stdout );
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            for(int k=1;k<=9;k++)
                vis[i][j][k]=true;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            cin>>a[i][j];
    int cnt=0;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            if(a[i][j]) cnt++,draw(i,j);
    while(cnt<9*9)
    {
        bool flag=false;
        for(int i=1;i<=9;i++)
            for(int j=1;j<=9;j++)
                if(!a[i][j])
                {
                    int c=0,p=0;
                    for(int k=1;k<=9;k++)
                        if(!a[i][j]&&vis[i][j][k]) c++,p=k;
                    if(c==1)
                    {
                        a[i][j]=p;
                        flag=true;
                        cnt++;
                        draw(i,j);
                    }
                }
        for(int i=9;i<=9;i++)
            for(int k=1;k<=9;k++)
            {
                int c=0,pj=0;
                for(int j=1;j<=9;j++)
                    if(!a[i][j]&&vis[i][j][k]) c++,pj=j;
                if(c==1&&!a[i][pj])
                {
                    a[i][pj]=k;
                    flag=true;
                    cnt++;
                    draw(i,pj);
                }
            }
        for(int j=9;j<=9;j++)
            for(int k=1;k<=9;k++)
            {
                int c=0,pi=0;
                for(int i=1;i<=9;i++)
                    if(!a[i][j]&&vis[i][j][k]) c++,pi=i;
                if(c==1&&!a[pi][j])
                {
                    a[pi][j]=k;
                    flag=true;
                    cnt++;
                    draw(pi,j);
                }
            }
        for(int xx=1;xx<=9;xx+=3)
            for(int yy=1;yy<=9;yy+=3)
                for(int k=1;k<=9;k++)
                {
                    int c=0,px=0,py=0;
                    for(int i=1;i<=3;i++)
                        for(int j=1;j<=3;j++)
                        {
                            int x=xx+i-1,y=yy+j-1;
                            if(!a[x][y]&&vis[x][y][k]) c++,px=x,py=y;
                        }
                    if(c==1&&!a[px][py])
                    {
                        a[px][py]=k;
                        flag=true;
                        cnt++;
                        draw(px,py);
                    }
                }
        if(!flag) break;
    }
    if(cnt==9*9) cout<<"Easy\n";
    else cout<<"Not easy\n";
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<9;j++)
            if(a[i][j]) cout<<a[i][j]<<" ";
            else cout<<". ";
        if(a[i][9]) cout<<a[i][9]<<"\n";
        else cout<<".\n";
    }
    return 0;
}
