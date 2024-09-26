#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>

#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

constexpr bool is_number( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T>
T read() {
	T res = 0, k = 1;
	char x = getchar();
	for( ; !is_number(x); x = getchar() )
		if( x == '-' ) 
			k = -1;
	for( ; is_number(x); x = getchar() )
		res = res * 10 + ( x - '0' );
	return res * k;
}
template <class T>
constexpr T Min( const T &a, const T &b ) { return a < b? a: b; }
template <class T>
constexpr T Max( const T &a, const T &b ) { return a > b? a: b; }
template <class T>
void chk_Min( T &a, const T &b ) { if( a > b ) a = b; }
template <class T>
void chk_Max( T &a, const T &b ) { if( a < b ) a = b; }
template <class T>
T pow( T a, int p ) {
	T res = 1;
	while(p) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 2048;

int b[N][N];

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif
	ci32 n = read<i32>(); 
	std::vector<i32> a(n + 1);
	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<i32>();
	std::vector<i32> sorted_a = a;
	std::sort( sorted_a.begin() + 1, sorted_a.end() );

	const auto check = [&]( ci32 mid ) {
		std::vector<i32> hashed_a( n + 1, 0 );
		for( int i = 1; i <= n; i ++ ) {
			hashed_a[i] = hashed_a[ i - 1 ] + ( a[i] <= sorted_a[mid] );
		}
		for( int i = 1; i <= n; i ++ ) {
			for( int j = i; j <= n; j ++ ) {
				ci32 cnt_1 = hashed_a[j] - hashed_a[ i - 1 ];
				ci32 len = j - i + 1;
				b[i][j] = ( cnt_1 >= len - cnt_1 );
			}
		}

		for( int j = 1; j <= n; j ++ ) {
			for( int i = j - 1; i >= 1; i -- ) {
				b[i][j] += b[ i + 1 ][j];
			}
			for( int i = j - 1; i >= 1; i -- ) {
				b[i][j] += b[i][ j - 1 ];
			}
		}

		i32 cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = i; j <= n; j ++ ) {
				ci32 len = 1LL * ( ( j - i + 1 ) + 1 ) * ( j - i + 1 ) / 2LL;
				cnt += ( b[i][j] >= len - b[i][j] );
			}
		}
		return cnt >= ( 1LL * ( 1 + n ) * n / 2LL - cnt );
	};

	i32 left = 1, rig = n, res = 1;
	while( left <= rig ) {
		ci32 mid = ( left + rig ) >> 1;
		if( check(mid) ) {
			res = mid;
			rig = mid - 1;
		}
		else 
			left = mid + 1;
	}

	printf( "%d\n", sorted_a[res] );
}
