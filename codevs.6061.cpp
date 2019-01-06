#include <cstdio>
using namespace std;

int n,r,a[30];
bool x;


void dfs(int deep,int temp){
	if(deep==r){
		for(int i=0;i<r;i++) printf("%3d",a[i]);
		printf("\n");
	}
	else for(int i=1;i<=n;i++){
		x=false;
		for(int j=0;j<deep;j++){
			if(a[j]==i) x=true;
		}
		if(x) continue;
		a[deep]=i;
		dfs(deep+1,i);
		a[deep]=0;
	}
}

int main(){
	scanf("%d%d",&n,&r);
	dfs(0,0);
}
