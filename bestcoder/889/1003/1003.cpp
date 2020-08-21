#include <cstdio>

#include <queue>

const int N = 1100;

int T;
int n, m;
int f[N][N];

struct node { int x, y; };
int gcd( int a, int b ) { return b == 0? a: gcd( b, a % b ); }

void init() {
	std::queue<node> q;
	q.push( (node) { 1, 1 } );
	f[1][1] = 1;
	while( !q.empty() ) {
		node top = q.front();
		if( top.x + 1 <= 1000 ) {
			int res = f[top.x][top.y] + ( gcd( top.x + 1, top.y ) == 1 );
			int &cur = f[ top.x + 1 ][top.y];
			if( cur == 0 )
				q.push( (node) { top.x + 1, top.y } );
			if( res > cur )
				cur = res;
		}
		if( top.y + 1 <= 1000 ) {
			int res = f[top.x][top.y] + ( gcd( top.x, top.y + 1 ) == 1 );
			int &cur = f[top.x][ top.y + 1 ];
			if( cur == 0 )
				q.push( (node) { top.x, top.y + 1 } );
			if( res > cur )
				cur = res;
		}
		q.pop();
	}
}

int main() {
	init();
	scanf( "%d", &T );
	while( T -- ) {
		int a, b;
		scanf( "%d%d", &a, &b );
		printf( "%d\n", f[a][b] );
	}
}
