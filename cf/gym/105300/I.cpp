#include <bits/stdc++.h>
using namespace std;
struct Node{
    int pos,val;
}b[300010],f[300010];
int c[300010];
bool cmp(Node p1,Node p2)
{
    return p1.pos<p2.pos;
}
int main()
{
    int n,m,D;
    cin>>n>>m>>D;
    for (int i=1;i<=n;i++) cin>>b[i].pos;
    for (int i=1;i<=m;i++) cin>>f[i].pos>>f[i].val;
    sort(b+1,b+n+1,cmp);
    sort(f+1,f+m+1,cmp);
    int p=1;
    long long ans=0;
    priority_queue<pair<int,int>> q;
    for (int i=1;i<=m;i++) {
        while (p<=n&&b[p].pos<=f[i].pos+D) {
            q.push(make_pair(0,-p));
            c[p]=0;
            p++;
        }
        while (q.size()&&-q.top().first<f[i].val) {
            int x=-q.top().second;q.pop();
            if (b[x].pos>=f[i].pos-D) {
                c[x]=f[i].val;
                q.push(make_pair(-c[x],-x));
                break;
            }
            else ans+=c[x];
        }
    }
    while (q.size()) {
        int x=-q.top().second;q.pop();
        ans+=c[x];
    }
    cout<<ans;
    return 0;
}