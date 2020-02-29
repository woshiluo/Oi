#include <cstdio>

inline int Min( int a, int b ) { return a < b? a: b; }
inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 50005;
const int M = 1005;
const int INF = 0x3f3f3f3f;
const int mod = 10007;

inline short add( short a, short b ) { return ( ( ( a + b ) % mod ) + mod ) % mod; }

int n, m, left, rig, res;
int a[N], sum[N], la[N];

short f_sum[M][N];

inline short query_sum( int level, int left, int rig ) { return add( f_sum[level][rig], - f_sum[level][ left -  1 ] ); }

bool check( int val ) {
	int cur = 0, less = m;
	for( int i = 1; i <= n; i ++ ) {
		cur += a[i];
		if( a[i] > val ) 
			return false;
		if( cur > val ) {
			cur = a[i], less --;
			if( less < 0 ) 
				return false;
		}
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.2511.in", "r", stdin );
	freopen( "luogu.2511.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		sum[i] = sum[ i - 1 ] + a[i];
	}
	rig = sum[n];
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( check(mid) ) {
			res = mid;
			rig = mid - 1;
		}
		else 
			left = mid + 1;
	}

	int p = 1;
	for( int i = 1; i <= n; i ++ ) {
		while( sum[i] - sum[ p - 1 ] > res && p <= n )
			p ++;
		la[i] = p;
	}

	f_sum[ m + 1 ][1] += 1;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = m + 1; j >= 0; j -- ) {
			short tmp = query_sum( j + 1, la[i], i );
			f_sum[j][ i + 1 ] = add( f_sum[j][i], tmp );
		}
	}
	
	short ans = 0;
	for( int i = 0; i <= m; i ++ ) {
		ans = add( ans, query_sum( i, n + 1, n + 1 ) );
	}

	printf( "%d %d", res, ans );
}
