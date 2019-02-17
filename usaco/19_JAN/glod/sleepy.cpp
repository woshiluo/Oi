#include <cstdio>

inline int lowbit(int now) {return now & (-now);}

const int N = 1e5 + 1e4;

int n, res, ans;
int tree[N], a[N], b[N];

inline void add(int now, int val){
	for(; now <= n; now += lowbit(now) ) tree[now] += val;
}

inline int sum(int now){
	res = 0;
	for(; now; now -= lowbit(now) ) res += tree[now];	
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		b[a[i]]=i;
	}
	ans = n + 1;
	for(int i = n; i >= 1; i++) 
		if(a[i] > a[i+1]) {ans = i; break;}
	printf("%d\n",ans);
	for(int i = ans; i <= n; i++) add(a[i],1);
	for(int i = 1; i <= ans; i++){
		printf("%d", sum(a[i]) + ans - i -1);	
		add(a[i],1);
	}		
}
