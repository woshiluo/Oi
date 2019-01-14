#include <cstdio>

inline int Min(int a,int b){return a<b?a:b;}
inline int Max(int a,int b){return a>b?a:b;}
inline int Aabs(int a) {return a<0?(0-a):a;}

int n,k,test,chat,tmp,tmp_test,tmp_chat,ans=-2147483647;
bool vis[1100];

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&tmp);
		if(tmp==-1) vis[i]=false,chat++;
		else vis[i]=true,test++;
	}
	for(int b=1;b<=n;b++){
		tmp_test=test;
		tmp_chat=chat;
		for(int i=1;i<=n;i++){
			if((i-b)%k==0){
				if(vis[i]) tmp_test--;
				else tmp_chat--;
			}
		}
		ans=Max(ans,Aabs(tmp_test-tmp_chat));
	}
	printf("%d",ans);
}
