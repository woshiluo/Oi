#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>

#include <map>
#include <string>
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


const int N = 1e5 + 1e4;
const int K = 30;


int cnt[K];
bool status[N][K];

int main() {
#ifdef woshiluo
	freopen( "m.in", "r", stdin );
	freopen( "m.out", "w", stdout );
#endif
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::map<std::string, i32> mp;
		memset( cnt, 0, sizeof(cnt) );
		memset( status, 0, sizeof(status[0]) * ( n + 1 ) );
		for( int i = 1; i <= n; i ++ ) {
			static char name[16], id[16], raw_status[16];
			scanf( "%s%s%s", name, id, raw_status );
			std::string name_cpp = name;
			if( !mp.count( name_cpp ) ) {
				ci32 nid = mp.size();
				mp[ name_cpp ] = nid;
			}
			ci32 cid = mp[name_cpp];
			if( raw_status[0] == 'a' && status[cid][ id[0] - 'A' ] == false ) {
				cnt[ id[0] - 'A' ] ++;
				status[cid][ id[0] - 'A' ] = 1;
			}
		}
		int res_id = -1;
		for( int i = 0; i < 26; i ++ ) {
			if( cnt[i] ) {
				if( res_id == -1 || cnt[ res_id ] < cnt[i] ) 
					res_id = i;
			}
		}
		printf( "%c\n", res_id + 'A' );
	}
}
