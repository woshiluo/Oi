#include <cstdio>
#include <cstring>
using namespace std;

int b,c,d,alen,ans;
char a[400];

int main(){
	scanf("%s".a);
	alen=strlen(a);
	for(int i=0;i<=alen;i++){
		if(a[i]=='(') b++;
		if(a[i]==')') c++;
		if(a[i]=='?') d++;
	}
}
