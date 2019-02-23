#include <cstdio>
#include <cstring>

const int N = 1e6 + 1e5;
int Max_Char = 'z' - '0' + 2;

int len;
bool now, la;
int rank[N], sa[N], tp[N], rank_cnt[N];
char str[N];

inline void sort(){
	memset(rank_cnt, 0, sizeof(rank_cnt));
	for(int i = 1; i <= len; i++) {
		rank_cnt[ rank[i] ]++;
	}
	for(int i = 1; i <= Max_Char; i++) {
		rank_cnt[i] += rank_cnt[i - 1];
	}
	for(int i = len; i >= 1; i--) {
		sa[ rank_cnt[ rank[ tp[i] ] ]-- ] = tp[i];
	}
}

inline void get_sa() {
	for(int i = 1; i <= len ; i++){ 
		rank[i] = str[i] - '0' + 1;
		tp[i] = i;
	}
	sort();
	for(int w = 1, tmp_cnt = 0; tmp_cnt < len; w <<= 1, Max_Char = tmp_cnt){
		tmp_cnt = 0;
		for(int i = 1; i <= w; i++) tp[ ++tmp_cnt ] = len - w + i;
		for(int i = 1; i <= len; i++) if(sa[i] > w) tp[ ++tmp_cnt ] = sa[i] - w;
		sort();

		memcpy(tp, rank, sizeof(rank));
		rank[ sa[1] ] = tmp_cnt = 1;
		for(int i = 2; i <= len; i++){
			rank[ sa[i] ] = ( tp[ sa[i - 1] ] == tp[ sa[i] ] && tp[ sa[i - 1] + w ] == tp[ sa[i] + w ] ) ? tmp_cnt: ++tmp_cnt;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen("luogu.3809.in", "r", stdin);
	freopen("luogu.3809.out", "w", stdout);
#endif
	scanf("%s", str + 1);
	len = strlen(str + 1); //len--;

	get_sa();
	for(int i = 1; i <= len; i++) 
		printf("%d ", sa[i]);
}
