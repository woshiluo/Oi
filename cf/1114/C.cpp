#include <cstdio>
#include <cmath>

const long long INF = 1e18 + 1e17;

inline long long Min(long long a, long long b){return a < b? a: b;}

struct node{
	long long now, cnt;	
}pri[(int)(1e6)];

int pcnt;
long long n, b, tmp, cnt, ans = INF;

inline void get_pri(long long b){
	tmp = std::sqrt(b);	
	for(long long i = 2; i <= tmp; i++){
		if(b % i == 0){
			pri[ ++pcnt ] = (node){i, 0};
			while(b % i == 0){
				pri[pcnt].cnt++;
				b/=i;
			}
		}
	}
	if(b != 1) pri[ ++pcnt ] = (node){b, 1};	
}

int main(){
	scanf("%lld%lld", &n, &b);	
	get_pri(b);
	for(int i = 1; i <= pcnt; i++){
		tmp = 1; cnt = 0;
		while(tmp * pri[i].now <= n){
			tmp *= pri[i].now;
			if(tmp < 0 || tmp % pri[i].now != 0) break;
			cnt += n / tmp;
		}		
		ans = Min(ans, cnt/pri[i].cnt);
	}
	printf("%lld\n", ans);
}
