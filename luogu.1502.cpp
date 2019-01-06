#include <cstdio>
#include <algorithm>

const int N=11000;

int T,n,W,H;

struct node{
	int x,y,li;
	bool f;
}line[N],col[N];

inline void init(){
}

inline void pre(){}

inline void readin(){
	scanf("%d%d%d",&n,&W,&H);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&line[i].x,&line[i].y,&line[i].li);	
	}
}

int main(){
	scanf("%d",&T);
	while(T--){
		init();
		readin();
		pre();
	}
}
