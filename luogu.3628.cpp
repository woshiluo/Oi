#include <cstdio>

long long square(long long x){ return x * x; }

const int N = 1e6 + 1e5;

int n, head, tail;
long long a, b, c, f[N], sum[N];
int q[N];

inline double slope(int x, int y){
	return 1.0 * (f[x] + a * square(sum[x]) - b * sum[x] - f[y] - a * square(sum[y]) + b * sum[y]) / (sum[x] - sum[y]);
}

int main(){
	scanf("%d%lld%lld%lld", &n, &a, &b, &c);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &sum[i]);	
		sum[i] += sum[i - 1];
	}
	for(int i = 1; i <= n; i++){
		while(head < tail && slope(q[head + 1], q[head]) > (a << 1) * sum[i])
			head++;
		f[i] = f[ q[head] ] + a * square(sum[i] - sum[ q[head] ]) + b * (sum[i] - sum[ q[head] ]) + c;
		while(head < tail && slope(q[tail], q[tail - 1]) < slope(i, q[tail]))
			tail--;
		q[ ++tail ] = i;
	}
	printf("%lld", f[n]);
}
