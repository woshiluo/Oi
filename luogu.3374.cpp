#include <cstdio>

inline int lowbit(int now){return now&(-now);}

const int N=510000;

int n,m,tmp;
int x,y,op;

// Bit start
int tree[N];

int ask(int now){
	int ans=0;
	for(int i=now;i;i-=lowbit(i)) ans+=tree[i];
	return ans;
}

void add(int now,int val){
	for(int i=now;i<=n;i+=lowbit(i)) tree[i]+=val;
}

// Bit end

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&tmp);
		add(i,tmp);
	}
	for(int i=1;i<=m;i++){
		scanf("%d",&op);	
		if(op==1){
			scanf("%d%d",&x,&y);
			add(x,y);
		}
		if(op==2){
			scanf("%d%d",&x,&y);
			printf("%d\n",ask(y)-ask(x-1));
		}
	}
}
