#include <cstdio>
#include <cstring>

const int N=1e5+1e4;

int n,k,cnt,tmp;
int vis[N];
int ans[N];

int main(){
	scanf("%d%d",&k,&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&tmp);
		if(vis[tmp]) vis[tmp]++; 
		else {
			vis[tmp]=1;
			cnt++;
		}
		if(cnt==k){
			for(int i=1;i<=k;i++){
				vis[i]--;
				if(vis[i]==0) cnt--;
			}
			ans[i]=1;
		}
	}
	for(int i=1;i<=n;i++) printf("%d",ans[i]);
}
