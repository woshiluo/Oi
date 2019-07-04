#include <cstdio>
#include <algorithm>

inline long long Min(long long a, long long b) {return a < b? a: b;}
inline double Max(double a, double b) {return a > b? a: b;}

const int N = 1e5 + 1e4;

int n, k, m;
double ans;
int a[N];
long long sum[N];

int main(){
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) 
		sum[i] = sum[i - 1] + (long long) a[i]; 
	int	tmp = Min(n - 1, m);
	for(int i = 1; i <= tmp + 1; i++) 
		ans = Max(ans, (double)(sum[n] - sum[ i - 1 ] + Min( m * 1LL- i * 1LL + 1LL , (n * 1LL - i * 1LL+ 1LL) * k * 1LL)) / (double)(n - i + 1LL)); 
	printf("%.9lf\n", ans);
}
