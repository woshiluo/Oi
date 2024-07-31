#include <bits/stdc++.h>
using namespace std;
int T;
string S;
int nexc[1000010][27],nexn[1000010][11],Nexc[27],Nexn[11],cnt1[1000010],cnt2[1000010],cnt[1000010];
bool vis[1000010][35];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T;
    while (T--) {
        int n,m;
        cin>>n>>m;
        cin>>S;
        for (int i=0;i<26;i++) 
          nexc[m-1][i]=nexc[m][i]=m;
        for (int i=0;i<10;i++)
          nexn[m-1][i]=nexn[m][i]=m;
        for (int i=m-2;i>=0;i--) {
            for (int j=0;j<26;j++)
              nexc[i][j]=nexc[i+1][j];
            for (int j=0;j<10;j++)
              nexn[i][j]=nexn[i+1][j];
            if (S[i+1]>='a'&&S[i+1]<='z') nexc[i][S[i+1]-'a']=i+1;
              else nexn[i][S[i+1]-'0']=i+1;
        }
        for (int j=0;j<26;j++)
          Nexc[j]=nexc[0][j];
        for (int j=0;j<10;j++)
          Nexn[j]=nexn[0][j];
        if (S[0]>='a'&&S[0]<='z') Nexc[S[0]-'a']=0;
              else Nexn[S[0]-'0']=0;
        cnt[m-1]=cnt1[m-1]=cnt2[m-1]=0;
        for (int i=1;i<=31;i++) vis[m-1][i]=false;
        for (int i=m-2;i>=0;i--) {
            if (cnt[i+1]==29) cnt[i]=29;
            else {
                cnt[i]=0;
                for (int j=1;j<=29;j++) {
                    vis[i][j]=false;
                    if (vis[i+1][j]) vis[i][j]=true;
                    else {
                        int x=j/10,y=j%10;
                        int p=nexn[nexn[i][x]][y];
                        if (p<m) vis[i][j]=true;
                    }
                    if (vis[i][j]) cnt[i]++;
                }
            }
            if (cnt1[i+1]==30) cnt1[i]=30;
            else {
                vis[i][30]=false;
                cnt1[i]=cnt[i];
                if (vis[i+1][30]) vis[i][30]=true;
                else {
                    int x=3,y=0;
                    int p=nexn[nexn[i][x]][y];
                    if (p<m) vis[i][30]=true;
                }
                if (vis[i][30]) cnt1[i]++;
            }
            if (cnt2[i+1]==31) cnt2[i]=31;
            else {
                vis[i][31]=false;
                cnt2[i]=cnt1[i];
                if (vis[i+1][31]) vis[i][31]=true;
                else {
                     int x=3,y=1;
                    int p=nexn[nexn[i][x]][y];
                    if (p<m) vis[i][31]=true;
                }
                if (vis[i][31]) cnt2[i]++;
            }
        }
        long long ans=0;
        for (int i=1;i<=n;i++) {
            string str;
            cin>>str;
            int len=str.size();
            int p=Nexc[str[0]-'a'];       
            for (int i=1;i<len&&p<m;i++) 
                p=nexc[p][str[i]-'a'];
            if (p>=m) continue;
            for (int i=1;i<=12;i++) {
                int x=i/10,y=i%10;
                int q=nexn[nexn[p][x]][y];
                if (q>=m) continue;
                if (i==1||i==3||i==5||i==7||i==8||i==10||i==12) ans+=cnt2[q];
                else if (i==2) ans+=cnt[q];
                  else ans+=cnt1[q];
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}