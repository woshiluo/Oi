#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
typedef pair <int, int> pii;

inline int read() {
	int x = 0, f = 0;
	char c = getchar();
	while (!isdigit(c)) {if (c == '-') f = 1; c = getchar();}
	while (isdigit(c)) x = (x << 1) + (x << 3) + (c & 15), c = getchar();
	return f? -x : x;
}

const int MAXN = 1e6, inf = 0x3f3f3f3f;
char str[MAXN + 10];
int dp[3][2][26], dp2[26][26], f[MAXN + 10], a[MAXN + 10], nxt[MAXN + 10], pos[26];
void chkmin(int &x, int y) {if(x>y) x=y;}

int main() {
#ifdef woshiluo
	freopen( "1006.in", "r", stdin );
	freopen( "1006.out" ,"w", stdout );
#endif
	int T = read();
	while (T--) {
		//fgets(str+1,MAXN+5,stdin);
		scanf("%s", str + 1);
		int n = strlen(str + 1);
		for (int i = 0; i < 26; ++i) pos[i] = 0;
		for (int i = 1; i <= n; ++i) a[i] = str[i] - 'a';
		for (int i = n; i >= 1; --i) {
			nxt[i] = pos[a[i]];
			pos[a[i]] = i;
		}
		for (int i = 0; i <= n; ++i)
			f[i] = inf;
		memset(dp,0x3f,sizeof dp);
		memset(dp2,0x3f,sizeof dp2);
		static int p[3];
		p[0] = 0; p[1] = 1; p[2] = 2;
		f[0] = 0;
		for(int j = 0;j < 26; ++j) dp[ p[1] ][0][j] = 1;
		for (int i = 1; i <= n; ++i) {
			p[0] ++;
			p[1] ++;
			p[2] ++;
			if( p[0] > 2 ) 
				p[0] -= 3;
			if( p[1] > 2 ) 
				p[1] -= 3;
			if( p[2] > 2 ) 
				p[2] -= 3;

			memset(dp[ p[2] ],0x3f,sizeof dp[0]);
			for(int j = 0;j < 26; ++j)
				chkmin(dp[ p[1] ][1][j],dp2[a[i]][j]);
			memset(dp2[a[i]],0x3f,sizeof dp2[a[i]]);

			f[i] = min(f[i], f[i - 1] + 1);
			chkmin(dp[ p[1] ][0][a[i]], f[i - 1]);
			f[i] = min(f[i], dp[ p[0] ][1][a[i]]);

			const int la = f[ i - 1 ];
			const int cur = a[i];
			const int cnxt = nxt[i];

			for (int j = 0; j < 26; ++j) {
				chkmin(dp[ p[1] ][0][j], min(la,dp[ p[0] ][0][j]) + 1);
				chkmin(dp[ p[1] ][1][j], min(dp[ p[0] ][0][j],dp[ p[0] ][1][j]) + 1);
				chkmin(dp[ p[2] ][1][j], dp[ p[0] ][0][j] + 1);
				chkmin(dp2[cur][j], dp[ p[0] ][0][j] + cnxt - i - 1);
				chkmin(f[i], dp[ p[0] ][1][j] + 1);
				chkmin(f[i], dp[ p[1] ][1][j] + 1);
			}

			const int tmp = f[i] + 1;
			for(int j = 0;j < 26; ++j)
				chkmin(dp[ p[1] ][0][j], tmp);
		}
		printf("%d\n", f[n]);
	}
	return 0;
}
