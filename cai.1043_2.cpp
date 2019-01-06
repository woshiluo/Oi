#include <cstdio>
#include <cmath>
using namespace std;

int n,cnt;


bool zs(int k){
	int temp=sqrt(k);
	for(int i=2;i<=temp;i++){
		if(k%i==0) return false;
	}
	return true;
}
void dfs(int deep){
	cnt++;
	if(zs(deep)) return ;
	for(int i=2;i<deep;i++){
		if(deep%i==0){
			dfs(deep/i);
		}
	}
}

int main(){
	scanf("%d",&n);
	dfs(n);
	printf("%d",cnt);
}
