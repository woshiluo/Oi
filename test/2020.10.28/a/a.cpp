#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 1e7 + 1e2;
const int M = ( N / 10 );

long long sum[N];

int max_pri[N], pri[M], pcnt;
bool is_prime[N];

void pre( int n ) {
	memset( is_prime, true, sizeof(is_prime) );
	is_prime[0] = is_prime[1] = false;
	sum[1] = 1;
	for( int i = 2; i <= n; i ++ ) {
		if( is_prime[i] ) {
			pcnt ++;
			max_pri[i] = i;
			pri[pcnt] = i;
			sum[i] = i;
		}
		for( int j = 1; j <= pcnt; j ++ ) {
			if( 1LL * i * pri[j] > n ) 
				break;
			int nxt = i * pri[j];
			is_prime[nxt] = false;
			if( i % pri[j] == 0 ) {
				max_pri[nxt] = max_pri[i];
				if( max_pri[i] != pri[j] ) 
					sum[nxt] = 1;
				else 
					sum[nxt] = sum[i];
				break;
			}
			else {
				max_pri[nxt] = max_pri[i];
				sum[nxt] = 1;
			}
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		sum[i] += sum[ i - 1 ];
	}
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r",  stdin );
	freopen( "a.out", "w", stdout );
#endif
	int a, b;
	scanf( "%d%d", &a, &b );
	pre(b);
	printf( "%lld\n", sum[b] - sum[ a - 1 ] );
}
