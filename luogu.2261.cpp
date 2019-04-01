#include <cstdio>

long long n, k, ans;

long long dc(long long left, long long rig){
	if(left == rig) 
		return left;
	return ( (left + rig) * (rig - left + 1) )>> 1;
}

int main(){
	scanf("%lld%lld", &n, &k);
	for(long long left = 1LL, rig; left <= n; left = rig + 1LL){
		rig = n / (n / left);	
		ans += dc(0LL, (rig - left + 1LL) - 1LL);
	} 
	
	ans += (n - k < 0LL? 0LL: n - k) * k;
	printf("%lld", ans);
}
