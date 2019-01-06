#include <cstdio>
using namespace std;

int n;
int a[110];
bool x[110],y;

void dfs(int deep){
	if(deep==n+1){
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
	}	
	else {
		for(int i=1;i<=n;i++){
			if(!x[i]){
				y=false;
				int temp=i;
				for(int j=deep-1;j>0;j--){
					temp--;
					if(temp==a[j]) y=true;
				}
				temp=i;
				for(int j=deep-1;j>0;j--){
					temp++;
					if(temp==a[j]) y=true;
				}
				if(y) continue;
				a[deep]=i;
				x[i]=true;
				dfs(deep+1);
				x[i]=false;
				a[deep]=0;
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	dfs(1);
	return 0;
}
