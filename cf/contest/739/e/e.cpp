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

const int N = 2100;
const double eps = 1e-7;

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

double p[N], u[N];
int n, limit_a, limit_b;

struct CheckRes { bool right; double val; };

double f[N];
int cnt_a[N], cnt_b[N];
CheckRes check_a( double offset_a, double offset_b ) {
	for( int i = 0; i <= n; i ++ ) {
		f[i] = 0; cnt_a[i] = cnt_b[i] = 0;
	}
	for( int i = 1; i <= n; i ++ ) {
		const double cost_a = p[i] - offset_a, cost_b = u[i] - offset_b;
		f[i] = f[ i - 1 ];
		cnt_a[i] = cnt_a[ i - 1 ]; cnt_b[i] = cnt_b[ i - 1 ];
		if( f[ i - 1 ] + cost_a - f[i] > eps ) {
			f[i] = f[ i - 1 ] + cost_a;
			cnt_a[i] = cnt_a[ i - 1 ] + 1;
			cnt_b[i] = cnt_b[ i - 1 ];
		}
		if( f[ i - 1 ] + cost_b - f[i] > eps ) {
			f[i] = f[ i - 1 ] + cost_b;
			cnt_a[i] = cnt_a[ i - 1 ];
			cnt_b[i] = cnt_b[ i - 1 ] + 1;
		}
		if( f[ i - 1 ] + cost_a + cost_b - u[i] * p[i] - f[i] > eps ) {
			f[i] = f[ i - 1 ] + cost_a + cost_b - u[i] * p[i];
			cnt_a[i] = cnt_a[ i - 1 ] + 1;
			cnt_b[i] = cnt_b[ i - 1 ] + 1;
		}
	}
	return (CheckRes) { cnt_a[n] >= limit_a, f[n] + offset_b * limit_b + offset_a * limit_a };
}

CheckRes check_b( double offset_b ) {
	double left = 0, rig = 1, offset_a = 0;
	while( left + eps <= rig ) {
		double mid = ( left + rig ) / 2.0;
		CheckRes res = check_a( mid, offset_b );

		if( res.right ) {
			offset_a = mid;
			left = mid + eps;
		}
		else
			rig = mid - eps;
	}

	check_a( offset_a, offset_b );

	return (CheckRes) { cnt_b[n] >= limit_b, f[n] + offset_b * limit_b + offset_a * limit_a };
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &limit_a, &limit_b );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lf", &p[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lf", &u[i] );
	}

	double left = 0, rig = 1, offset_b = 0;
	while( left + eps <= rig ) {
		double mid = ( left + rig ) / 2.0;
		CheckRes res = check_b(mid);

		if( res.right ) {
			offset_b = mid;
			left = mid + eps;
		}
		else 
			rig = mid - eps;
	}
	
	printf( "%.4lf", check_b(offset_b).val );
}
