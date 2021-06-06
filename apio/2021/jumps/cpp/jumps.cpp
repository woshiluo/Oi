#include "jumps.h"

#include <cstring>

#include <vector>
#include <queue>

const int N = 2e5 + 1e4;
const int INF = 0x3f3f3f3f;

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

void init( int n, std::vector<int> height ) {
	{
		for( int i = 0; i < n; i ++ ) {
			for( int j = i - 1; j >= 0; j -- ) {
				if( height[j] > height[i] ) {
					add_edge( i, j );
					break;
				}
			}
		}
	}
	{
		for( int i = n - 1; i > 0; i -- ) {
			for( int j = i + 1; j < n; j ++ ) {
				if( height[j] > height[i] ) {
					add_edge( i, j );
					break;
				}
			}
		}
	}
}

int dis[N];
int minimum_jumps( int a, int b, int c, int d ) {
	memset( dis, INF, sizeof(dis) );
	std::queue<int> q;
	for( int i = a; i <= b; i ++ ) {
		q.push(i);
		dis[i] = 0;
	}
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		if( c <= cur && cur <= d ) 
			return dis[cur];
		for( int i = ehead[cur]; i; i = e[i].next ) {
			int to = e[i].to;
			if( dis[to] > dis[cur] + 1 ) {
				dis[to] = dis[cur] + 1;
				q.push(to);
			}
		}
	}
	return -1;
}
