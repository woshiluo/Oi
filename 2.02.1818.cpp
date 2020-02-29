#include <bits/stdc++.h>
using namespace std;
int dx[4]={0,0,-1,+1},dy[4]={+1,-1,0,0},m,n,cnt=0,x,y;
char a[101][101];
void search(int x,int y){
	for(int i=0;i<=3;i++)
		int xx=x+dx[i],yy=y+dy[i];
		if(xx>=1 && xx<=m && yy>=1 && yy<=n && a[xx][yy]=='.')//满足条件 
			a[xx][yy]='#';cnt++;search(xx,yy);//标记成已经包括的，回溯 
	}
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			scanf("%c",&a[i][j]);
			if(a[i][j]=='@')x=i;y=j;
		} 
	search(x,y);//因为每一次搜索完之后都要加一 
	printf("%d",cnt);
}
