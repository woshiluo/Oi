#include <cstdio>
#include <cstring>

int n;
char input_str[5100], tmp_str[5100];

inline bool check(char *str) {
	int tmp_int = n >> 1;
	for(int i = 1; i <= tmp_int; i++) {
		if( str[i] != str[ n - i + 1 ] ) 
			return false;
	}
	if( strcmp(str + 1, input_str + 1) == 0 ) 
		return false;
	return true;
}

int main() {
	scanf("%s", input_str + 1);
	n = strlen(input_str + 1);

	for(int i = 1, j; i < n; i++){
		j = 0;	
		for(int k = i + 1; k <= n; k++) {
			tmp_str[ ++j ] = input_str[k];
		}
		for(int k = 1; k <= i; k++) {
			tmp_str[ ++j ] = input_str[k];
		}
		if( check(tmp_str) ) {
			printf("1");
			return 0;
		}
	}
	
	for(int i = 1, j; i <= n >> 1; i++) {
		j = 0;	
		for(int k = n - i + 1; k <= n; k++) {
			tmp_str[ ++j ] = input_str[k];
		}
		for(int k = i + 1; k <= n - i; k++) {
			tmp_str[ ++j ] = input_str[k];
		}
		for(int k = 1; k <= i; k++) {
			tmp_str[ ++j ] = input_str[k];
		}
		if( check(tmp_str) ) {
			printf("2");
			return 0;
		}
	}
	printf("Impossible");
}
