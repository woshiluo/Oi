#include <cstdio>
using namespace std;

double a;

int main(){
	scanf("%lf",&a);
	double cnt=2,temp=2;
	int i=1;
	while(cnt<a){
		temp*=0.98;
		cnt+=temp;
		i++;
	}
	printf("%d",i);
}
