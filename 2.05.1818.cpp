#include <cstdio>
using namespace std;

int w,h,x,y,cnt=0,dx[4]={0,0,-1,+1},dy[4]={-1,+1,0,0};
char a[110][110];

void dfs(){
	for(int i)		
}
int main(){
	scanf("%d %d",&w,&h);
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			scanf("%c",&a[i][j]);
			if(a[i][j]=='@') y=j,x=i;
		}
	}
}

