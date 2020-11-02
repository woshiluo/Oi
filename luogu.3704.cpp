#include <cstdio>

#include <cstring>

const int N = 1e6 + 1e5;
const int mod = 1e9 + 7;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline void add_eq( int &a, int b ) { a = add( a, b ); }
inline void mul_eq( int &a, int b ) { a = mul( a, b ); }

int T;
int n, m, pcnt;
int f[N], pri[N];
bool is_prime[N];

void pre() {
	f[0] = f[1] = 1;
	for( int i = 2; i < N; i ++ ) { 
		f[i] = add( f[ i - 1 ], f[ i - 2 ] );
	}

	is_prime[1] = false;
	for( int i = 2; i < N; i ++ ) {
		if( is_prime[i] ) {
			pri[ ++ pcnt ] = i;
			mu[i] = -1;
			is_prime[i] = true;
		}
		for( int j = 1; j <= pcnt; j ++ ) {
			if( 1LL * pri[j] * i >= N ) 
				break;
			int nxt = 1LL * pri[j] * i;
			is_prime[nxt] = false;
			if( i % pri[j] == 0 ) {
				mu[nxt] = 0;
				break;
			}
			else 
				mu[nxt] = -mu[i];
		}
	}
}

int main() {
	scanf( "%d", &T );
	pre();
	while( T -- ) {
		scanf( "%d%d", &n, &m );
	}
}
