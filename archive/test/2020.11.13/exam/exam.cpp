#include <cstdio>

#include <algorithm>

const int N = 1e4 + 1e3;

int a[N], b[N];


int main() {
	freopen( "exam.in", "r", stdin );
	freopen( "exam.out", "w", stdout );

	int n;
	std::vector<int> uni;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		uni.push_back( a[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &b[i] );
		uni.push_back( b[i] );
	}
	{
		std::sort( uni.begin(), uni.end() );
		auto end = std::unique( uni.begin(), uni.end() );
		uni.erase( end, uni.end() );
		for( auto x: uni ) 
			printf( "%d\n", x );
	}


	fclose( stdin );
	fclose( stdout );
	return 0;
}
