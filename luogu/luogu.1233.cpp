#include <cstdio>
#include <algorithm>

const int N=5100;

struct sti{
	int w,l;
}s[N];

int n;

bool cmp(sti a,sti b){return a.w<b.w;}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&s[i].l,&s[i].w);
	std::sort(s+1,s+n+1,cmp);
	
}
