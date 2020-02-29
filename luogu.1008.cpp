#include <cstdio>
#include <cstring>
using namespace std;

int main(){
	for(int i=300;i<=999;i++){
		int g,s,b,a[10];
		memset(a,0,sizeof(a));
		g=i%10;
		s=i%100-g;
		b=i/100;
		s/=10;
		if(g==s||s==b||g==b) continue;
		if(i%3!=0) continue;
		a[g]++;a[s]++;a[b]++;
		if(g==0||s==0||b==0) continue;
		int temp=i/3;
		g=temp%10;
		s=(temp%100-g)/10;
		b=temp/100;
		a[g]++;a[s]++;a[b]++;		
		if(g==0||s==0||b==0) continue;
		int temp2=temp*2;
		g=temp2%10;
		s=temp2%100-g;
		b=temp2/100;
		s/=10;
		a[g]++;a[s]++;a[b]++;
		if(g==0||s==0||b==0) continue;
		bool x=true;
		for(int i=1;i<10;i++) {if(a[i]>=2) x=false;}
		if(x) printf("%d %d %d\n",temp,temp2,i);
	}
	return 0;
}
