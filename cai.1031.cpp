#include <cstdio>
using namespace std;

int n,a[30];
bool x;

void dfs(int deep){
	if(deep==n+1){
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
	}
	else for(int i=1;i<=n;i++){
		x=false;
		for(int j=1;j<deep;j++){
			if(a[j]==i) x=true;		
		}
		if(x) continue;
		a[deep]=i;
		dfs(deep+1);
		a[deep]=0;
	}
}

int main(){
	scanf("%d",&n);
	dfs(1);

}
