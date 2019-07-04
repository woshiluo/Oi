#include <cstdio>
#include <cstring>
using namespace std;

char a[10],b[10],c[10];
int alen,blen,clen;
int d[30];


void dfs(int la,int ra,int lb,int rb){
	if(la>ra) return ;
	int ta=d[b[rb]];
	printf("%c",b[rb]);
    dfs(la,ta-1,lb,rb-ra+ta-1);
	dfs(ta+1,ra,lb+ta-la,rb-1);
}

int main(){
	scanf("%s",a);
	scanf("%s",b);
	alen=strlen(a);
	blen=strlen(b);
	for(int i=0;i<blen;i++) d[a[i]]=i; 
	dfs(0,alen-1,0,blen-1);
	return 0;
}
