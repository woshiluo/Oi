#include <cstdio>

const int N = 4e5;

int n;
int left, cnt, sum[N];
char str[N];

int main(){
	scanf("%d", &n);
	scanf("%s", str);
	if(str[0] == '(') left++, cnt++;
	else if(str[0] == ')'){
		printf(":(");
		return 0;
	}
	else str[0] = '(', left ++, cnt++;
	for(int i = n - 1; i >= 0; i--)
		sum[i] = sum[i + 1] + (str[i] == '('); 	
	for(int i = 1; i < n; i++){
		if(cnt + sum[i] == (n >> 1)){
			for(int j = i; j < n; j++){
				if(str[j] != '(')
					str[j] = ')';
			}
			break;
		}
		if(str[i] == ')') {
			left--;
			continue;
		}
		left++; cnt++;
		str[i] = '(';
	}
	left = 0;
	for(int i = 0; i < n; i++){
		if(str[i] == '(') 
			left++;
		else 
			left--;
		if(left < 0 || (left == 0 && i != n - 1) ){
			printf(":(");	
			return 0;
		}
	}
	if(left != 0){
		printf(":(");	
		return 0;
	}
	printf("%s", str);
}
