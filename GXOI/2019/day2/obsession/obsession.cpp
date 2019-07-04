#include <cstdio>
#include <cstring>

const int SIZE = 5;
const int mod = 1e9 + 7;

int T, n;

struct matrix{
	long long f[SIZE][SIZE];
	long long *operator[] (int now){ return f[now]; }
	matrix operator* (const matrix &b) const{
		matrix tmp = matrix(0);
		for(int i = 0; i < SIZE; i++){
			for(int j = 0; j < SIZE; j++){
				for(int k = 0; k < SIZE; k++){
					tmp.f[i][j] = (tmp.f[i][j] + f[i][k] * b.f[k][j]) % mod;	
				}
			}
		}
		return tmp;
	}
	matrix operator^ (int p){
		matrix res = matrix(1);
		while(p){
			if(p & 1) 
				res = res * (*this);
			(*this) = (*this) * (*this);
			p >>= 1;
		}
		return res;
	}
	matrix(long long now = 0){
		for(int i = 0; i < SIZE; i++){
			for(int j = 0; j < SIZE; j++){
				if(i != j)
					f[i][j] = 0;
				else 
					f[i][j] = now;
			}
		}
	}
}B, ans;

int main(){
	freopen("obsession.in", "r", stdin);
	freopen("obsession.out", "w", stdout);
	scanf("%d", &T);	
	while(T--){
		scanf("%d", &n);
		if(n <= 2) 
			printf("0\n");
		else {
			n -= 3;	
			ans = B = matrix(0);
			ans[0][0] = ans[0][2] = 2;
			ans[0][3] = ans[0][4] = 1;
			ans[0][1] = 0;
			B[0][0] = B[0][1] = B[1][0] = B[2][2] = B[3][2] = B[4][2] = B[3][3] = B[4][3] = B[3][4] = 1;
			B[2][0] = 2;
			ans = ans * (B ^ n);
			printf("%lld\n", ans[0][0]);
		}
	}
	fclose(stdin);
	fclose(stdout);
}
