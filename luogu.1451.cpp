#include <cstdio>
using namespace std;

int n,m,cnt;
int a[110][110],b[110][110];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

/*void dfs(int i,int j,int now,int temp){	
	if(temp==1) cnt++;
	for(int k=0;k<4;k++){
		int tx=i+dx[k];
		int ty=j+dy[k];
		a[i][j]=0;
		if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&a[tx][ty]!=0) {
			dfs(tx,ty,now,temp+1);
		}
	}
}*/


int main(){
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=n;i++){ 
		for(int j=1;j<=m;j++){
			scanf("%1d",&a[i][j]);
		}
	}
/*	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=0) {
				dfs(i,j,a[i][j],1);
			}
		}
	}*/
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!=0){
				if(b[i-1][j]!=0&&i-1>=1){
					b[i][j]=a[i-1][j];
				}
				if(b[i][j-1]!=0&&j>=1){
				
				}
			}
		}
	}
	printf("%d",cnt);
}
