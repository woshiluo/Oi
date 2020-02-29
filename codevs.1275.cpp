#include <cstdio>
using namespace std;

int temp;

int jue(int n){
	if(n>=0) return n;
	else return -n;
}

int main(){
	int a,b,c,d;
	scanf("%d %d %d %d",&a,&b,&c,&d);
	if(a==b&&b==c&&c==d) printf("Fish At Constant Depth");
	else if(a>b&&b>c&&c>d) printf("Fish Diving");
	else if(a<b&&b<c&&c<d) printf("Fish Rising");
	else printf("No Fish");
}
