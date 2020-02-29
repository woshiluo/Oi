#include <cstdio>
#include <cstring>

const int N = 1e6 + 1e5;

int T;
char str[N];
bool fir, sec, tir;

int main(){
	scanf("%d\n", &T);
	while(T--){
		fgets(str, N - 1, stdin);
//		getline(str);
		fir = sec = tir = false;
		for(int i = 0; ;i++){
			if(str[i] == '\n' || str[i] == 0 ) 
				 break;
			if(str[i] == ' ') 
				continue;
			if(str[i] == '\''){
				fir = true;
				continue;
			}
			else if(fir && str[i] == 'o' && str[i + 1] == 'r' && (str[i + 2] == ' ')){
				i++;
				sec = true;
				continue;
			}
			else if(fir && sec){
				if(str[i] == str[i + 2] && str[i + 1] == '=' && ( (str[i] <= '9' && str[i] >= '0') || (str[i] <= 'Z' && str[i] >= 'A') || ( str[i] <='z' &&  str[i] >='a') ) && str[i + 3] == '#'){
					tir = true;
					break;
				}
				else fir = sec = tir = false;
			}
			else fir = sec = tir = false;
		}	
		if(fir && sec && tir)
			printf("Warning\n");
		else 
			printf("Safe\n");
	}
}
