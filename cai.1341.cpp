#include <cstdio>
using namespace std;

int n,max;
int a[20][20],cnt;
bool x[20];

void dfs(int deep){
	if(deep==n+1){
		if(cnt<max) max=cnt;
		cnt=0;
	}
	else {
		for(int i=2;i<=n;i++){
			if(!x[i]){
				
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	dfs(1);
}
