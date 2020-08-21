#include <cstdio>
#include <cstring>

const int N = 1e6 + 1e5;

int len, Max_char;
int sa[N], tp[N], rank[N], rank_cnt[N];
char str[N];

void sort(){
	memset(rank_cnt, 0, sizeof(rank_cnt));
	for(int i = 1; i <= len; i++)
		rank_cnt[ rank[i] ] ++;
	for(int i = 1; i <= Max_char; i++)
		rank_cnt[i] += rank_cnt[i - 1];
	for(int i = len; i > 0; i--){
		sa[ rank_cnt[ rank[ tp[i] ] ] -- ] = tp[i];	
	}
}

void get_sa(){
	Max_char = 'z' - '0' + 2;
	for(int i = 1; i <= len; i++){
		rank[i] = str[i] - '0' + 1;
		tp[i] = i;
	}
	sort();
	
	for(int l = 1, tmp_cnt = 0; tmp_cnt < len; l <<= 1, Max_char = tmp_cnt){
		tmp_cnt = 0;
		for(int i = 1; i <= l; i++)
			tp[ ++ tmp_cnt ] = len - l + i;
		for(int i = 1; i <= len; i++){
			if( sa[i] > l )
				tp[ ++ tmp_cnt ] = sa[i] - l;
		}
		sort();
		
		memcpy(tp, rank, sizeof(rank));
		rank[ sa[1] ] = tmp_cnt = 1;
		for(int i = 2; i <= len; i++){
			rank[ sa[i] ] = ( tp[ sa[i] ] == tp[ sa[i - 1] ] && tp[ sa[i] + l ] == tp[ sa[i - 1] + l ]) ? tmp_cnt: ++ tmp_cnt;
		}
	}
}

int main(){
	scanf("%s", str + 1);
	len = strlen(str + 1);
	
	get_sa();

	for(int i = 1; i <= len; i++)
		printf("%d ", sa[i]);
}
