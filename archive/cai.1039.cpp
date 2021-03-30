#include <cstdio>
using namespace std;

int n;
int a[110][110],b[110][110];
int dx[8]={-2,-1,-2,1,2,2,1,-1};
int dy[8]={-1,2,1,2,1,-1,-2,-2};
bool yx[110][110],z;

void dfs(int x,int y,int deep){
	if(z) return ;
	if(deep==n*n){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%d ",a[i][j]);
			}	
			printf("\n");
		}
		z=true;
		return ;
	}
	for(int i=0;i<8;i++){
		int tx=x+dx[i],ty=y+dy[i];
		if(tx>=1&&ty>=1&&tx<=n&&ty<=n&&!yx[tx][ty]){
			a[tx][ty]=deep+1;
			yx[tx][ty]=true;
			dfs(tx,ty,deep+1);
			yx[tx][ty]=false;
			a[tx][ty]=0;
		}
	}
}

int main(){
	scanf("%d",&n);
	a[1][1]=1;
	yx[1][1]=1;
	dfs(1,1,1);
	if(!z) printf("-1");
}
