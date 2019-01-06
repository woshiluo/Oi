#include <cstdio>
#include <cstring>
using namespace std;

char a[110],b[110],x[110];
int lx,k[110];

void dfs(int la,int ra,int lb,int rb){
	if(la>ra) return ;
	int temp_a=k[a[la]]-lb;
	dfs(la+1,la+temp_a,lb,k[a[la]]-1);
	dfs(la+temp_a+1,ra,k[a[la]]+1,rb);
	x[lx++]=a[la];
}

int main(){
	scanf("%s",a);
	scanf("%s",b);
	int lena=strlen(a);
	int lenb=strlen(b);
	for(int i=0;i<lenb;i++) k[b[i]]=i;
	lx=0;
	dfs(0,lena-1,0,lenb-1);
	for(int i=0;i<lx;i++){
		printf("%c",x[i]);
	}
}
