#include <cstdio>
#include <cstring>

inline int Max(int a, int b){return a > b? a: b;}

const int N = 1100;

int T, n, m, stcnt, ans;
char tmp_read;
int height[N], width[N], st[N];
bool map[N][N];

inline void init(){
	ans = 0;
	memset(height, 0, sizeof(height));	
}

inline void readin(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			tmp_read=getchar();
			while(tmp_read!='F' && tmp_read!='R')
				tmp_read=getchar();
			map[i][j] = tmp_read == 'F' ? 1: 0;
		}
	}
}

inline void get_ans(int dep){
	stcnt = 0;
	for(int i = 1;i <= m; i++){
		if(map[dep][i]) 
			height[i]++;
		else 
			height[i] = 0;
	}
	for(int i = 1; i <= m + 1; i++){
		if(st[stcnt] < height[i]){
			st[++stcnt] = height[i];
			width[stcnt] = 1;
			ans = Max(ans, height[i]);
		}
		else {
			int tmp_width = 0;
			while(stcnt && st[stcnt] >= height[i]){
				tmp_width += width[stcnt];
				ans = Max(ans, st[stcnt--] * tmp_width);
			}
			st[++stcnt] = height[i];
			width[stcnt] = tmp_width + 1;
			ans = Max(ans, st[stcnt] * width[stcnt]);
		}
	}
}

int main(){
#ifdef woshiluo
	freopen("poj.1964.in", "r" , stdin);
	freopen("poj.1964.out", "w", stdout);
#endif
	scanf("%d", &T);
	while(T--){
		init();
		readin();
		for(int i = 1; i <= n; i++) 
			get_ans(i);
		printf("%d\n", ans * 3);
	}
}
