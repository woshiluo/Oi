#include <cstdio>
#include <cstring>
const int N=2100;

inline int Min(int a,int b){return a<b?a:b;}
inline long long Max(long long a,long long b){return a>b?a:b;}

int n,m;
int a[N],b[N];
int sa[N],sb[N],len[N],ans,res;
long long x;

inline long long binary_serach(int now){
	int left,rig,mid;
	left=1;
	rig=n;
	while(left<=rig){
		mid=(left+rig)>>1;
		if(1LL*len[mid]*now==x) return mid;
		if(1LL*len[mid]*now<x) left=mid+1;
		else rig=mid-1;
	}
	return rig;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sa[i]=sa[i-1]+a[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&b[i]);
		sb[i]=sb[i-1]+b[i];
	}
	scanf("%lld",&x);
	memset(len,0x3f,sizeof(len));
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			len[j-i+1]=Min(len[j-i+1],sa[j]-sa[i-1]);
		}
	}

	for(int i=1;i<=m;i++){
		for(int j=i;j<=m;j++){
			int tmp=binary_serach(sb[j]-sb[i-1]);
			res=Max(tmp*(j-i+1),res);
		}
	}
	printf("%d",res);
}
