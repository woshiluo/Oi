#include<bits/stdc++.h>
using namespace std;
int n,a[100010],b[100010],c[100010],d[100010],id[200010];
int A[100010],B[100010],vis[100010];
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i]>>c[i]>>d[i];
        id[a[i]]=id[b[i]]=i;
    }
    for(int i=1;i<=n+n;i++){
        if(vis[id[i]])continue;
        if(a[id[i]]==i&&c[id[i]]){
            vis[id[i]]=1;
            A[++A[0]]=id[i];
        }
        if(b[id[i]]==i&&d[id[i]]){
            vis[id[i]]=1;
            B[++B[0]]=id[i];
        }
    }
    cout<<A[0]<<' ';
    for(int i=1;i<=A[0];i++)
        cout<<A[i]<<" \n"[i==A[0]];
    cout<<B[0]<<' ';
    for(int i=1;i<=B[0];i++)
        cout<<B[i]<<" \n"[i==B[0]];
}