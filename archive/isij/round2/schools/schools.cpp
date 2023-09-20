#include <cstdio>
#include <cstring>

#include <vector>

int n, node_cnt = 1;

char str[110];
int cnt[1000*110];
int nxt[1000*110][100];

inline bool is_number( char s ) {
	return ( s >= '0' && s <= '9' );
}

inline int hash( char s ) {
	if( is_number(s) )
		return s - '0';
	if( s >= 'A' && s <= 'B' ) 
		return s - 'A' + 9;
	return s - 'a' + 9 + 26;
}

void insert( char *s ) {
	int cur = 1;
	for( ; *s; s ++ ) {
		if( nxt[cur][hash(*s)] )
			cur = nxt[cur][hash(*s)];
		else {
			nxt[cur][hash(*s)] = ++ node_cnt;
			cur = nxt[cur][hash(*s)];
		}
	}
	cnt[cur] ++;
}

char st[110];
int st_cnt, ans;
void get_ans( int cur ) {
	if( cnt[cur] && cnt[cur] <= 5 ) 
		ans ++;
	for( int i = 0; i <= 9; i ++ ) {
		if( nxt[cur][i] ) {
			get_ans( nxt[cur][i] );
		}
	}
}
void dfs( int cur ) {
	if( cnt[cur] && cnt[cur] <= 5 ) {
		st[ st_cnt + 1 ] = 0;
		printf( "%s\n", st + 1 );
	}
	for( int i = 0; i <= 9; i ++ ) {
		if( nxt[cur][i] ) {
			st[ ++ st_cnt ] = i + '0';
			dfs( nxt[cur][i] );
			st_cnt --;
		}
	}
}

int main() {
	freopen( "schools.in", "r", stdin );
	freopen( "schools.out", "w", stdout );

	scanf( "%d\n", &n );
	for( int i = 1; i <= n; i ++ ) {
		char str[110];
		fgets( str, 105, stdin );
		int len = strlen(str);
		bool flag = false;
		char tmp[110]; int tmp_len = -1;
		for( int j = 0; j < len; j ++ ) {
			if( is_number( str[j] ) ) {
				flag = true;
				tmp[ ++ tmp_len ] = str[j];
			}
			else if( flag ) {
				break;
			}
		}
		tmp[ tmp_len + 1 ] = 0;
		if( tmp_len >= 0 ) 
			insert(tmp);
	}

	get_ans(1);
	printf( "%d\n", ans );
	dfs(1);

	fclose( stdin );
	fclose( stdout );
	return 0;
}
