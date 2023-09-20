/*
 * 1004.cpp
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

template <class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }

const int N = 1e3 + 1e2;
const double eps = 1e-6;

struct Func {
	int left, rig;
	double k, b;
	double f( cint cur ) {
		return k * cur + b;
	}
};

struct Node {
	int x, y;
} a[N], c[N];

struct Square {
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
} b[N];

struct SSeg {
	int op, x, y, k;
} d[N];

bool cross( Func &cur, Node &to ) {
	if( to.x < cur.left || to.x > cur.rig ) 
		return false;
	if( aabs( cur.f(to.x) - (double)to.y ) <= eps ) 
		return true;
	return false;
}

bool cross( Func &cur, SSeg &to ) {
	if( to.op == 0 ) {
		const auto res = ( ( (double)to.y - cur.b  ) / cur.k );
		if( to.x <= res && res <= to.x + to.k ) 
			return true;
		return false;
	}
	if( to.op == 1 ) {
		const auto res = cur.f(to.x);
		if( to.y <= res && res <= to.y + to.k ) 
			return true;
		return false;
	}
	return false;
}

void calc() {
	cint n = read<int>();
	cint m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i].x = read<int>();
		a[i].y = read<int>();
	}
	for( int i = 1; i <= m; i ++ ) {
		b[i].x1 = read<int>();
		b[i].y1 = read<int>();
		b[i].x2 = read<int>();
		b[i].y2 = read<int>();
		b[i].x3 = read<int>();
		b[i].y3 = read<int>();
		b[i].x4 = read<int>();
		b[i].y4 = read<int>();
		cint base = ( i - 1 ) * 4;;
		c[ base + 1 ] = { b[i].x1, b[i].y1 };
		c[ base + 2 ] = { b[i].x2, b[i].y2 };
		c[ base + 3 ] = { b[i].x3, b[i].y3 };
		c[ base + 4 ] = { b[i].x4, b[i].y4 };
		d[ base + 1 ] = { 0, b[i].x2, b[i].y2, b[i].x1 - b[i].x2 };
		d[ base + 2 ] = { 0, b[i].x3, b[i].y3, b[i].x4 - b[i].x3 };
		d[ base + 3 ] = { 1, b[i].x3, b[i].y3, b[i].y2 - b[i].y3 };
		d[ base + 4 ] = { 1, b[i].x4, b[i].y4, b[i].y1 - b[i].y4 };
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= 4 * m; j ++ ) {
			if( is_x
		}
	}
}

int main() {
	int T = read<int>();
	while( T -- ) {
		calc();
	}
}
