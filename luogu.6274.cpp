#include <cstdio>

#include <map>
#include <vector>

struct node {/*{{{*/
	unsigned long long x, y;
	inline bool operator <( const node &b ) const { 
		if( x == b.x ) 
			return y < b.y;
		return x < b.x;
	}
	inline int get_val( int cur ) {
		if( cur < 32 ) 
			return ( ( y >> ( cur << 1 ) ) & 3 );
		else
			return ( ( x >> ( ( cur - 32 ) << 1 ) ) & 3 );
	}
	inline void add_val( int cur, unsigned long long val = 1 ) {
		if( cur < 32 ) {
			y += ( 1ull << ( cur << 1 ) ) * val;
		}
		else {
			x += ( 1ull << ( ( cur - 32 ) << 1 ) ) * val;
		}
	}
};/*}}}*/

const int N = 10;
const int mod = 1e9 + 7;

inline int pow( int a ) { return 1 << a; }
inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }

long long n;
int pri_cnt;
int pri[N], pri_pow[N], cnt[64];
std::vector<int> conn[64];
std::map<node,int> mp;

int dfs( node cur ) {
	if( mp.count(cur) != 0 ) 
		return mp[cur];
	int res = 1;
	for( int i = 1; i < pow(pri_cnt); i ++ ) {
		int bit = cur.get_val(i);
		if( bit <= 1 ) {
			node tmp = cur;
			int size = conn[i].size();
			for( int j = 0; j < size; j ++ ) {
				if( tmp.get_val(conn[i][j]) < 2 ) 
					tmp.add_val(conn[i][j]);
			}
			res = add( res, mul( dfs(tmp), cnt[i] ) );
		}
	}
	return mp[cur] = res;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.6274.in", "r", stdin );
	freopen( "luogu.6274.out", "w", stdout );
#endif
	scanf( "%lld", &n );
	for( int i = 2; 1LL * i * i <= n; i ++ ){
		if( n % i == 0 ) {
			pri_cnt ++;
			while( n % i == 0 ) {
				n /= i;
				pri_pow[ pri_cnt ] ++;
			}
		}
	}
	if( n > 1 ) 
		pri_pow[ ++ pri_cnt ] = 1;
	for( int i = 0; i < pow(pri_cnt); i ++ ) {
		cnt[i] = 1;
		for( int j = 1; j <= pri_cnt; j ++ ) {
			if( ( i >> ( j - 1 ) ) & 1 ) 
				cnt[i] *= pri_pow[j];
		}
	}
	for( int i = 0; i < pow(pri_cnt); i ++ ) {
		for( int j = 0; j < pow(pri_cnt); j ++ ) {
			if( i & j ) 
				conn[i].push_back(j);
		}
	}

	printf( "%d", ( dfs( (node){0, 0} ) - 1 + mod ) % mod );
}
