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

#include <vector>
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

template <class T>
T aabs( const T cur ) { return cur < 0? -cur: cur; }

const int N = 110;
const int Q = 1e7 + 1e3;
const int INF = 0x3f3f3f3f;

struct Set {/*{{{*/
	int fa[N];
	void init( int n ) {
		for( int i = 0; i <= n; i ++ ) {
			fa[i] = i;
		}
	}
	Set( int n = 0 ) { init(n); }
	int& get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int &p = get_fa( fa[cur] );
		fa[cur] = p;
		return p;
	}
	inline int& operator[] ( int index ) {
		return this -> get_fa(index);
	}
} set;/*}}}*/

struct Edge { int from, to, val; bool flag; };
struct Ans { 
	int id; ll val; int tot_0, tot_1; 
	bool operator< ( const Ans &_b ) const { return id < _b.id; }
	bool operator== ( const Ans &_b ) const { return id == _b.id; }
};

std::vector<Edge> ori, e[2];
std::vector<Ans> ans;
int q[Q];

ll gen( int n, int x, int &min_cost, int tot[] ) {
	min_cost = 0;
	std::vector<Edge> list;
	e[0].clear(); e[1].clear();
	for( auto &edge: ori ) {
		if( edge.val - x < 0 ) {
			e[0].push_back( (Edge) { edge.from, edge.to, aabs( edge.val - x ), false } );
			list.push_back( e[0].back() );
		}
		else {
			e[1].push_back( (Edge) { edge.from, edge.to, aabs( edge.val - x ), true } );
			list.push_back( e[1].back() );
		}
	}

	auto cmp = []( const Edge &_a, const Edge &_b ) { return _a.val < _b.val; };
	std::sort( e[0].begin(), e[0].end(), cmp );
	std::sort( e[1].begin(), e[1].end(), cmp );
	std::sort( list.begin(), list.end(), cmp );

	ll res = 0;
	set.init(n);
	for( auto &edge: list ) {
		if( set[ edge.from ] == set[ edge.to ] ) 
			continue;
		tot[ edge.flag ] ++;
		set[ edge.from ] = set[ edge.to ];
		res += 1LL * edge.val;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n, m;
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int u, v, w;
		u = read<int>(); v = read<int>(); w = read<int>();
		ori.push_back( (Edge) { u, v, w, 0 } );
	}

	{
		int cur = 0, nxt = 0, tot[2] = { 0, 0 };
		ll val = gen( n, cur, nxt, tot );
		ans.push_back( (Ans){ cur, val, tot[0], tot[1] } );
	}
	{
		for( int i = 0; i < m; i ++ ) {
			for( int j = i; j < m; j ++ ) {
				{
					int cur = ( ori[i].val + ori[j].val ) / 2, nxt = 0, tot[2] = { 0, 0 };
					ll val = gen( n, cur, nxt, tot );
					ans.push_back( (Ans){ cur, val, tot[0], tot[1] } );
				}
				{
					int cur = ( ( ori[i].val + ori[j].val ) / 2 ) + 1, nxt = 0, tot[2] = { 0, 0 };
					ll val = gen( n, cur, nxt, tot );
					ans.push_back( (Ans){ cur, val, tot[0], tot[1] } );
				}
			}
		}
	}

	std::sort( ans.begin(), ans.end() );
	ans.erase( std::unique( ans.begin(), ans.end() ), ans.end() );

	ll res = 0;
	{
		int p, k;
		int a, b, c;
		p = read<int>(); k = read<int>(); 
		a = read<int>(); b = read<int>(); c = read<int>();
		for( int i = 1; i <= k; i ++ ) {
			if( i <= p ) 
				q[i] = read<int>();
			else 
				q[i] = ( 1LL * q[ i - 1 ] * a + 1LL * b ) % c;

			int id = std::upper_bound( ans.begin(), ans.end(), (Ans) { q[i], 0, 0, 0 } ) - ans.begin() - 1;
			int len = ( q[i] - ans[id].id );
			ll tmp = ( ans[id].val + 1LL * ( ans[id].tot_0 - ans[id].tot_1 ) * len );
			// printf( "%d %d %lld\n", q[i], ans[id].id, tmp );

			res ^= tmp;
		}
	}
	printf( "%lld\n", res );
}
