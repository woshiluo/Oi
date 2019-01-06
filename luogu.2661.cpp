#include <cstdio>

inline int Min(int a,int b){return a<b?a:b;}

const int N=210000;

int fa[N],son[N],n,v,ans=0x7fffffff;

int get_fa(int now){
	if(fa[now]==now) return fa[now];
	else return fa[now]=get_fa(fa[now]);
}

inline void Merge(int left,int rig){
	son[get_fa(left)]+=son[get_fa(rig)];
	fa[rig]=left;
	get_fa(rig);
}

int main(){
	freopen("luogu.2661.in","r",stdin);
	freopen("luogu.2661.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {fa[i]=i;son[i]=1;}
	for(int i=1;i<=n;i++){
		scanf("%d",&v);	
		if(get_fa(i)!=get_fa(v)) Merge(v,i);
		else ans=Min(ans,son[get_fa(i)]);
	}
	printf("%d\n",ans-1);
}
