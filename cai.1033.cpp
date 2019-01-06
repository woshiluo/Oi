#include <cstdio>
#include <cmath>
using namespace std;

int a[30],b[30],temp_cnt,cnt;
int n,k,r;

bool zs(int n){
	for(int i=2;i<=sqrt(n)+2;i++){
		if(n%i==0) return false;
	}
	return true;
}

void dfs(int deep,int temp){
	if(deep==r) {
		temp_cnt=0;
		for(int i=0;i<r;i++){
			temp_cnt+=a[b[i]];
		}
		if(zs(temp_cnt)) cnt++;
	}
	for(int i=temp+1;i<=n;i++){
		b[deep]=i;
		dfs(deep+1,i);
		b[deep]=0;
	}
}

int main(){
	scanf("%d%d",&n,&r);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	dfs(0,0);
	printf("%d",cnt);
}
