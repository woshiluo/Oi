#include <bits/stdc++.h>
using namespace std;
int n,x,y;
int a[100010],p[100010][210];
long long f[100010][210],g[100010][210];

bool cmp(int p1,int p2) { return p1>p2; }

int main()
{
	scanf("%d%d%d",&n,&x,&y);
	int s=x+y;
	for (int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	sort(a+1,a+n+1,cmp); 

	for (int i=n;i>=1;i--)
		for (int j=0;j<=s;j++) {
			f[i][j]=0;g[i][j]=0;
			for (int k=0;k<=j;k++) {
				if (k+1<=s-j&&g[i+1][j+k+1]+a[i]>g[i+1][j-k]) {
					f[i][j]=max(f[i][j],f[i+1][j+k+1]);
				}
				else {
					f[i][j]=max(f[i][j],f[i+1][j-k]+a[i]);
				}
			}
			for (int k=0;k<=s-j;k++) {
				if (k<=j&&f[i+1][j-k]+a[i]>f[i+1][j+k]) {
					g[i][j]=max(g[i][j],g[i+1][j-k]);
				}
				else {
					g[i][j]=max(g[i][j],g[i+1][j+k]+a[i]); 
				}
			}
		}
	cout<<f[1][x];
	return 0;
}
