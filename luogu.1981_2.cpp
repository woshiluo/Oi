#include <cstdio>
using namespace std;

int n;
char b;


int jf(int temp){
    scanf("%d",&n);
    scanf("%c",&b);
    if(b=='+') jf(temp+n);
    if(b=='*') {
        if(temp==0) temp=1;
        jf(temp*n);
    }
    if(b=='\n') return temp;
}
int main(){
    printf("%d",jf(0));

}
