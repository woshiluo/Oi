#include <cstdio>
#include <cstring> 

#include <queue>
#include <vector>

#include "chameleon.h"

namespace woshiluo{
};

void Solve(int n) {
	n = n * 2;
	bool vis[ n + 10 ], upd[ n + 10 ], inque[ n + 10 ];
	//int f[ n + 10 ][ n + 10 ];
	int same[ n + 10 ][ n + 10 ];
	// -1 false 0 unkown 1 true
	std::vector<int> edge[ n + 10 ];
	//	memset( f, -1, sizeof(f) );
	memset( same, 0, sizeof(same) );
	memset( vis, 0, sizeof(vis) );
	memset( inque, 0, sizeof(inque) );
	memset( upd, 0, sizeof(upd) );


	for( int top = 1; top <= n; top ++ ) {
		vis[top] = true;
		for( int i = 1; i <= n; i ++ ) {
			if( vis[i] || i == top ) 
				continue;
			std::vector<int> a;
			a.push_back( top ); a.push_back(i);
			int cnt = Query(a);
			if( cnt != 2 ) { 
				edge[top].push_back(i);
				edge[i].push_back(top);
			}
		}
		int size = edge[top].size();
		if( size == 1 ) {
			int to = edge[top][0];
			same[top][to] = same[to][top] = 1;
		}
		if( size == 3 ) {
			int son1 = edge[top][0], son2 = edge[top][1], 
				son3 = edge[top][2], cnt12, cnt13, cnt23;
			std::vector<int> a, b;
			a.push_back( top );
			b = a; b.push_back( son1 ); b.push_back( son2 );
			cnt12 = Query(b);

			b = a; b.push_back( son1 ); b.push_back( son3 );
			cnt13 = Query(b);

			b = a; b.push_back( son2 ); b.push_back( son3 );
			cnt23 = Query(b);

			if( cnt12 == cnt13 && cnt12 == 2 ) 
				same[top][son1] = same[son1][top] = -1;
			if( cnt12 == cnt23 && cnt12 == 2 ) 
				same[top][son2] = same[son2][top] = -1;
			if( cnt13 == cnt23 && cnt13 == 2 ) 
				same[top][son3] = same[son3][top] = -1;
		} 

	}
	for( int i = 1; i <= n; i ++ ) {
		if( upd[i] ) 
			continue;
		int size = edge[i].size();
		for( int j = 0; j < size; j ++ ) {
			if( same[i][ edge[i][j] ] != -1 ) {
				fprintf( stderr, "%d %d\n", i, edge[i][j] );
				Answer( i, edge[i][j] );
				upd[i] = upd[ edge[i][j] ] = true;
				break;
			}
		}
	}
}
