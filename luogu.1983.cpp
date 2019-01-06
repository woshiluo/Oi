#include <cstdio>
using namespace std;

const int N=1100;

int n,m,c,tmp,fi,la;
bool vis[N];

// edge start
struct edge{
	int next,to;
}e[N*N];
int ehead[N],ecnt;
inline void add_edge(int now,int to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end

int main(){
	scanf("%d%d",&n,&m);	
	for(int i=1;i<=m;i++){
		scanf("%d",&c);
		scanf("%d",&fi);
		c--;
		while(c--){
			scanf("%d",&tmp);
			la=tmp;
			vis[tmp]=true;
		}
		for(int j=fi;j<=la;j++){
			if(!vis[j]) add_edge(fi,j);
			else vis[j]=false;
		}
	}
	dfs(1);
}
