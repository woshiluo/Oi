#include <cstdio>

const int N=1100;

int n,cnt;
int a[N],k[N],kmp[N],ans[N],aid;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		k[i]=a[i]-a[i-1];
	}
	for(int i=2;i<=n;i++){
		while(cnt>0&&k[i]!=k[cnt+1]) cnt=kmp[cnt];
		if(k[i]==k[cnt+1]) cnt++;
		kmp[i]=cnt;
	}
	int tmp=n-kmp[n];
	for(int i=tmp;i<n;i+=tmp){
		//printf("%d ",i);
		ans[++aid]=i;
	}
	//printf("%d",n);
	ans[++aid]=n;
	printf("%d\n",aid);
	for(int i=1;i<=aid;i++) printf("%d ",ans[i]);
}
