#include <cstdio>

#include <vector>
#include <algorithm>

const int N = 40;
const int BIT = 22;

int n;
long long m, ans;
long long a[N], sum[N];

inline int full_bit( int k ) { return 1 << k; }
inline int has( int k, int i ) { return ( k >> ( i - 1 ) ) & 1; }

int main() {
	scanf( "%d%lld", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i] );
	}
	std::sort( a + 1, a + n + 1 );
	int fir_cnt = n / 2; int sec_cnt = ( n / 2 ) + ( n & 1 );
	std::vector<long long> fir, sec;
	for( int k = 0; k < full_bit(fir_cnt); k ++ ) {
		long long res = 0;
		for( int i = 1; i <= fir_cnt; i ++ ) {
			if( has( k, i ) ) {
				res += a[i];
			}
		}
		if( res <= m ) {
			fir.push_back(res);
		}
	}
	for( int k = 0; k < full_bit(sec_cnt); k ++ ) {
		long long res = 0;
		for( int i = 1; i <= sec_cnt; i ++ ) {
			if( has( k, i ) ) {
				res += a[i + fir_cnt];
			}
		}
		if( res <= m ) {
			sec.push_back(res);
		}
	}
	std::sort( fir.begin(), fir.end() );
	std::sort( sec.begin(), sec.end() );
	int fir_size = fir.size(), sec_size = sec.size();
	int p1 = 0, p2 = sec_size - 1;
	long long ans = 0;
	while( p1 < fir_size && p2 >= 0 ) {
		while( fir[p1] + sec[p2] > m && p2 >= 0 ) {
			p2 --;
		}
		if( p2 < 0 ) {
			break;
		}
		ans += 1LL * ( p2 + 1 );
		p1 ++;
	}
	printf( "%lld\n", ans );
}
