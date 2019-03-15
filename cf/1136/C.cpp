#include <cstdio>
#include <algorithm>

const int N = 510;

struct line{
	int num[N], cnt;
	int& operator[](int i){
		return num[i];	
	}
}left[(N << 1) + 20], n_left[(N << 1) + 20];

int n, m;
int map1[N][N], map2[N][N];

int main(){
	scanf("%d%d", &n, &m);	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &map1[i][j]);	
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &map2[i][j]);	
		}
	}
	
	for(int o = 1; o <= n; o++){
		int i = o, j = m; 
		while(i <= n && j > 0){
			left[o][++left[o].cnt] = map1[i][j];
			i++, j--;
		}
		std::sort(left[o].num + 1, left[o].num + left[o].cnt + 1);
	}
	for(int o = 1; o <= m - 1; o++){
		int i = 1, j = o; 
		while(i <= n && j > 0){
			left[n + o][++left[n + o].cnt] = map1[i][j];
			i++, j--;
		}
		std::sort(left[n + o].num + 1, left[n + o].num + left[n + o].cnt + 1);
	}

	for(int o = 1; o <= n; o++){
		int i = o, j = m; 
		while(i <= n && j > 0){
			n_left[o][++n_left[o].cnt] = map2[i][j];
			i++, j--;
		}
		std::sort(n_left[o].num + 1, n_left[o].num + n_left[o].cnt + 1);
		for(i = 1; i <= n_left[o].cnt; i++){
			if(n_left[o][i] != left[o][i]){
				printf("NO");
				return 0;
			}
		}
	}
	for(int o = 1; o <= m - 1; o++){
		int i = 1, j = o; 
		while(i <= n && j > 0){
			n_left[n + o][++n_left[n + o].cnt] = map2[i][j];
			i++, j--;
		}
		std::sort(n_left[n + o].num + 1, n_left[n + o].num + n_left[n + o].cnt + 1);
		for(i = 1; i <= n_left[n + o].cnt; i++){
			if(n_left[n + o][i] != left[n + o][i]){
				printf("NO");
				return 0;
			}
		}
	}
	printf("YES");
}
