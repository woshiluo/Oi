#include<bits/stdc++.h>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
typedef long long ll;
const int maxn=500+5;
int n;
ll p;
const int pr[]={2,3,5,7,11,13,17,19},m=256;
ll dp[m][m],f1[2][m][m],f2[2][m][m];
int d[maxn],ord[maxn],t[maxn];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	p=readint();
	for(int i=2;i<=n;i++){
		d[i]=i;
		for(int j=0;j<8;j++) if(d[i]%pr[j]==0){
			t[i]|=1<<j;
			while(d[i]%pr[j]==0) d[i]/=pr[j];
		}
	}
	for(int i=2;i<=n;i++) ord[i]=i;
	sort(ord+2,ord+n+1,[](int a,int b){
		return d[a]<d[b];
	});
	for(int i=0;i<m;i++) for(int j=0;j<m;j++)
		if(!(i&j)) f1[1][i][j]=f2[1][i][j]=dp[i][j]=1%p;
	for(int i=2;i<=n;i++){
		for(int j=0;j<m;j++) for(int k=0;k<m;k++) if(!(j&k)){
			f1[i%2][j][k]=f1[(i-1)%2][j][k];
			if(!(k&t[ord[i]]))
				f1[i%2][j][k]=(f1[i%2][j][k]+f1[(i-1)%2][j|t[ord[i]]][k])%p;
			f2[i%2][j][k]=f2[(i-1)%2][j][k];
			if(!(j&t[ord[i]]))
				f2[i%2][j][k]=(f2[i%2][j][k]+f2[(i-1)%2][j][k|t[ord[i]]])%p;
		}
		if(i==n||d[ord[i]]==1||d[ord[i+1]]!=d[ord[i]])
			for(int j=0;j<m;j++) for(int k=0;k<m;k++) if(!(j&k))
				f1[i%2][j][k]=f2[i%2][j][k]=dp[j][k]=(f1[i%2][j][k]+f2[i%2][j][k]-dp[j][k]+p)%p;
	}
	printf("%lld\n",dp[0][0]);
	return 0;
}
