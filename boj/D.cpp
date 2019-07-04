#include<cstdio>
#include<cstring>

inline int Aabs(int now){return now < 0? (0 - now): now;}

const int p=998244353,N=1e7+7;

int t, a, b;
long long ans, q;
long long ny[N], f[N];

long long ksm(long long a,int b){
	long long res=1;
	while(b){
		if(b&1) res = res * a % p;
		a = a * a %p;
		b >>= 1;
	}
	return res;
}

long long C(int x,int y){
	if(x < 0||y < 0||x < y)return 0;
	return f[x]*ny[y]%p*ny[x-y]%p;
}

long long solve(int now){ return C(t, now) * C(t - now, a + now) % p * C(t - a - now - now,( (t - a -  b) >> 1) - now)%p; } 

int main(){
	scanf("%d%d%d", &a, &b, &t);
	a=Aabs(a); b=Aabs(b);
	if(((t-a-b)&1)||t<a+b){
		printf("0");
		return 0;
	}
	f[0]=1;ny[0]=1;
	for(int i=1;i<=t;i++) f[i]=f[i-1]*i%p;
	q = ksm(ksm(4,t),p-2);
	ny[t] = ksm(f[t],p-2);
	for(int i=t-1;i>=1;i--) ny[i]=ny[i+1]*(i+1)%p;
	for(int i=0;i<=t;i++)
		ans = ( ans + solve(i) ) % p;
	printf("%lld\n",ans*q%p);
	return 0;
}
