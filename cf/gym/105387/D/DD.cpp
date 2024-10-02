#include <bits/stdc++.h>
using namespace std;
char S[100010],T[200010];
int p[200010],n=0,ans=0;
int check(int i,int j)
{
    if(T[i]=='A'&&T[j]=='T')return 1;
    if(T[i]=='T'&&T[j]=='A')return 1;
    if(T[i]=='C'&&T[j]=='G')return 1;
    if(T[i]=='G'&&T[j]=='C')return 1;
    if(T[i]=='#'&&T[j]=='#')return 1;
    return 0;
}
int main()
{
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
    scanf("%s",S+1);
    int len=strlen(S+1);
    T[0]='$';
    for (int i=1;i<=len;i++) {
        T[++n]='#';
        T[++n]=S[i];
    }
    T[++n]='#';
    int id=0,mx=0,l,r;
    for (int i=1;i<=n;i++) {
        if (i<=mx) p[i]=min(mx-i,p[2*id-i]);else p[i]=1;
        while (check(i-p[i],i+p[i])) p[i]++;
        if (i+p[i]-1>mx) id=i,mx=i+p[i]-1;
        if (T[i]=='#'&&p[i]-1>ans) {
            ans=p[i]-1;
            l=i-p[i]+1;r=i+p[i]-1;
        }
        cout<<i<<' '<<p[i]<<'\n';
    }
    cout<<ans<<'\n';
    if (ans)
      for (int i=l;i<=r;i++)
        if (T[i]!='#') cout<<T[i];
}
