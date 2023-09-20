/*
 * biden.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

const int N = 5100;
const int M = 1 << 13;
const int mod = 998244353;

struct ModInt {/*{{{*/
	int cur;
	ModInt( int _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

int n, m; 
int count[N], val[N];

const ModInt G = 3;
struct Poly {
	bool is_dot;
	ModInt a[M];
	Poly() { is_dot = false; }

	void change() {/*{{{*/
		is_dot ^= 1;
		static int r[M];
		for( int i = 0; i < M; i ++ ) {
			r[i] = r[ i >> 1 ] >> 1;
			if( i & 1 ) 
				r[i] |= (M >> 1);
		}
		for( int i = 0; i < M; i ++ ) 
			if( r[i] < i ) 
				std::swap( a[i], a[ r[i] ] );
	}/*}}}*/

	void ntt( bool on ) {/*{{{*/
		if( on != is_dot )
			return ;
		this -> change();

		for( int h = 2; h <= M; h <<= 1 ) {
			int k = ( h >> 1 );
			ModInt wn = pow( G, ( mod - 1 ) / h );
			if( on ) 
				wn = (ModInt)1 / wn;
			for( int i = 0; i < M; i += h ) {
				ModInt w = 1;
				for( int j = 0; j < k; j ++ ) {
					const int cur = i + j, nxt = i + j + k;
					const ModInt u = a[cur],
						v = w * a[nxt];

					a[cur] = u + v;
					a[nxt] = u - v;

					w *= wn;
				}
			}
		}

		if( on ) {
			for( int i = 0; i < M; i ++ ) 
				a[i] /= M;
		}
	}/*}}}*/

	Poly operator* ( Poly &b ) {/*{{{*/
		Poly res;
		this -> ntt(false); b.ntt(false);

		for( int i = 0; i < M; i ++ ) {
			res.a[i] = a[i] * b.a[i];
		}
		res.is_dot = true;

		return res;
	}/*}}}*/

	void output() {
#ifdef DEBUG
		this -> ntt(true);
		for( int i = 0; i < 20; i ++ ) 
			a[i].output( ' ' );
		printf( "\n" );
#endif
	}
};

Poly gen_poly( int cur ) {
	Poly res;
	for( int i = 0; i <= count[cur]; i ++ ) 
		if( i * val[cur] < M )
			res.a[ i * val[cur] ] = 1;
	return res;
}

struct SegmentTree {/*{{{*/
	struct Node { Poly p; } tree[ N << 2 ];
	inline void push_up( int cur ) { tree[cur].p = tree[ cur << 1 ].p * tree[ cur << 1 | 1 ].p; }

	void set( int pos, Poly &p, int cur, int left, int rig ) {
		if( left == rig ) {
			tree[cur].p = p;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid )
			set( pos, p, cur << 1, left, mid );
		if( pos > mid )
			set( pos, p, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void set( int pos, Poly p ) { set( pos, p, 1, 1, n ); }

	Poly query( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur].p;
		}

		Poly lp, rp;
		int mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			lp = query( from, to, cur << 1, left, mid );
		if( to > mid ) 
			rp = query( from, to, cur << 1 | 1, mid + 1, rig );

		if( from <= mid && to > mid ) 
			return lp * rp;
		if( from <= mid ) 
			return lp;
		if( to > mid ) 
			return rp;
		return res;

	}
	Poly* query( int from, int to ) { return query( from, to, 1, 1, n ); }

	void build( int cur = 1, int left = 1, int rig = n ) {
		if( left == rig ) {
			tree[cur].p = gen_poly(left);
			return ;
		}

		const int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
} sgt;/*}}}*/

int main() {
	freopen( "biden.in", "r", stdin );
	freopen( "biden.out", "w", stdout );

	n = read<int>(); m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		val[i] = read<int>();
	}
	sgt.build();
	for( int i = 1; i <= m; i ++ ) {
		int op = read<int>();
		if( op == 1 ) {
			int x, y;
			x = read<int>(); y = read<int>();
			count[x] += y;
			sgt.set( x, gen_poly(x) );
		}
		else if( op == 2 ) {
			int x, y;
			x = read<int>(); y = read<int>();
			count[x] -= y;
			sgt.set( x, gen_poly(x) );
		}
		else if( op == 3 ) {
			int x, y, z;
			x = read<int>(); y = read<int>(); z = read<int>();
			Poly *res = sgt.query( x, y );
			res -> ntt( true );
			ModInt ans = 0;
			for( int j = 1; j <= z; j ++ ) {
				ans += res -> a[j];
			}
			ans.output();
		}
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
