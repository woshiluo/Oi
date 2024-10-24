#include<bits/stdc++.h>
using namespace std;
bool js;
int ans,last=1,num=1,Len,fa[2000010],len[2000010],son[2000010]['z'-'A'+1];
int st[2000010],rk[2000010],sze[2000010],Minpos[2000010],pos[2000010];
char str[1000010];
long long tot[200],sum[1000010],ssum[1000010];
bool ks;
void insert(int ch)
{
    int y=last,x=last=++num;
    len[x]=len[y]+1;sze[x]=1;
    for(;y&&!son[y][ch];y=fa[y])
        son[y][ch]=x;
    if(!y)return fa[x]=1,void();
    int z=son[y][ch];
    if(len[z]==len[y]+1)return fa[x]=z,void();
    int clone=++num;
    memcpy(son[clone],son[z],232);
    fa[clone]=fa[z];fa[z]=fa[x]=clone;
    len[clone]=len[y]+1;
    for(;y&&son[y][ch]==z;y=fa[y])
        son[y][ch]=clone;
}
int main()
{
    // cout<<(&js-&ks)/1024./1024<<endl;
    // cout<<'z'-'A'+1<<endl;?
    scanf("%s",str+1);
    Len=strlen(str+1);
    for(int i=1;i<=Len;i++){
        // memcpy(sum[i],sum[i-1],480);
        // sum[i][str[i]-'A']++;
        // memcpy(ssum[i],ssum[i-1],480);
        // for(int j=0;j<58;j++)
            // ssum[i][j]+=sum[i][j];
        insert(str[i]-'A');
        Minpos[pos[i]=last]=i;
    }
    for(int i=1;i<=num;i++)st[len[i]]++;
    for(int i=1;i<=Len;i++)st[i]+=st[i-1];
    for(int i=1;i<=num;i++)rk[st[len[i]]--]=i;
    for(int i=num;i;i--){
        sze[fa[rk[i]]]+=sze[rk[i]];
        if(!Minpos[fa[rk[i]]])
            Minpos[fa[rk[i]]]=Minpos[rk[i]];
        Minpos[fa[rk[i]]]=min(Minpos[rk[i]],Minpos[fa[rk[i]]]);
    }
    for(int i=1;i<=num;i++){
        int cnt=len[rk[i]]-len[fa[rk[i]]];
        // int r=Minpos[rk[i]],l1=r-len[rk[i]]+1,l2=r-len[fa[rk[i]]];
        // for(int j=0;j<58;j++)
        //     tot['A'+j]+=sum[r][j]*cnt-(ssum[l2-1][j]-ssum[l1-2][j]);
        int temp=sze[rk[i]];
        while(temp){
            tot[48+temp%10]+=cnt;
            temp/=10;
        }
    }
    for(int j='A';j<='Z';j++){
        for(int i=1;i<=Len;i++){
            sum[i]=sum[i-1]+(str[i]==j);
            ssum[i]=ssum[i-1]+sum[i];
        }
        for(int i=1;i<=num;i++){
            int cnt=len[rk[i]]-len[fa[rk[i]]];
            int r=Minpos[rk[i]],l1=r-len[rk[i]]+1,l2=r-len[fa[rk[i]]];
            tot[j]+=sum[r]*cnt-(ssum[l2-1]-ssum[l1-2]);
        }
    }
    for(int j='a';j<='z';j++){
        for(int i=1;i<=Len;i++){
            sum[i]=sum[i-1]+(str[i]==j);
            ssum[i]=ssum[i-1]+sum[i];
        }
        for(int i=1;i<=num;i++){
            int cnt=len[rk[i]]-len[fa[rk[i]]];
            int r=Minpos[rk[i]],l1=r-len[rk[i]]+1,l2=r-len[fa[rk[i]]];
            tot[j]+=sum[r]*cnt-(ssum[l2-1]-ssum[l1-2]);
        }
    }
    for(int i='0';i<='z';i++)
    if(tot[i])
        cout<<char(i)<<' '<<tot[i]<<endl;
}