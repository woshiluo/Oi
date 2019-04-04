#include <cstdio>
#include <cstring>

const int N = 51000;
const int W = 1e4;
const int M = 4;

int ten[10] = {0, 1, 10, 100, 1000, 10000};

struct bigint{
	int num[N], len;
	bigint(){
		len = 0;
		memset(num, 0, sizeof(num));
	}
	bigint operator* (bigint b){
		bigint c;	
		for(int j = 1; j <= b.len; j++){
			for(int i = 1; i <= this -> len; i++){
				c[i + j - 1] += this -> num[i] * b[j];	
			}
		}
		for(int i = 1; i <= this -> len + b.len; i++){
			c[i + 1] += c[i] / W;
			c[i] %= W;
		}
		c.len = this -> len + b.len - 1;
		while(c[ c.len + 1 ] != 0) 
			c.len++;
		return c;
	}
	int& operator[](int now){
		return this -> num[now];	
	}
	void to_int(char s[]){
		len = 0;
		int slen = strlen(s), cnt = 1, tmp = 0; int tmp1 = slen % M;	
		for(int i = slen - 1; i >= tmp1; i--){
			if(cnt > M){
				len++;
				num[len] = tmp;
				tmp = 0; cnt = 1;
			}
			tmp += (s[i] - '0') * ten[cnt++];
		}
		if(slen - 1 >= tmp1){
			len++;	
			num[len] = tmp;
		}
		tmp = 0;
		if(tmp1 != 0){
			cnt = 1;
			for(int i = tmp1 - 1; i >= 0; i--)
				tmp += (s[i] - '0') * ten[cnt++];
			len++;	
			num[len] = tmp;
		}
//		this -> len = len;
	}
	void print(){
		int buf[10], bcnt, tmp;
		printf("%d", this -> num[ this -> len ]);
		for(int i = (this -> len) - 1; i >= 1; i--){
			memset(buf + 1, 0, sizeof(int) * M);
			tmp = this -> num[i]; bcnt = 0;	
			while(tmp){
				bcnt++;
				buf[bcnt] = tmp % 10;
				tmp /= 10;
			}
			if(bcnt < M) 
				bcnt = M;
			while(bcnt) 
				putchar(buf[bcnt--] + '0');	
		}	
	}
}a, b;

char str1[N], str2[N];

int main(){
	freopen("multiplication.in", "r", stdin);
	freopen("multiplication.out", "w", stdout);
	while(scanf("%s %s", str1, str2) != EOF){
		a.to_int(str1); b.to_int(str2);
//		a.print(); printf("\n");
//		b.print(); printf("\n");
//		tmp = a * b;
		(a * b).print();
		printf("\n");
	}
}
