#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

int n;
std::string a[30];

bool cmp(std::string a,std::string b){
	return a+b>b+a;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) std::cin >> a[i];
	std::sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) std::cout << a[i];
}
