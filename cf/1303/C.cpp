#include <cstdio>
#include <cstring>

const int N = 210;

int n;
char str[N];
bool vis[N];

struct node {
	int left, rig;
	char node;
} links[N];

void print( int cur, int la ) {
	if( cur == 0 )
		return ;
	if( links[cur].left != la )
		print( links[cur].left, cur );
	printf( "%c", links[cur].node );
	if( links[cur].rig != la )
		print( links[cur].rig, cur );
}

int main() {
#ifdef woshiluo
	freopen( "C.in", "r", stdin );
	freopen( "C.out", "w", stdout );
#endif
	scanf( "%d", &n );
	while( n -- ) {
		memset( links, 0, sizeof(links) );
		memset( vis, 0, sizeof(vis) );
		scanf( "%s", str + 1 );
		links[1].node = str[1];
		vis[ str[1] ] = true;
		int cur = 1, len = strlen( str + 1 ), links_cnt = 1; bool flag = false;
		for( int i = 2; i <= len; i ++ ) {
			if( links[cur].left != 0 && links[ links[cur].left ].node == str[i] ) {
				cur = links[cur].left;
				continue;
			}
			if( links[cur].rig != 0 && links[ links[cur].rig ].node == str[i] ) {
				cur = links[cur].rig;
				continue;
			}
			if( vis[ str[i] ] ) {
				flag = true;
				break;
			}
			vis[ str[i] ] = true;
			if( links[cur].left == 0 ) {
				links_cnt ++;
				links[cur].left = links_cnt;
				links[ links_cnt ].rig = cur;
				links[ links_cnt ].node = str[i];
				cur = links_cnt;
				continue;
			}
			if( links[cur].rig == 0 ) {
				links_cnt ++;
				links[cur].rig = links_cnt;
				links[ links_cnt ].left = cur;
				links[ links_cnt ].node = str[i];
				cur = links_cnt;
				continue;
			}
			flag = true;
			continue;
		}
		if( flag ) 
			printf( "NO\n" );
		else {
			printf( "YES\n" );
			print( 1, 0 );
			for( int i = 0; i <= 25; i ++ ) {
				if( vis[ i + 'a' ] == false )
					printf( "%c", i + 'a' );
			}
			printf( "\n" );
		}
	}
}
