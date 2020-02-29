#include <cstdio>
using namespace std;

int cnt;

void f(int n){
	cnt++;
	for(int i=1;i<=n/2;i++){
		f(i);
	}
}

int main(){
	int n;
	scanf("%d",&n);
	f(n);
	printf("%d",cnt);
}
