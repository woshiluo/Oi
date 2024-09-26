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

int main() {
}
