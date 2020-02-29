#include <cstdio>
#include <cstring>
using namespace std;

int t,n,m;
int a[110][110],f[110][110],h[110],l[110],th[110],tl[110];
bool b[20][20],c[20][20];
int ans;

void dfs(int x,int y){
	if(ans>1) return ;
	if(x>n){
		bool mdzz=false;
		for(int i=1;i<=m;i++) if(tl[i]!=l[i]) mdzz=true;
		if(!mdzz){
			ans++;
			if(ans==1){
				for(int i=1;i<=n;i++){
					for(int j=1;j<=m;j++){
						f[i][j]=a[i][j];
					}
				}
			}
		}
	}
	else if(y>m){
		if(th[x]==h[x]) dfs(x+1,1);
	}
	else if(a[x][y]!=0) dfs(x,y+1);
	else {
		for(int i=1;i<10;i++){
			if(! b[x][i] && ! c[y][i]&&th[x]<h[x]&&tl[y]<l[y]){
				a[x][y]=i;
				b[x][i]=c[y][i]=true;
				th[x]+=i;
				tl[y]+=i;
				dfs(x,y+1);
				th[x]-=i;
				tl[y]-=i;
				b[x][i]=c[y][i]=false;
				a[x][y]=0;
			}
		}
	}

}

int main(){
	scanf("%d",&t);
	for(int i=0;i<t;i++){
		scanf("%d%d",&n,&m);
		ans=0;
		memset(a,0,sizeof(a));
		memset(h,0,sizeof(h));
		memset(l,0,sizeof(l));
		memset(th,0,sizeof(th));
		memset(tl,0,sizeof(tl));
		memset(c,false,sizeof(c));
		memset(b,false,sizeof(b));
		for(int j=1;j<=n;j++) scanf("%d",&h[j]);
		for(int j=1;j<=m;j++) scanf("%d",&l[j]);

		for(int j=1;j<=n;j++){
			for(int k=1;k<=m;k++){
				scanf("%d",&a[j][k]);
				b[j][a[j][k]]=c[k][a[j][k]]=true;
				th[j]+=a[j][k];
				tl[k]+=a[j][k];
			}
		}
		dfs(1,1);
		if(ans==1){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=m;k++){
					printf("%d ",f[j][k]);
				}
				printf("\n");
			}
		}
		else if(ans==0){
			printf("No answer.\n");
		}
		else printf("Not unique.\n");
	}	
}
