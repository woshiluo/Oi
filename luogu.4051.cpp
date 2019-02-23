#include <cstdio>
#include <cstring>

const int N = (int)(1e5 + 1e4) << 2;
int Max_char = 'z';

char str[N];

int len;
int tp[N], rank[N], rank_cnt[N], sa[N];

inline void sort(){
	memset(rank_cnt, 0, sizeof(rank_cnt));
	for(int i = 1; i <= len; i++){
		rank_cnt[ rank[i] ]++;
	}
	for(int i = 1; i <= Max_char; i++){
		rank_cnt[i] += rank_cnt[i - 1];
	}
	for(int i = len; i >= 1; i--){
		sa[ rank_cnt[ rank[ tp[i] ] ]-- ] = tp[i];
	}	
}

inline void get_sa(){
	for(int i = 1; i <= len; i++){
		rank[i] = str[i];
		tp[i] = i;
	}
	sort();

	for(int w = 1, tmp_cnt; tmp_cnt < len; w <<= 1, Max_char = tmp_cnt) {
		tmp_cnt = 0;
		for(int i = 1; i <= w; i++) {
			tp[ ++tmp_cnt ] = len - w + i;
		}
		for(int i = 1; i <= len; i++) {
			if(sa[i] > w) 
				tp[ ++tmp_cnt ] = sa[i] - w;
		}
		sort();

		memcpy(tp, rank, sizeof(rank));
		rank[ sa[1] ] = tmp_cnt = 1;
		for(int i = 2; i <= len; i++) {
			rank[ sa[i] ] = ( tp[ sa[i] ] == tp[ sa[i - 1] ] && tp[ sa[i] + w ] == tp[ sa[i - 1] + w ] )? tmp_cnt: ++tmp_cnt;
		}
	}
}

int main(){
#ifdef woshiluo
	freopen("luogu.4051.in", "r", stdin);
	freopen("luogu.4051.out", "w", stdout);
#endif
	scanf("%s", str + 1);
	len = strlen(str + 1);
	for(int i = len + 1; i <= (len << 1); i++){
		str[i] = str[i - len];
	}
	len <<= 1;
	
	get_sa();
	for(int i = 1; i <= len; i++){
		if( sa[i] > (len >> 1) ) continue;
		if(sa[i] == 1)
			printf("%c", str[len >> 1]);
		else 
			printf("%c", str[sa[i] - 1]);
	}
}
