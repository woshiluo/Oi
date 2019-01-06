#include <cstdio>
#include <queue>
using namespace std;

int deep[1100],floor[1100];
int n,a,b;
bool x;
queue<int> q;

void bfs(int start,int end){
	q.push(start);
	while(!q.empty()){
		int deepth=q.front();
		q.pop();
		if(deepth==end){
			x=true;
			printf("%d",deep[deepth]);
			return ;
		}
		if(floor[deepth]+deepth<=n&&!deep[floor[deepth]+deepth]){
			deep[deepth+floor[deepth]]=deep[deepth]+1;
			q.push(deepth+floor[deepth]);
		}
		if(deepth-floor[deepth]>0&&!deep[deepth-floor[deepth]]){
			deep[deepth-floor[deepth]]=deep[deepth]+1;
			q.push(deepth-floor[deepth]);
		}
	}
}

int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++){
		scanf("%d",&floor[i]);
	}
	bfs(a,b);
	if(!x) printf("-1");
}
