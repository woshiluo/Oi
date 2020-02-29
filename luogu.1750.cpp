#include <cstdio>

const int N=11000;

int n,c,a[N],Min=0,cnt,now;
bool vis[N],flag;

int main(){
	a[0]=0x7fffffff;
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	while(1){
		flag=false;
		now=Min;
		Min=0,cnt=0;
		for(;;){
			now++;
			while(vis[now]) now++;
			if(now>n) break;
			cnt++;
			if(cnt>c) break;
			flag=true;	
			if(a[Min]>a[now]) Min=now;
		}
		if(!flag) break;
		vis[Min]=true;
		printf("%d ",a[Min]);
	}
	for(int i=n;i>=1;i--) if(!vis[i]) printf("%d ",a[i]);
}
