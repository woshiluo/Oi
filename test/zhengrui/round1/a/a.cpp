/*
 * a.cpp
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

#include <map>
#include <queue>
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

const int N = 3e4 + 1e2;
const int K = 110;
const int INF = 0x3f3f3f3f;

namespace dinic {
	struct Edge {
		int to, next, flow;
	} e[ N * K ];
	int ehead[N], chead[N], ecnt = 1;
	void add_edge( int cur, int to, int flow ) {
		ecnt ++;
		e[ecnt].to = to;
		e[ecnt].flow = flow;
		e[ecnt].next = ehead[cur];
		ehead[cur] = ecnt;
	}

	std::vector<int> dep;
	bool bfs( int s, int t ) {
		std::queue<int> q;
		dep.clear();
		dep.resize( t + 10, -1 );
		dep[s] = 0; q.push(s);
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = ehead[cur]; i; i = e[i].next ) {
				if( e[i].flow == 0 ) 
					continue;
				const int to = e[i].to;
				if( dep[ to ] == -1 ) {
					dep[ to ] = dep[cur] + 1;
					q.push(to);
				}
			}
		}
		return dep[t] != -1;
	}

	int ed;
	int dfs( int cur, int flow ) {
		if( cur == ed ) 
			return flow;
		int res = 0;
		for( int &i = chead[cur]; i; i = e[i].next ) {
			if( e[i].flow == 0 || dep[ e[i].to ] != dep[cur] + 1 )
				continue;
			int p = dfs( e[i].to, Min( flow, e[i].flow ) );
			e[i].flow -= p;
			e[ i ^ 1 ].flow += p;
			res += p;
			flow -= p;
			if( flow == 0 ) 
				break;
		}
		return res;
	}
	int dinic( int s, int t ) {
		ed = t;
		int res = 0;
		while( bfs( s, t ) ) {
			memcpy( chead, ehead, sizeof(ehead) );
			res += dfs( s, INF );
		}
		return res;
	}
}

std::map<std::vector<int>, int> mp;
std::vector<int> node[N];

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int n, k;
	n = read<int>(); k = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j < k; j ++ ) {
			node[i].push_back(read<int>());
		}
		mp[ node[i] ] = i;
	}

	int n2 = ( n << 1 );
	int s = n2 + 1, t = n2 + 2;
	for( int i = 1; i <= n; i ++ ) {
		const int p1 = i;
		const int p2 = i + n;
		int cnt = 0;
		// self connect
		{
			dinic::add_edge( p1, p2, 1 );
			dinic::add_edge( p2, p1, 0 );
		}
		// add to s / t
		{
			for( auto &x: node[i] ) 
				cnt += ( x & 1 );
			if( cnt == 0 ) {
				dinic::add_edge( s, p1, INF );
				dinic::add_edge( p1, s, 0 );
			}
			if( cnt == k ) {
				dinic::add_edge( p2, t, INF );
				dinic::add_edge( t, p2, 0 );
			}
		}
		// add edge if dis( a, b ) = 1
		{
			for( int j = 0; j < k; j ++ ) {
				if( node[i][j] & 1 ) 
					continue;
				{
					std::vector<int> tmp = node[i];
					tmp[j] += 1;
					if( mp.count(tmp) ) {
						const int to = mp[tmp];
						dinic::add_edge( p2, to, INF );
						dinic::add_edge( to, p2, 0 );
					}
				}
				{
					std::vector<int> tmp = node[i];
					tmp[j] -= 1;
					if( mp.count(tmp) ) {
						const int to = mp[tmp];
						dinic::add_edge( p2, to, INF );
						dinic::add_edge( to, p2, 0 );
					}
				}
			}
		}
	}

	printf( "%d\n", dinic::dinic( s, t ) );

	return 0;
}
