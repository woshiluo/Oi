#include <cstdio>
#include <cstring>
using namespace std;

char a[110][110];
int k,cnt=0,temp,la,ha,lb,hb,dx[4]={-1,+2,-1,0},dy[4]={0,0,+1,-2};
bool yn[110]={false};

void sreach(int x,int y){
	if(x==hb&&y==lb) yn[cnt]=true;
	for(int i=0;i<4;i++){
		x+=dx[i];y+=dy[i];
		if(x>=0&&y>=0&&y<temp&&y<temp&&a[x][y]=='.'){
			a[x][y]='@';
			sreach(x,y);
		}
	}	
}

int main(){
	scanf("%d",&k);
	for(int i=0;i<k;i++){
		cnt++;
		scanf("%d",&temp);
		memset(a,0,sizeof(a));
		for(int i=0;i<temp;i++){
			scanf("%s",a[i]);
		}
		scanf("%d %d %d %d",&ha,&la,&hb,&lb);
		if(a[ha][la]=='#'||a[hb][lb]=='#'){
			yn[cnt]=false;
			continue;
		}
		a[ha][la]='@';
		sreach(ha,la);
	}
	for(int i=1;i<=k;i++){
		if(yn[i]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
