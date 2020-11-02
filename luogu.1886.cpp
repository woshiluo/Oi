#include <cstdio>

#include <queue>

const int N = 1e6 + 1e5;

int n, k;
int a[N];

int main() {
#ifdef woshiluo
	freopen( "luogu.1886.in", "r", stdin );
	freopen( "luogu.1886.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}

	{
		std::deque<int> q;
		for( int i = 1; i <= n; i ++ ) {
			while( !q.empty() && q.front() + k <= i ) 
				q.pop_front();
			while( !q.empty() && a[q.back()] > a[i] )
				q.pop_back();
			q.push_back(i);
			if( i >= k ) 
				printf( "%d ", a[q.front()] );
		}
	}
	printf( "\n" );
	{
		std::deque<int> q;
		for( int i = 1; i <= n; i ++ ) {
			while( !q.empty() && q.front() + k <= i ) 
				q.pop_front();
			while( !q.empty() && a[q.back()] < a[i] )
				q.pop_back();
			q.push_back(i);
			if( i >= k ) 
				printf( "%d ", a[q.front()] );
		}
	}
}
