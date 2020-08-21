#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a > b? a: b; }

const int N = 3e5 + 1e4;
const long long INF = ( 1LL << 62LL );

int n;
char S[N];
int val[N];
int min[N], max[N], size[N], id[N];
long long cnt[N], res[N], ans[N];

struct set {
	int fa[N];
	inline void init( int n ) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	int get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return cur;
		return fa[cur] = get_fa( fa[cur] );
	}
	int &operator[] ( int cur ) { return fa[cur]; }
} fa;

void merge( int x, int y, int len ) {
	x = fa.get_fa(x); y = fa.get_fa(y);
	fa[y] = x;
	cnt[len] += 1LL * size[x] * size[y];
	size[x] += size[y];
	res[x] = Max( Max( res[x], res[y] ), 
			Max( Max( 1LL * max[x] * max[y], 1LL * min[x] * min[y] ), 
				Max( 1LL * max[x] * min[y], 1LL * min[x] * max[y] ) ) );
	min[x] = Min( min[x], min[y] );
	max[x] = Max( max[x], max[y] );
	ans[len] = Max( ans[len], res[x] );
}

struct suffix_array {
	int len, Max_char;
	int height[N], sa[N], rk[N], tp[N];
	char *str;
	// Init
	void sort() {
		static int rk_cnt[N];
		memset( rk_cnt, 0, sizeof(rk_cnt) );
		for( int i = 1; i <= len; i ++ ) 
			rk_cnt[ rk[i] ] ++;
		for( int i = 1; i <= Max_char; i ++ ) 
			rk_cnt[i] += rk_cnt[ i - 1 ];
		for( int i = len; i >= 1; i --  )
			sa[ rk_cnt[ rk[ tp[i] ] ] -- ] = tp[i];
	}
	void init( char *S, int _len ) {
		str = S;
		len = _len;
		Max_char = 'z' - 'a' + 2;
		for( int i = 1; i <= len; i ++ ) {
			rk[i] = str[i] - 'a' + 1;
			tp[i] = i;
		}
		sort();

		for( int k = 1, tmp_cnt = 0; tmp_cnt < len; k <<= 1, Max_char = tmp_cnt ) {
			tmp_cnt = 0;
			for( int i = 1; i <= k; i ++ ) {
				tp[ ++ tmp_cnt ] = len - k + i;
			}
			for( int i = 1; i <= len; i ++ ) {
				if( sa[i] > k ) 
					tp[ ++ tmp_cnt ] = sa[i] - k;
			}
			sort();

			memcpy( tp, rk, sizeof(rk) );
			rk[ sa[1] ] = tmp_cnt = 1;
			for( int i = 2; i <= len; i ++ ) {
				if( tp[ sa[i] ] == tp[ sa[ i - 1 ] ] && tp[ sa[i] + k ] == tp[ sa[ i - 1 ] + k ] )
					rk[ sa[i] ] = tmp_cnt;
				else {
					tmp_cnt ++;
					rk[ sa[i] ] = tmp_cnt;
				}
			}
		}
#ifdef woshiluo
		for( int i = 1; i <= n; i ++ ) printf( "%d ", sa[i] );
		printf( "\n" );
#endif
	}
	void get_height() {
		for( int i = 1, k = 0; i <= len; i ++ ) {
			if( k ) 
				k --;
			while( str[ i + k ] == str[ sa[ rk[i] - 1 ] + k ] ) 
				k ++;
			height[ rk[i] ] = k;
		}
	}
} sa;

bool cmp( int a, int b ) { return sa.height[a] > sa.height[b]; }

int main() {
#ifdef woshiluo
	freopen( "loj.2133.in", "r", stdin );
	freopen( "loj.2133.out", "w", stdout );
#endif
	scanf( "%d", &n );
	scanf( "%s", S + 1 );

	sa.init( S, n );
	sa.get_height();

	fa.init(n);
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &val[i] );
		size[i] = 1; min[i] = max[i] = val[i]; res[i] = ans[i] = -INF;
		id[i] = i;
	}
	ans[ n + 1 ] = -INF;

	std::sort( id + 2, id + n + 1, cmp );

	for( int i = 2; i <= n; i ++ ) {
		merge( sa.sa[ id[i] ], sa.sa[ id[i] - 1 ], sa.height[ id[i] ] );
	}
	
	for( int i = n; i >= 0; i --  ) 
		cnt[i] += cnt[ i + 1 ];
	for( int i = n; i >= 0; i -- )
		ans[i] = Max( ans[i], ans[ i + 1 ] );
	for( int i = 0; i < n; i ++ ) {
		printf( "%lld %lld\n", cnt[i], cnt[i] == 0? 0: ans[i] );
	}
}
