#include <cstdio>
#include <cstring>

const int N=110;

int n,k;
int a[N][N],high[N],low[N];
bool vis[N][N];

struct que{
	int x,y;
}q[N*N];
int head,tail;
int dx[4]={+1,-1,0,0};
int dy[4]={0,0,+1,-1};
inline int bfs(int i,int j){
	head=tail=0;
	q[head].x=i;q[head].y=j;
	while(head<=tail){
		que top=q[head];
		for(int i=0;i<4;i++){
			que tmp=top;
			top.x+=dx[i];
			top.y+=dy[i];

			if(vis[top.x][top.y]) continue;
			vis[top.x][top.y]=true;

		}	
	}
}

bool fill(){
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(vis[i][j]) continue;
			else bfs(i,j);
		}
	}
	return false;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%1d",&a[i][j]);
			if(a[i][j]!=0){
				if(high[i]==0) high[j]=i;
				else low[j]=i;
			}
		}		
	}
	while(fill())fail();
}
