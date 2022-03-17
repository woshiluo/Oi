/*
 * e.cpp
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

#include <random>
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

const int N = 3e5 + 1e4;

int mod = 10;

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

std::random_device seed;
std::mt19937 rnd(seed());

ModInt a[N], b[N], c[N];
ModInt g1[N], g2[N], sum1[N], sum2[N];

struct Fib {
	ModInt f1, f2;

	Fib( ModInt _a = 0, ModInt _b = 0 ) { f1 = _a; f2 = _b; }

	Fib operator+ ( const Fib &_b ) const { return (Fib){ f1 + _b.f1, f2 + _b.f2 }; }
	void operator+= ( const Fib &_b ) { f1 += _b.f1; f2 += _b.f2; }

	void set_empty() { f1 = 0; f2 = 0; }
	bool has_value() const { return !(f1.cur == 0 && f2.cur == 0); }
	ModInt get( int k ) { return f1 * g1[k] + f2 * g2[k]; }
	ModInt sum( int k ) { return f1 * sum1[k] + f2 * sum2[k]; }
};

void init( int n ) {
	g1[1] = 1; g2[2] = 1;
	for( int i = 3; i <= n; i ++ ) {
		g1[i] = g1[ i - 1 ] + g1[ i - 2 ];
		g2[i] = g2[ i - 1 ] + g2[ i - 2 ];
	}
	for( int i = 1; i <= n; i ++ ) {
		sum1[i] = sum1[ i - 1 ] + g1[i];
		sum2[i] = sum2[ i - 1 ] + g2[i];
	}
}

int len( int left, int rig ) { return rig - left + 1; }

struct SegmentTree {
	struct Node {
		ModInt sum;
		Fib lazy;
	} tree[ N << 2 ];
	int n;

	void push_up( int cur ) { tree[cur].sum = tree[ cur << 1 ].sum + tree[ cur << 1 | 1 ].sum; }
	void push_down( int cur, int left, int rig ) {
		if( tree[cur].lazy.has_value() ) {
			int mid = ( left + rig ) >> 1;
			Fib p1 = tree[cur].lazy;
			Fib p2 = (Fib) { p1.get(mid + 1), p1.get(mid + 2) };

			tree[ cur << 1 ].sum += p1.sum( len( left, mid ) );
			tree[ cur << 1 | 1 ].sum += p2.sum( len( mid + 1, rig ) );
			tree[ cur << 1 ].lazy += p1;
			tree[ cur << 1 | 1 ].lazy += p2;
			tree[cur].lazy.set_empty();
		}
	}

	void build( int cur, int left, int rig, int val[] ) {
		tree[cur].sum = 0;
		tree[cur].lazy.set_empty();
		if( left == rig ) {
			tree[cur].sum = val[left];
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid, val );
		build( cur << 1 | 1, mid + 1, rig, val );

		push_up(cur);
	}
	void init( int _n, int val[] ) { n = _n; build( 1, 1, n, val ); }

	void add( int from, int to, Fib val, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].sum += val.sum( len( left, rig ) );
			tree[cur].lazy += val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		push_down( cur, left, rig );

		if( from <= mid ) {
			Fib p1 = (Fib) { val.f1, val.f2 };
			add( from, to, p1, cur << 1, left, mid );
		}
		if( to > mid ) {
			Fib p2;
			if( from <= mid + 1 ) 
				p2 = (Fib) { val.get( len( from, mid + 1 ) ), val.get( len( from, mid + 2 ) ) };
			else
				p2 = (Fib) { val.f1, val.f2 };
			add( from, to, p2, cur << 1 | 1, mid + 1, rig );
		}

		push_up(cur);
	} 
	void add( int from, int to, Fib val ) { add( from, to, val, 1, 1, n ); }

	ModInt sum( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to )
			return tree[cur].sum;

		int mid = ( left + rig ) >> 1;
		push_down( cur, left, rig );
		ModInt res = 0;
		if( from <= mid ) 
			res += sum( from, to, cur << 1, left, mid );
		if( to > mid ) 
			res += sum( from, to, cur << 1 | 1, mid + 1, rig );
		push_up(cur);

		return res;
	}
	ModInt sum( int from, int to ) { return sum( from, to, 1, 1, n ); }
};

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.ans", "w", stdout );
#endif
	int n, q; SegmentTree sgt;
	n = read<int>(); q = read<int>(); mod = read<int>();
	init( n + 100 );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		c[i] = a[i] - b[i];
	}

//	sgt.init( n, c );
	while( q -- ) {
		char op[3];
		scanf( "%s", op );
		int x, y; 
		x = read<int>(); y = read<int>();
		if( op[0] == 'A' ) {
			for( int i = x, p = 1; i <= y; i ++, p ++ ) 
				c[i] += g1[p] + g2[p];
		}
		else {
			for( int i = x, p = 1; i <= y; i ++, p ++ ) 
				c[i] -= g1[p] + g2[p];
		}

		for( int i = 1; i <= n; i ++ ) {
			c[i].output( ' ' );
		}
		printf( "\n" );

		bool flag = true;
		for( int i = 1; i <= n; i ++ ) 
			if( c[i].cur != 0 ) 
				flag = false;
		printf( "%s\n", flag? "YES": "NO" );
	}
}
