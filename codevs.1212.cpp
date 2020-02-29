#include <cstdio>
using namespace std;


int gcd(int n,int m){
	if(!m) return n;
	else return gcd(m,n%m);
}

int main(){
	int m,n;
	scanf("%d %d",&m,&n);
	if(m>n) printf("%d",gcd(m,n));
	else printf("%d",gcd(n,m));
}
