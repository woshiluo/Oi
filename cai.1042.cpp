#include <cstdio>
using namespace std;

int n,m,best=0x7fffffff;
int a[210];
bool x[210];


int jd(int temp){
	if(temp>0) return temp;
	else return 0-temp;
}

void dfs(int deep){
	if(best==m) return ;
	for(int i=1;i<=n;i++){
		if(x[i]) continue;
		if(!x[i]){
			if(a[i]==m||a[i]+deep==m){
				best=m;
				return ;
			}
			else if(jd(a[i]+deep-m)<jd(m-best)){
				best=a[i]+deep;
			}
			else if(a[i]+deep>m){
				return ;
			}
			else{
				x[i]=true;
				dfs(a[i]+deep);
				x[i]=false;
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	dfs(0);
	printf("%d",best);
}
