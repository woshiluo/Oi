/*
 * 1005.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <vector>
#include <algorithm>

typedef const int cint;
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
	for (; isdigit(ch) == 0; ch = getchar())
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

const int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const int N = 1e5 + 1e4;
const int K = 22;
const int INF = 0x3f3f3f3f;

struct SegmentTree {/*{{{*/
	int n;
	ModInt tree[ N << 2 ], lazy[ N << 2 ];
	void push_up( cint cur ) { tree[cur] = tree[ cur << 1 ] + tree[ cur << 1 | 1 ]; }
	void push_down( cint cur ) {
		if( lazy[cur].cur != 1 ) {
			tree[ cur << 1 ] *= lazy[cur];
			tree[ cur << 1 | 1 ] *= lazy[cur];
			lazy[ cur << 1 ] *= lazy[cur];
			lazy[ cur << 1 | 1 ] *= lazy[cur];
			lazy[cur] = 1;
		}
	}
	
	void build( cint cur, cint left, cint rig ) {/*{{{*/
		lazy[cur] = 1;
		if( left == rig ) {
			tree[cur] = 0;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		
		push_up(cur);
	}
	void init( cint _n ) { n = _n; build( 1, 0, _n ); }/*}}}*/

	void add( cint pos, const ModInt val, cint cur, cint left, cint rig ) {/*{{{*/
		if( left == rig && left == pos ) {
			tree[cur] += val;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		push_down(cur);
		if( pos <= mid ) 
			add( pos, val, cur << 1, left, mid );
		if( pos > mid ) 
			add( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void add( cint pos, const ModInt val ) { add( pos, val, 1, 0, n ); }/*}}}*/

	ModInt sum( cint from, cint to, cint cur, cint left, cint rig ) {/*{{{*/
		if( from <= left && rig <= to ) 
			return tree[cur];

		cint mid = ( left + rig ) >> 1;
		push_down(cur);
		ModInt res = 0;
		
		if( from <= mid ) 
			res += sum( from, to, cur << 1, left, mid );
		if( to > mid ) 
			res += sum( from, to, cur << 1 | 1, mid + 1, rig );

		return res;
	}
	ModInt sum( cint from, cint to ) { return sum( from, to, 1, 0, n ); }/*}}}*/

	void mul( cint from, cint to, const ModInt val, cint cur, cint left, cint rig ) {
		if( from <= left && rig <= to ) {
			tree[cur] *= val;
			lazy[cur] *= val;
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		push_down(cur);

		if( from <= mid ) 
			mul( from, to, val, cur << 1, left, mid );
		if( to > mid ) 
			mul( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void mul( cint from, cint to, const ModInt val ) { return mul( from, to, val, 1, 0, n ); }
} sgt;/*}}}*/

struct Skill { int left, rig; };

int log_2[N];
int a[N], b[N];

int stl[N][K], str[N][K];

int full_pow( cint cur ) { return 1 << cur; } 

int main() {
#ifdef woshiluo
	freopen( "1005.in", "r", stdin );
	freopen( "1005.out", "w", stdout );
#endif
	log_2[1] = 0;
	for( int i = 2; i < N; i ++ ) {
		log_2[i] = log_2[ i >> 1 ] + 1;
	}
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			b[i] = read<int>();
		}

		memset( stl, INF, sizeof(stl) );
		memset( str, INF, sizeof(str) );

		for( int i = 2; i <= n; i ++ ) 
			stl[i][0] = a[i] - b[ i - 1 ];
		for( int i = 1; i < n; i ++ ) 
			str[i][0] = a[i] - b[ i + 1 ];

		for( int k = 1; k < K; k ++ ) {
			for( int i = 2; i <= n; i ++ ) {
				cint nxt = i + full_pow( k - 1 );
				if( nxt + full_pow( k - 1 ) - 1 <= n )
					stl[i][k] = Min( stl[i][ k - 1 ], stl[nxt][ k - 1 ] );
			}
		}
		for( int k = 1; k < K; k ++ ) {
			for( int i = 1; i < n; i ++ ) {
				cint nxt = i + full_pow( k - 1 );
				if( nxt + full_pow( k - 1 ) - 1 < n )
					str[i][k] = Min( str[i][ k - 1 ], str[nxt][ k - 1 ] );
			}
		}

		auto query_st = [] ( int st[N][K], cint left, cint rig ) {
			cint len = ( rig - left + 1 );
			cint d = log_2[len];
			return Min( st[left][d], st[ rig - full_pow(d) + 1 ][d] );
		};

		auto query_l = [&] ( cint st, cint val ) {
			int left = 1, rig = st - 1, res = st;
			while( left <= rig ) {
				cint mid = ( left + rig ) >> 1;
				if( query_st( stl, mid + 1, st ) >= val ) {
					res = mid;
					rig = mid - 1;
				}
				else
					left = mid + 1;
			}
			return res;
		};

		auto query_r = [&] ( cint st, cint val ) {
			int left = st + 1, rig = n, res = st;
			while( left <= rig ) {
				cint mid = ( left + rig ) >> 1;
				if( query_st( str, st, mid - 1 ) >= val ) {
					res = mid;
					left = mid + 1;
				}
				else
					rig = mid - 1;
			}
			return res;
		};

		std::vector<Skill> skills;
		for( int i = 1; i <= m; i ++ ) {
			cint x = read<int>();
			cint l = read<int>();
			cint r = read<int>();
			skills.push_back( { query_l( x, l ), query_r( x, r ) } );
		}

		std::sort( skills.begin(), skills.end(), []( const Skill &_a, const Skill &_b ) { 
			if( _a.left == _b.left ) 
				return _a.rig < _b.rig; 
			return _a.left < _b.left;
		});

		sgt.init(n);
		sgt.add( 0, 1 );

		for( auto &skill: skills ) {
			sgt.add( skill.rig, sgt.sum( skill.left - 1, skill.rig ) );
			if( skill.rig + 1 <= n )
				sgt.mul( skill.rig + 1, n, 2 );
		}

		( sgt.sum( n, n ) ).output();
	}
}
