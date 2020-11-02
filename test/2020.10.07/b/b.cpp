#include <cstdio>

#include <queue>

const int N = 2e6 + 1e5;

int n;
bool in[N], vis[N];
int sec[N];
int sub[N];

std::queue<int> q[2];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for ( int i = 1; i <= n; i ++ ) {
		int x, y;
		scanf( "%d%d", &x, &y );
		in[x] = true; in[y] = false;
		sub[x] = sub[y] = i;
	}

	int ans = 1;
	n = n * 2;
	for( int i = 1; i <= n; i ++ ) {
		if( in[i] ) {
			q[0].push( sub[i] );
			vis[ sub[i] ] = true;
			sec[ sub[i] ] = false;
		}
		else {
			if( sec[ sub[i] ] ) {
				while( !q[0].empty() ) {
					int cur = q[0].front(); q[0].pop();
					if( sec[cur] ) {
						printf( "0\n" );
						return 0;
					}
					sec[cur] ++;
					q[1].push(cur);
				}
			}
			else {
				bool flag = false;
				while( !q[0].empty() ) {
					int cur = q[0].front(); q[0].pop();
					if( sec[cur] == 1 ) 
						flag = true;
					if( sec[cur] == 2 ) {
						printf( "0\n" );
						return 0;
					}
					sec[cur] ++;
					q[1].push(cur);
				}
				if( flag == false ) 
					ans = ans * 2;
			}
		}
	}
	printf( "%d\n", ans );
}
