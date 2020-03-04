#include <cstdio>

int a;

int f( int cur ) {
	int tmp;
	if( scanf( "%d", &tmp ) != EOF )
		return f( ( cur | tmp ) - tmp );
	return ( cur | tmp ) - tmp;
}

int main() {
	scanf( "%d", &a );
	printf( "%d", f( a ) );
}
