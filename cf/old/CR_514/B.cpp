#include <cstdio>

const int N=1100;

int n,m;
char s[N];
int a[N][N];
bool vis[N][N];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		for(int j=0;j<m;j++){
			if(s[j]=='#') a[i][j+1]=1;
			else a[i][j+1]=0;
		}
	}
	for(int i=1;i<=n-2;i++){
		for(int j=1;j<=m-2;j++){
			if(a[i][j]==1){
				if(a[i][j+1]==a[i][j]&&a[i][j+2]==a[i][j]&&a[i+1][j]==a[i][j]&&a[i+1][j+2]==a[i][j]&&a[i+2][j]==a[i][j]&&a[i+2][j+2]==a[i][j]&&a[i+2][j+1]==a[i][j]){
					vis[i][j]=vis[i][j+1]=vis[i][j+2]=vis[i+1][j]=vis[i+1][j+2]=vis[i+2][j]=vis[i+2][j+2]=vis[i+2][j+1]=true;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==1&&vis[i][j]==false){
				printf("NO");
				return 0;
			}
		}
	}
	printf("YES");
}
