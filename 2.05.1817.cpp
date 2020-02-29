#include <cstdio>
using namespace std;

int m,n,a[11000][11000],max=-1;

int dfs(int x,int y){
	int k=a[x][y],cnt=1;
	if(k==0){
		if(y-1>=0) cnt+=dfs(x,y-1);
		if(y+1<n) cnt+=dfs(x,y+1);
		if(x-1>=0) cnt+=dfs(x-1,y);
		if(x+1<m) cnt+=dfs(x+1,y);
		return cnt;
	}
	if(k>=8) k-=8;
	else if(x+1<m) cnt+=dfs(x+1,y);
	if(k>=4) k-=4;
	else if(y+1<n) cnt+=dfs(x,y+1);
	if(k>=2) k-=1;
	else if(x-1>=0) cnt+=dfs(x-1,y);
	if(k>=1) k-=1;
	else if(y-1>=0) cnt+=dfs(x,y-1);
	return cnt;
}

int main(){
	scanf("%d %d",&m,&n);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(max<dfs(i,j)) max=dfs(i,j);
		}
	}
	printf("%d",max);
}
