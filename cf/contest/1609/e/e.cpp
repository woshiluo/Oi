/*
 * e.cpp
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

const int N = 1e5 + 1e4;
const int K = 5;
const int INF = 0x3f3f3f3f;

struct Matrix {
	int f[K][K];
	Matrix( const int p = 0 ) {
		memset( f, INF, sizeof(f) );
		if( p == INF ) 
			return ;
		for( int i = 0; i < K; i ++ ) {
			f[i][i] = p;
		}
	}

	Matrix operator* ( const Matrix &_b ) const {
		Matrix res;
		memset( (int*)&res, INF, sizeof(res) );
		for( int i = 0; i < K; i ++ ) {
			for( int j = 0; j < K; j ++ ) {
				for( int k = 0; k < K; k ++ ) {
					chk_Min( res.f[i][j], f[i][k] + _b.f[k][j] );
				}
			}
		}
		return res;
	}
	void operator*= ( const Matrix &_b ) { (*this) = *this * _b; }
} ori, base, mat_a, mat_b, mat_c;

struct SegmentTree {
	int n;
	Matrix tree[ N << 2 ];
	void push_up( int cur ) { tree[cur] = tree[ cur << 1 ] * tree[ cur << 1 | 1 ]; }

	void set( int pos, Matrix &val, int cur, int left, int rig ) {
		if( left == rig ) {
			tree[cur] = val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid ) 
			set( pos, val, cur << 1, left, mid );
		else
			set( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void set( int pos, Matrix &val ) { set( pos, val, 1, 1, n ); }
	
	void build( int cur, int left, int rig ) {
		if( left == rig ) {
			tree[cur] = Matrix();
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		
		push_up(cur);
	}
	void build( int _n ) { n = _n; build( 1, 1, n ); }
} sgt;

// 0 ""
// 1 a
// 2 ab
int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	memset( (int*)&ori, INF, sizeof(ori) );
	mat_a = ori, mat_b = ori; mat_c = ori; base = ori;
	mat_a.f[0][0] = 1; mat_a.f[1][1] = 0; mat_a.f[2][2] = 0;
	mat_b.f[0][0] = 0; mat_b.f[1][1] = 1; mat_b.f[2][2] = 0;
	mat_c.f[0][0] = 0; mat_c.f[1][1] = 0; mat_c.f[2][2] = 1;
	mat_a.f[0][1] = 0;
	mat_b.f[1][2] = 0;
	base.f[0][0] = 0;

	int n, q;
	char str[N];
	n = read<int>(); q = read<int>();
	scanf( "%s", str + 1 );

	sgt.build(n);
	for( int i = 1; i <= n; i ++ ) {
		if( str[i] == 'a' ) 
			sgt.set( i, mat_a );
		if( str[i] == 'b' ) 
			sgt.set( i, mat_b );
		if( str[i] == 'c' ) 
			sgt.set( i, mat_c );
	}
	while( q -- ) {
		int pos; char x[3];
		scanf( "%d%s", &pos, x );
		{
			if( x[0] == 'a' ) 
				sgt.set( pos, mat_a );
			if( x[0] == 'b' ) 
				sgt.set( pos, mat_b );
			if( x[0] == 'c' ) 
				sgt.set( pos, mat_c );
		}
		Matrix res = base * sgt.tree[1];
		printf( "%d\n", Min( res.f[0][0], Min( res.f[0][1], res.f[0][2] ) ) );
	}
}
