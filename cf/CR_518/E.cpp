#include <cstdio>

const int N=110000;

int n,k,u,v;
int low[N];
bool vis[N],deg[N];

// edge start 
struct edge{
	int to,next;
}e[N<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to){
	ecnt++;
	e[ecnt].to=to;
	e[ecnt].next=ehead[now];
	ehead[now]=ecnt;
}
// edge end
// bfs start
struct que{
	int now,dep;
}q[N];
int head,tail,cnt,id;

inline bool bfs(){
	head=tail=0;
	for(int i=1;i<=n;i++){
		if(low[i]==1){
			q[head].now=i;
			break;
		}
	}
	while(head<=tail){
		for(int i=ehead[q[head].now];i;i=e[i].next){
			if(q[head].dep+1>k) break;	
			if(!vis[e[i].to]&&low[e[i].to]>=3){
				if(q[head].dep+1==k){ 
					//cnt++;
					if(id) return false;
					id=e[i].to;
					vis[e[i].to]=true;
				}
				vis[e[i].to]=true;
				que tmp=q[head];
				tmp.now=e[i].to;
				tmp.dep++;
				q[++tail]=tmp;
			}			
		}	
		head++;
	}
	return true;
}
// bfs end
// dfs start 
bool dfs(int now,int la,int ka){
	int son=0;bool flag=true;
	for(int i=ehead[now];i;i=e[i].next){
		if(la==e[i].to) continue;
		if(low[e[i].to]==1){
			if(ka>1) return false;
			son++;
		}
		else if(low[e[i].to]==2) return false;
		else if(low[e[i].to]>=3){
			if(ka<=1) return false;
			flag=flag&&dfs(e[i].to,now,ka-1);
			son++;
		}
	}	
	if(son<3) flag=false;
	return flag;
}
// dfs end 
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
		low[v]++;
		low[u]++;
	}
	if(bfs()){
		if(id==0) printf("No\n");
		else if(dfs(id,0,k)) printf("Yes\n");
		else printf("No\n");
	}
	else printf("No\n");
}
