/*
 * loj.2083.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 31000;
const int K = 18;
const int INF = 0x3f3f3f3f;

inline int full_pow( int k ) { return 1 << k; }

int log_2[N];

struct SuffixArray {
	int n;
	char *str;
	
	 // Gen SA
	int sa[N], rk[N], tp[N];
	int height[N], st[N][K];
	SuffixArray() {
		memset( sa, 0, sizeof(sa) );
		memset( rk, 0, sizeof(rk) );
		memset( tp, 0, sizeof(tp) );
	}

	void sort( int charset_size = 30 ) {
		static int pool[N];
		memset( pool, 0, sizeof(pool) );
		for( int i = 0; i < n; i ++ ) 
			pool[ rk[i] ] ++;
		for( int i = 1; i <= charset_size; i ++ ) 
			pool[i] += pool[ i - 1 ];
		for( int i = n - 1; i >= 0; i -- ) {
			sa[ pool[ rk[ tp[i] ] ] ] = tp[i];
			pool[ rk[ tp[i] ] ] --;
		}
	}

	void gen_sa() {
		for( int i = 0; i < n; i ++ ) {
			rk[i] = str[i] - 'a' + 1;
			tp[i] = i;
		}
		sort();

		for( int k = 1, charset_size = 0; charset_size < n; k <<= 1 ) {
			if( charset_size == 0 )
				charset_size = 30;
			{
				int cnt = 0;
				for( int i = 0; i < k; i ++ ) 
					tp[ cnt ++ ] = n - i - 1;
				for( int i = 1; i <= n; i ++ ) {
					if( sa[i] >= k ) 
						tp[ cnt ++ ] = sa[i] - k;
				}
			}

			sort( charset_size );

			for( int i = 0; i < n; i ++ ) 
				tp[i] = rk[i];

			rk[ sa[1] ] = 1; charset_size = 1;
			for( int i = 2; i <= n; i ++) {
				if( !( tp[ sa[i] ] == tp[ sa[ i - 1 ] ] &&
						tp[ sa[i] + k ] == tp[ sa[ i - 1 ] + k ] ) )
					charset_size ++;
				rk[ sa[i] ] = charset_size;
			}
		}
	}

	void gen_height() {
		memset( height, 0, sizeof(height) );
		for( int i = 0, k = 0; i < n; i ++ ) {
			if( k ) 
				k --;
			while( rk[i] != 1 && str[ i + k ] == str[ sa[ rk[i] - 1 ] + k ] ) 
				k ++;
			height[ rk[i] ] = k;
		}
	}
	
	void gen_st() {
		memset( st, INF, sizeof(st) );
		for( int i = 1; i <= n; i ++ ) 
			st[i][0] = height[i];
		for( int k = 1; k < K; k ++ ) {
			for( int i = 1; i <= n; i ++ ) {
				if( i + full_pow( k - 1 ) <= n ) 
					st[i][k] = Min( st[i][ k - 1 ], st[ i + full_pow( k - 1 ) ][ k - 1 ] );
			}
		}
	}

	int lcp( int left, int rig ) const {
		if( left < 0 )
			return 0;
		left = rk[left]; rig = rk[rig];
		if( left > rig ) 
			std::swap( left, rig );
		left ++;
		int k = log_2[ rig - left + 1 ];

		if( left > rig ) 
			return 0;
		
		return Min( st[left][k], st[ rig - full_pow(k) + 1 ][k] );
	}

	void build( char *_str, int len ) {
		str = _str;
		n = len;
		gen_sa(); gen_height(); gen_st();
	}
};

int main() {
#ifdef woshiluo
	freopen( "loj.2083.in", "r", stdin );
	freopen( "loj.2083.out", "w", stdout );
#endif
	log_2[1] = 0;
	for( int i = 2; i < N; i ++ ) 
		log_2[i] = log_2[ i >> 1 ] + 1;

	int T = read<int>();
	while( T -- ) {
		char str[N];
		int pre_sum[N], suf_sum[N];
		memset( pre_sum, 0, sizeof(pre_sum) );
		memset( suf_sum, 0, sizeof(suf_sum) );

		scanf( "%s", str );
		int len = strlen(str);
		SuffixArray pre, suf;
		suf.build( str, len );
		std::reverse( str, str + len );
		pre.build( str, len );

		auto reverse_id = [len]( int cur ) { return len - cur - 1; };
		auto lcp = [suf]( int left, int rig ) { return suf.lcp( left, rig ); };
		auto lcs = [pre, reverse_id]( int left, int rig ) { return pre.lcp( reverse_id(left), reverse_id(rig) ); };

		for( int i = 1; i <= len / 2; i ++ ) {
			for( int st = i - 1, ed = i + i - 1; ed < len; st += i, ed += i ) {
				int lt = Min( (int)lcp( st, ed ), i );
				int rt = Min( (int)lcs( st - 1, ed - 1 ), i - 1 );

				int t = lt + rt - i + 1;
				if( lt + rt >= i ) {
					suf_sum[ st - rt ] ++; suf_sum[ st - rt + t ] --;
					pre_sum[ ed + lt - t ] ++; pre_sum[ ed + lt ] --;
				}
			}
		}

		for( int i = 1; i < len; i ++ ) {
			pre_sum[i] += pre_sum[ i - 1 ];
			suf_sum[i] += suf_sum[ i - 1 ];
		}

		long long res = 0;
		for( int i = 1; i < len; i ++ ) {
			res += 1LL * pre_sum[ i - 1 ] * suf_sum[i];
		}

		printf( "%lld\n", res );
	}
}
