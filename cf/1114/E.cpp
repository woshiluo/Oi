#include <cstdio>
#include <algorithm>

int gcd(int a, int b){return b? gcd(b ,a%b): a;}
inline int Min(int a, int b){return a < b? a: b;}
inline int Aabs(int a){return a < 0? (0 - a): a;}

const int N = 1e6 + 1e5;

int n, global_tmp, d, max, chance_cnt = 60;
int a[N];

inline bool has_num(int now){
	printf("> %d\n",now);
	fflush(stdout);
	scanf("%d", &global_tmp);
	chance_cnt--;
	return global_tmp;
}

inline int binary_search_max(int max_limit){
	int left = 0, rig = max_limit, mid, res;
	while(left <= rig){
		mid = (left + rig) >> 1;
		if( has_num(mid) ) left = mid + 1;
		else rig = mid - 1, res = mid;
	}
	return res;
}

int main(){
	scanf("%d", &n);	

	max = binary_search_max(1e9);

	for(int i = 1; i <= n; i++) a[i] = i;
	for(int i = 1; i <= 5; i++) std::random_shuffle(a + 1, a + n + 1);	

	for(int i = 1; i <= Min(n ,chance_cnt); i++){
		printf("? %d\n", a[i]);	
		fflush(stdout);
		scanf("%d", &global_tmp);
		if(global_tmp == max) continue;
		if(d == 0) d = Aabs(max-global_tmp);
		d = gcd(d , Aabs(max-global_tmp));
	}
	fflush(stdout);
	printf("! %d %d\n", max - (n - 1) * d, d);
}
