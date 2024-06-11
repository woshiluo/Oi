/*
 * a.cpp 2024-03-03
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <stack>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1e6 + 1e5;
const int mod = 1e9 + 7;

struct ModInt {/*{{{*/
	int cur;
	ModInt( i64 _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

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

struct Edge {
	i32 to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

i32 in[N];

int col_cnt,  col[N];
bool cv[N], vis[N], cir[N];
ModInt sum[N];
ModInt p[N];
std::stack<i32> st;

void dfs( ci32 cur ) {
	if( cv[cur] ) {
		col_cnt ++;
		sum[col_cnt] = 1;
		while( st.top() != cur ) {
			cir[ st.top() ] = true;
			col[ st.top() ] = col_cnt;
			sum[col_cnt] *= ( (ModInt)1 - p[ st.top() ] );
			st.pop();
		}
		cir[ st.top() ] = true;
		col[ st.top() ] = col_cnt;
		sum[col_cnt] *= ( (ModInt)1 - p[ st.top() ] );
		st.pop();
		return ;
	}
	cv[cur] = true;
	vis[cur] = true;
	st.push(cur);
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to != cur && (cv[to] || !vis[to] ) )
			dfs(to);
	}
	cv[cur] = false;
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		ci32 fa = read<i32>();
		add_edge( i, fa );
		in[fa] ++;
	}
	for( int i = 1; i <= n; i ++ ) {
		p[i] = read<i32>();
	}

	for( int i = 1; i <= n; i ++ ) {
		if( !vis[i] ) 
			dfs(i);
		while( !st.empty() ) 
			st.pop();
	}

	ModInt res = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( !cir[i] ) {
			res += ( (ModInt)1 - p[i] );
		}
		else {
			res += ( (ModInt)1 - p[i] ) * ( (ModInt)1 - ( sum[ col[i] ] / ( (ModInt)1 - p[i] ) ) );
		}
	}

	for( int i = 1; i <= col_cnt; i ++ ) {
		res += sum[i];
	}

	res.output();
}
