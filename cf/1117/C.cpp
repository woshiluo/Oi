#include <cstdio>

inline long long Aabs(long long a){return a < 0? (0 - a): a;}

const long long N = 1e5 + 1e4;

long long x1, y1, x2, y2, dx, dy, n, tmp, ans, mid;
char str[N];

int main(){
	scanf("%lld%lld", &x1, &y1);	
	scanf("%lld%lld", &x2, &y2);	
	scanf("%lld", &n);
	scanf("%s", str + 1);

	for(long long i = 1; i <= n; i++){
		if(str[i] == 'U') dy++;
		if(str[i] == 'D') dy--;
		if(str[i] == 'L') dx--;
		if(str[i] == 'R') dx++;
	}

	long long left = 0, rig = (int)2e9;
	while(left <= rig){
		mid = (left + rig) >> 1;
		if( Aabs(x1 + dx * mid - x2) + Aabs(y1 + dy * mid - y2) <= n * mid ) rig = mid - 1;
		else left = mid + 1;
	}

	x1 += dx * rig;
	y1 += dy * rig;
	ans = n * rig;
	if( Aabs(x1 - x2) + Aabs(y1 - y2) <= ans){
		printf("%lld", ans);
		return 0;
	}  

	for(long long i = 1; i <= n; i++){
		if(str[i] == 'U') y1++;
		if(str[i] == 'D') y1--;
		if(str[i] == 'L') x1--;
		if(str[i] == 'R') x1++;
		ans++;

		if( Aabs(x1 - x2) + Aabs(y1 - y2) <= ans ){
			printf("%lld", ans);
			return 0;
		}  
	}	
	printf("-1");
}
