#include <cstdio> 
#include <cstring> 

int n, m; 
int c[5]; 
int a[505][505], b[505]; 
bool flag, flag1, flag2; 

int main(){

	scanf("%d%d", &n, &m); 
	for(int i = 1; i <= n;  i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &a[i][j]); 
		}
	}

	for(int l = 0; l < 11; l++){
		c[0] =  0;  c[1] = 0;  c[2] = 0; 
		for(int i = 1; i <= n; i++){
			flag1 = flag2 = 0;
			for(int j = 1; j <= m; j++)
				if((a[i][j] >> l) & 1){
					b[i] = 1; 
					flag2 = true; 
					if(flag1){
						b[i] = 2; 
						break; 
					}
				}
				else{
					flag1 = true; 
					b[i] = 0; 
					if(flag2){
						b[i] = 2; 
						break; 
					}
				}
			c[ flag2 + flag1 ]++;
			if(flag1 && flag2 == false) c[1]--, c[0]++;
		}
		if(c[1] & 1){
			printf("TAK\n"); 
			for(int i = 1; i <= n; i++){
				if(b[i] == 0||b[i] == 1) printf("1 "); 
				else if(b[i] == 2){
					for(int j = 1; j <= m; j++)
						if(!((a[i][j] >> l)&1)){
							printf("%d ", j); 
							break; 
						}
				}
			}
			return 0; 
		}
		else{
			if(c[2]){
				flag = false;
				printf("TAK\n"); 
				for(int i = 1; i <= n; i++){
					if(b[i] == 0||b[i] == 1) printf("1 "); 
					else if(b[i] == 2){
						for(int j = 1; j <= m; j++)
							if(!flag&&((a[i][j] >> l)&1)){
								printf("%d ", j); 
								flag = true; 
								break; 
							}
							else if(flag&&(!((a[i][j] >> l)&1))){
								printf("%d ", j); 
								break; 
							}
					}
				}
				return 0; 
			}
		}
	}

	printf("NIE\n"); 
	return 0; 
}
