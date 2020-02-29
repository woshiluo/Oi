#include <cstdio>
#include <cstring>

typedef unsigned __int128 int128;

const int N = 3e5 + 1e3;

int128 readin(){
	char ch = getchar();
	while(ch > '9' && ch <'0') 
		ch = getchar();
	int128 tmp = (int128)0;
	while(ch <= '9' && ch >= '0'){
		tmp *= (int128)10;
		tmp += (int128)(ch - '0');
		ch = getchar();
	}
	while(ch != '\n')
		ch = getchar();
	return tmp;
}

int buff[90], buff_cnt;
void writeout(int128 a, bool h = true){
	buff_cnt = (int128)0;
	while(a){
		buff[++buff_cnt] = (int)(a % (int128)10);
		a /= (int128)10;
	}	
	while(buff_cnt){
		putchar('0' + buff[buff_cnt]);
		buff_cnt--;
	}
	if(h) printf("\n");
	return ;
}

int128 n, e, k, len, T;
char str[N];

int128 ksm(int128 a, int128 p){
	int128 res = (int128)1;
	while(p){
		if(p & (int128)1) 
			res = (res * a) % n;
		a = (a * a) % n;
		p >>= (int128)1;
	}
	return res;
}


int main(){
#ifdef woshiluo
	freopen("B.in", "r", stdin);
	freopen("B.out", "w" , stdout);
#endif
	n = readin();
	e = readin();
	k = readin();
	fgets(str + 1, (int)(N - 1), stdin);
	len = strlen(str + (int128)1);
	if(str[len] == '\n') 
		len--;
	if(str[len] == '\r')
		len--;
	T = len / (k - (int128)2) + (len % (k - (int128)2) != (int128)0);	
	writeout(T);
	for(int128 i = (int128)1, base, tmp; i <= T; i++){
		base = (i - (int128)1) * (k - (int128)2);
		tmp = (int128)0;
		for(int128 j = (int128)1; j <= (k - (int128)2); j++){
			if(j + base > len) break;
			tmp <<= (int128)8;
			tmp |= (int128)str[j + base];
		}
		writeout(ksm(tmp, e));
	}
	return 0;
}
