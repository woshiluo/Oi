#include <cstdio>

#include <map>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 1e5 + 1e4;
const int mod = 1e9 + 7;

int n, ans = 0, char_cnt;
char S[N];
int pool[512], hash_mp[512];
bool vis[512];

struct sum_node {
	int sum[128];
	bool operator< ( const sum_node &b ) const {
		for( int i = 1; i <= char_cnt; i ++ ) {
			if( sum[i] != b.sum[i] )
				return sum[i] < b.sum[i];
		}
		return false;
	}
	int& operator[] ( int index ) { return sum[index]; }
}cur;

std::map<sum_node, int> mp;

inline int add( int a, int b) { return ( a + b ) % mod; }
inline int hash( char a ) { return hash_mp[a]; }

int main() {
#ifdef woshiluo
	freopen( "luogu.6273.in", "r", stdin );
	freopen( "luogu.6273.out", "w", stdout );
#endif
	scanf( "%d", &n );
	scanf( "%s", S + 1 );
	for( int i = 1; i <= n; i ++ ) {
		if( vis[ S[i] ] == false ) {
			char_cnt ++;
			hash_mp[ S[i] ] = char_cnt;
			vis[ S[i] ] = true;
		}
	}

	mp[cur] = 1;
	for( int i = 1; i <= n; i ++ ) {
		int cur_str = hash( S[i] );
		cur[ cur_str ] ++;

		int min = n + 10;
		for( int i = 1; i <= char_cnt; i ++ ) {
			if( min > cur[i] )
				min = cur[i];
		}
		for( int i = 1; i <= char_cnt; i ++ )
			cur[i] -= min;

		int eq_cnt;
		if( mp.count(cur) != 0 )
			eq_cnt = mp[cur];
		else 
			eq_cnt = 0;
		ans = add( ans, eq_cnt );
		mp[cur] = eq_cnt + 1;
	}
	printf( "%d\n", ans );
}
