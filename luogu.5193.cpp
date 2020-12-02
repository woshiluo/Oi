#include <cstdio>

struct point { int x, y; };

int n;
point a[N];

bool cmp( point _a, point _b ) {
	if( _a.x == _b.x ) 
		return _a.y < _b.y;
	return _a.x < _b.x;
}

int main() {
	scanf( "%d%d", &n, &r );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &x, &y );
		a[i].x = x + y; a[i].y = x - y;
	}
}
