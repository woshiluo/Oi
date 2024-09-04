#include <bits/stdc++.h>
using namespace std;
int n;
int a[2010][2010],b[2010][4010],h[2010][4010];
int Min[4010][15],len[2010][4010],ans[2010][4010];
int c[2010],L[2010][2010],R[2010][2010];
int f[2010],g[15];
int Get_Min(int l,int r)
{
    if (l>r) return 0;
    int lenn=f[r-l+1];
    return min(Min[l][lenn],Min[r-g[lenn]+1][lenn]);
}
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void Print(int x)
{
    if (!x) return ;
    Print(x/10);
    putchar(x%10+'0');
}
int main()
{
    n=read();
    int p=n,pp=n;
    int N=2*(2*n-1)-1;
    for (int i=1;i<=2*n-1;i++) f[i]=log2(i);
    for (int i=0;i<=11;i++) g[i]=(1<<i); 
    for (int i=1;i<2*n;i++) {
        c[i]=p;
        for (int j=1;j<=p;j++) a[i][j]=read();
        for (int j=1;j<pp;j++) b[i][j]=-1;
        for (int j=1;j<=p;j++) b[i][pp+2*(j-1)]=a[i][j],h[i][pp+2*(j-1)]=j;
        for (int j=pp+2*(p-1)+1;j<=N;j++) b[i][j]=-1;
        if (i>=n) p--,pp++;
          else p++,pp--;
    }
    for (int i=1;i<2*n;i++) {
        for (int j=1;j<=c[i];j++) 
          if (a[i][j-1]==a[i][j]) L[i][j]=L[i][j-1]+1;
            else L[i][j]=1;
        for (int j=c[i];j>=1;j--)
          if (a[i][j+1]==a[i][j]) R[i][j]=R[i][j+1]+1;
            else R[i][j]=1;
    }
    // for (int i=1;i<=2*n-1;i++) {
    //     cout<<'\n';
    //     for (int j=1;j<=N;j++)
    //       cout<<b[i][j]<<' ';
    // }
    // cout<<'\n';
    for (int j=1;j<=N;j++) {
        for (int i=1;i<=2*n-1;i++) {
            len[i][j]=0;
            if (b[i][j]==-1) continue;
            if (b[i][j]==0) {
                if (b[i][j-1]==b[i][j+1]) len[i][j]=2*min(L[i][h[i][j-1]],R[i][h[i][j+1]]);
                  else len[i][j]=0; 
            }
            else len[i][j]=2*min(L[i][h[i][j]],R[i][h[i][j]])-1;
        }
        for (int i=1;i<=2*n-1;i++) Min[i][0]=len[i][j]-i;//len>=n-(x-i) len-i>=n-x
        for (int k=1;k<=11;k++) 
          for (int i=1;i<=2*n-1-g[k]+1;i++)
            Min[i][k]=min(Min[i][k-1],Min[i+g[k-1]][k-1]);
        int las=-1,t=1;
        for (int i=1;i<=2*n-1;i++) {
            if (b[i][j]==-1) continue;
            if (b[i][j]==0) {
                if (b[i][j-1]!=b[i][j+1]) las=-1;
                  else {
                      if (b[i][j-1]!=las) t=i;
                      las=b[i][j-1];
                  }
                continue;
            }
            if (b[i][j]!=las) t=i;
            las=b[i][j];
            int l=1,r=i-t+1;
            while (l<r) {
                int mid=(l+r+1)>>1;
                if (Get_Min(i-mid+1,i)<2*mid-1-i) r=mid-1;
                  else l=mid;
            }
            
            ans[i][j]=l;
        }
        for (int i=1;i<=2*n-1;i++) Min[i][0]=len[i][j]+i;//len>=n-(i-x) len+i>=n+x
        for (int k=1;k<=11;k++) 
          for (int i=1;i<=2*n-1-g[k]+1;i++)
            Min[i][k]=min(Min[i][k-1],Min[i+g[k-1]][k-1]);
        las=-1,t=2*n-1;
        for (int i=2*n-1;i>=1;i--) {
            if (b[i][j]==-1) continue;
            if (b[i][j]==0) {
                  if (b[i][j-1]!=b[i][j+1]) las=-1;
                  else {
                      if (b[i][j-1]!=las) t=i;
                      las=b[i][j-1];
                  }
                continue;
            }
            if (b[i][j]!=las) t=i;
            las=b[i][j];
            int l=1,r=t-i+1;
            while (l<r) {
                int mid=(l+r+1)>>1;
                if (Get_Min(i,i+mid-1)<2*mid-1+i) r=mid-1;
                  else l=mid;
            }
            // cout<<i<<' '<<h[i][j]<<"???"<<t<<' '<<l<<'\n';
            ans[i][j]=min(ans[i][j],l);
        }
    }
    for (int i=1;i<=2*n-1;i++) {
        for (int j=1;j<=N;j++)
          if (b[i][j]>0) 
            Print(ans[i][j]),putchar(' ');
        printf("\n");
    }
    return 0;
}