#include <cstdio>
using namespace std;

int main(){
	int k;
	scanf("%d",&k);
	double i=1;
	double cnt=0;
	while(cnt<k){
		double temp=1.0/i;
		cnt+=temp;
		i++;
	}
	printf("%.0lf",i-1);	
}
