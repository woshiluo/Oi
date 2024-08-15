#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,m;
LL f[100010][52],S;
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}

constexpr int nxt[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
constexpr int pre[] = {9, 0, 1, 2, 3, 4, 5, 6, 7, 8};
constexpr int mi[] = { 0, 1, 10, 100, 1000, 10000, 100000, 1000000 };

void bfs()
{
    const int mx = mi[ n + 1 ];
    for(int i=49;i>=0;i--){
        for(int x=0;x<mx;x++){
            for(int l=1;l<=n;l++){
                int A=x,B=x;
                for(int r=l;r<=n;r++){
                    const int p = ( x / mi[r] ) % 10;
                    A-=p*mi[r];B-=p*mi[r];
                    A+=nxt[p]*mi[r];B+=pre[p]*mi[r];
                    // cout<<x<<' '<<A<<' '<<B<<'\n';
                    f[x][i]|=f[A][i+1];
                    f[x][i]|=f[B][i+1];
                }
            }
        }
    }
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();m=read();S=(1LL<<m)-1;
        memset(f,0,sizeof(LL)*(mi[n+1]+5)*52);
        for(int i=1;i<=m;i++){
            int num=read();
            f[num][read()]|=1LL<<(i-1);
        }
        bfs();
        int ans=0,cnt=0;
        for(int i=0;i<mi[n+1];i++)
            if(f[i][0]==S){
                cnt++;ans=i;
            }
        if(!cnt)printf("IMPOSSIBLE\n");
        else{
            if(cnt==1){
                // char str[20];
                // sprintf(str,"%%0%dd",n);
                // cout<<str<<' '<<ans<<'\n';
                printf("%0*d\n", n, ans);
            }else printf("MANY\n");
        }
    }
}
