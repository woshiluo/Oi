#include <cstdio>
using namespace std;

int n,r,a[30];

void dfs(int deep,int temp){
	if(deep==r){
		for(int i=0;i<r;i++) printf("%d ",a[i]);
		printf("\n");
	}	
	for(int i=temp+1;i<=n;i++){
		a[deep]=i;
		dfs(deep+1,i);
		a[deep]=0;
	}
}

int main(){
	scanf("%d%d",&n,&r);
	dfs(0,0);
}
