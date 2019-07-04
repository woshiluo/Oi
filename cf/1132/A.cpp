#include <cstdio>

int cnt[5];

int main(){
	scanf("%d%d%d%d", &cnt[1], &cnt[2], &cnt[3], &cnt[4]);
	if(cnt[3] != 0 && cnt[1] == 0 ){
		printf("0");
		return 0;
	} 
	if(cnt[1] != cnt[4]){
		printf("0");
		return 0;
	}
	printf("1");
}
