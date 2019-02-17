#include <cstdio>

long long a, b, mod;

inline long long ksm(long long a, long long p){
	long long res = 1;
	while(p){
		if(p & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		p >>= 1;
	}
	return res;
}

int main(){
	scanf("%lld%lld%lld", &a, &b, &mod);
	printf("%lld^%lld mod %lld=%lld" , a, b, mod, ksm(a, b) % mod);
}
