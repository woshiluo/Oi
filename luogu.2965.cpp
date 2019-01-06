#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct name{
	int x,y,col;
};

queue<name> q;

int m,n,x,y,c,temp_col,ans=-1;
int col[110][110],coin[110][110];
int dx[4]={+1,-1,0,0};
int dy[4]={0,0,+1,-1};
bool map[110][110];

void bfs(){
	while(!q.empty()){
		name u=q.front();q.pop();
		if(u.x==m&&u.y==m){
			ans=coin[m][m];
			return ;
		}
		for(int i=0;i<4;i++){
			x=u.x+dx[i];y=u.y+dy[i];
			if(x>0&&y>0&&x<=m&&y<=m){
				name te;
				te.x=x;te.y=y;te.col=0;
				if(!map[x][y]){
					if((col[u.x][u.y]==col[x][y]||(col[x][y]==u.col&&&u.col!=0))&&coin[x][y]>coin[u.x][u.y]||coin[x][y]==-1){
						map[x][y]=true;
						coin[x][y]=coin[u.x][u.y]+1;
						q.push(te);
						map[x][y]=false;
					}
					else if(col[x][y]!=0&&coin[x][y]>coin[u.x][u.y]+1){
						map[x][y]=true;
						coin[x][y]=coin[u.x][u.y]+1;
						q.push(te);
						map[x][y]=false;
					}
					else if(col[x][y]==0&&u.col==0&&coin[x][y]>coin[u.x][u.y]+2){
						map[x][y]=true;
						coin[x][y]=coin[u.x][u.y]+2;
						te.col=col[u.x][u.y];
						q.push(te);
						map[x][y]=false;				
					}
				}
			}
		}
	}
}

int main(){
	memset(coin,-1,sizeof(coin));
	scanf("%d%d",&m,&n);
	for(int i=0;i<n;i++){
		scanf("%d%d%d",&x,&y,&c);
		if(c==0) temp_col=1;
		else if(c==1) temp_col=2;
		else temp_col=0;
		col[x][y]=temp_col;
	}
	name s;
	s.col=0;s.x=1;s.y=1;
	q.push(s);
	map[1][1]=true;
	bfs();
	printf("%d",ans);
}
