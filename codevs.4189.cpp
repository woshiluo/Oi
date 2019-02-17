/*
作者:Woshiluo
题目:p4189 字典
*/

/*
//如何写一份可以提交的代码？以P1000 A+B为例
#include <iostream>
using namespace std;
int main()
{
    int a, b; //定义两个变量名
    cin >> a >> b; //从标准输入流中输入两个整数
    cout << a + b << endl; //输出到标准输出流中

}
// 完成程序以后，点击下方的提交，即可看到测试结果
*/
#include <cstdio>
#include <cstring>

int n, len, now, tmp, tcnt;
int trie[2000000][26];
char str[20];

inline void insert(char *str){
	len = strlen(str);	
	now = 0;
	for(int i = 0; i < len; i++){
		tmp=str[i]-'a';
		if( trie[now][tmp] == 0 ) trie[now][tmp] = ++tcnt;
		now = trie[now][tmp];
	}
}

inline bool find(char *str){
	len = strlen(str);	
	now = 0;
	for(int i = 0; i < len; i++){
		tmp = str[i] - 'a';
		if( trie[now][tmp] == 0 ) return false;
		now = trie[now][tmp];
	}
	return true;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%s", str);
		insert(str);
	}
	
	scanf("%d",&n);
	while(n--){
		scanf("%s", str);
		printf("%s\n", find(str)? "YES": "NO");
	}
}
