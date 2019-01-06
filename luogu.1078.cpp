#include <cstdio>
#include <cstring>
using namespace std;

int n,k,m,s,t,temp;
int wh[110],fl[110][110];;
bool bc[110][110];

int main(){
	memset(fl,9999,sizeof(fl));
	scanf("%d%d%d%d%d",&n,&k,&m,&s,&t);
	for(int i=0;i<n;i++){ 
		scanf("%d",&temp);
		wh[i]=temp-1;
	}
	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++){
			scanf("%d",&temp);
			if(temp==0) bc[i][j]=false;
			else bc[i][j]=true;
		}
	}
	//以下代码看了标称才打出来
	for(int i=0;i<m;i++){
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		if(!bc[wh[u-1]][wh[v-1]]){
			if(d<fl[v-1][u-1]) fl[v-1][u-1]=d;
		}
		if(!bc[wh[v-1]][wh[u-1]]){
			if(d<fl[u-1][v-1]) fl[u-1][v-1]=d;
		}
	}
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(!bc[wh[k]][wh[i]]&&!bc[wh[j]][wh[i]]&&!bc[wh[j]][wh[k]]){
					if(fl[i][k]+fl[k][j]<fl[i][j]) fl[i][j]=fl[k][j]+fl[i][k];			
				}
			}
		}
	}
	if(fl[s-1][t-1]>=0x7f) printf("-1");
	else printf("%d",fl[s-1][t-1]);
}
