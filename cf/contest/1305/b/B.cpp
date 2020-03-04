#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

const int N = 1100;

char s[N];
bool vis[N];
std::vector<int> a;

int main() {
#ifdef woshiluo
	freopen( "B.in", "r", stdin );
	freopen( "B.out", "w", stdout );
#endif
	scanf( "%s", s + 1 );
	int n = strlen( s + 1 );
	for( int i = 1; i <= n; i ++ ) {
		if( s[i] == '(' ) {
			for( int j = n; j > i; j -- ) {
				if( vis[j] == false && s[j] == ')' ) {
					vis[i] = true;
					vis[j] = true;
					a.push_back(i), a.push_back(j);
					break;
				}
			}
		}
	}
	int cnt = a.size();
	if( cnt == 0 ) {
		printf( "0" );
		return 0;
	}
	std::sort( a.begin(), a.end() );
	printf( "1\n" );
	printf( "%d\n", cnt );
	for( int i = 0; i < cnt; i ++ ) {
		printf( "%d ", a[i] );
	}
}
