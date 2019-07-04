#include <cstdio>
#include <algorithm>

const long long N = 2e5 + 1e4;

struct node{
	long long now, id;
}b[N];

long long n, m, k, cnt, time;
long long a[N];
bool vis[N];

bool cmp(node a, node b){
	return a.now > b.now;
}

int main(){
	scanf("%lld%lld%lld", &n, &m, &k);
	for(long long i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
		b[i].now = a[i], b[i].id = i;
	}
	std::sort(b + 1, b + n + 1, cmp);
	long long tmp = m * k;
	for(long long i = 1; i <= tmp; i++) vis[ b[i].id ] = true, cnt += b[i].now;
	printf("%lld\n",cnt);

	cnt = 0;
	for(long long i = 1; i <= n; i++){
		cnt += vis[i];	
		if(cnt == m){
			time++;
			time < k && printf("%lld ",i);
			cnt = 0;
		}
	}
}
