#include <cstdio>
#include <cstring>

#include <queue>

const int N = 1e6 + 1e5;

class AC_AM {/*{{{*/
	private: 
		struct node { int sum, fail, nxt[26]; };

		int node_cnt = 1;
		node tree[N];
	public:
		void insert( char str[] ) {
			int len = strlen(str);
			int cur = 1;
			for( int i = 0; i < len; i ++ ) {
				int cur_char = str[i] - 'a';
				if( tree[cur].nxt[cur_char] == 0 ) { 
					tree[cur].nxt[cur_char] = ++ node_cnt;
					tree[node_cnt].fail = 1;
				}
				cur = tree[cur].nxt[cur_char];
			}
			tree[cur].sum ++;
		}
		void build() {
			std::queue<int> q;
			for( int i = 0; i < 26; i ++ ) {
				if( tree[1].nxt[i] ) 
					q.push( tree[1].nxt[i] );
				else 
					tree[1].nxt[i] = 1;
			}
			while( !q.empty() ) {
				int fnt = q.front(); q.pop();
				for( int i = 0; i < 26; i ++ ) {
					if( tree[fnt].nxt[i] ) {
						tree[ tree[fnt].nxt[i] ].fail = tree[ tree[fnt].fail ].nxt[i];
						q.push( tree[fnt].nxt[i] );
					}
					else 
						tree[fnt].nxt[i] = tree[ tree[fnt].fail ].nxt[i];
				}
			}
		}
		int query( char str[] ) {
			int cur = 1, res = 0;
			for( int i = 0; str[i] != 0; i ++ ) {
				cur = tree[cur].nxt[ str[i] - 'a' ];
				for( int tmp = cur; tmp != 1 && tree[tmp].sum != -1; tmp = tree[tmp].fail ) {
					res += tree[tmp].sum; tree[tmp].sum = -1;
				}
			}
			return res;
		}
};/*}}}*/

int n;
char s[N];
AC_AM ac_am;

int main() {
#ifdef woshiluo
	freopen( "luogu.3808.in", "r", stdin );
	freopen( "luogu.3808.out", "w", stdout );
#endif
	scanf( "%d", &n );
	while( n -- ) {
		scanf( "%s", s );
		ac_am.insert(s);
	}
	ac_am.build();
	scanf( "%s", s );
	printf( "%d\n", ac_am.query(s) );
}
