#include <cstdio>
#include <cstring>

long long n,cnt,ans=99999999999,ncnt;
char num[25][50]={"","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty"};
char num2[10][25]={"","a","both","another","first","second","third"};
char s[10][110];
long long a[10];
bool vis[10];

void dfs(long long now,long long depth){
	if(depth==ncnt){
		if(now<=ans) ans=now;
		return ;
	}
	for(long long i=1;i<=ncnt;i++){
		if(vis[i]==false){
			vis[i]=true;
			dfs(now*100+a[i],depth+1);
			vis[i]=false;
		}	
	}	
}

int main(){
	while(scanf("%s",s[cnt++])!=EOF);
	for(long long i=0;i<cnt;i++){
		for(long long j=1;j<=20;j++){
			if(strcmp(num[j],s[i])==0){
				a[++ncnt]=(j*j)%100;
				break;
			}
		}
	}
	for(long long i=0;i<=cnt;i++){
		for(long long j=1;j<=6;j++){
			if(strcmp(num2[j],s[i])==0){
				a[++ncnt]=(j*j)%100;
				break;
			}
		}	
	}
	dfs(0,0);
	printf("%lld",ans);
}
