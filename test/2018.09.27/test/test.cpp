#include <cstdio>
#include <algorithm>

int n;
long long time,ans,tmp;

struct que{
	int ta,tb;
}q[110000];

bool cmp(que a,que b){return 1LL*a.ta*b.tb<1LL*b.ta*a.tb; }

int main(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&q[i].ta,&q[i].tb);
	std::sort(q+1,q+n+1,cmp);
	for(int i=1;i<=n;i++){
		tmp=1LL*time*q[i].tb+1LL*q[i].ta;
		ans+=tmp;
		time+=tmp;
	}
	printf("%lld",ans);
	fclose(stdin);
	fclose(stdout);
}
