#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

std::string bn;

int n,cnt;
std::map <std::string,int> a;

int main(){
	freopen("az.in","r",stdin);
	freopen("az.out","w",stdout); 
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		std::cin >> bn;
		std::sort(bn.begin(),bn.end());
		if(a[bn]==0) cnt++,a[bn]=1;
	}
	printf("%d",cnt);
	fclose(stdin);
	fclose(stdout);
}

