#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

const int N=1000005;
char s[N]; int n;

const int op[]={
	1,2,0,1,0,0,0,2,2,0,0,0,1,0,2,1
};
int ans[N];

int main(){
	freopen("key.in","r",stdin);
	freopen("key.out","w",stdout);
	scanf("%s",s+1); n=strlen(s+1)/3; for (int i=1;i<=3*n;i++) s[i]-='0';
	for (int i=0;i<n;i++){
		int t=(s[3*i]<<3)+(s[3*i+1]<<2)+(s[3*i+2]<<1)+(s[3*i+3]<<0);
		if (op[t]){
			ans[++*ans]=3*i+op[t];
			s[3*i+op[t]]^=1,s[3*i+op[t]+1]^=1;
		}
	}
	printf("%d\n",*ans);
	for (int i=1;i<=*ans;i++)
		printf("%d ",ans[i]);
	return 0;
}
