#include <cstdio>
#include <cstring>

const int N = 5e5 + 1e4; 

int len_s, len_t, cnt_0, cnt_1, tmp_0, tmp_1; 
int s0[N], s1[N], next[N];
char s[N], t[N]; 

void get_next(int len){
    next[1] = 0; 
    for(int i = 2, j = 0; i <= len; ++i){
        while(j && t[i] != t[j + 1])
            j = next[j]; 
        if(t[i] == t[j + 1])
            ++j; 
        next[i] = j; 
    }
}

int main(){
    scanf("%s", s + 1); 
	scanf("%s", t + 1); 
    len_s = strlen(s + 1); 
    len_t = strlen(t + 1); 
    for(int i = 1; i <= len_s; ++i){
        s0[i] = s0[i-1] + (s[i] == '0'); 
        s1[i] = s1[i-1] + (s[i] == '1'); 
    }
    cnt_0 = s0[len_s]; 
    cnt_1 = s1[len_s]; 
    get_next(len_t); 
    tmp_0  =  tmp_1  =  0; 
    for(int i = 1; i <= next[len_t]; ++i)
        if(t[i] == '0')
            ++tmp_0; 
        else
            ++tmp_1; 
    if(!(cnt_0 >= tmp_0 && cnt_1 >= tmp_1)){
        printf("%s", s + 1); 
        return 0; 
    }
    cnt_0 -= tmp_0; 
    cnt_1 -= tmp_1; 
    for(int i = 1; i <= next[len_t]; ++i)
        printf("%c", t[i]); 
    tmp_0 = tmp_1 = 0; 
    for(int i = next[len_t] + 1; i <= len_t; ++i)
        if(t[i] == '0')
            ++tmp_0; 
        else
            ++tmp_1; 
    while(cnt_0 >= tmp_0 && cnt_1 >= tmp_1){
        for(int i = next[len_t] + 1; i <= len_t; ++i)
            printf("%c", t[i]); 
        cnt_0 -= tmp_0; 
        cnt_1 -= tmp_1; 
    }
    for(int i = 1; i <= cnt_0; ++i)
        printf("0"); 
    for(int i = 1; i <= cnt_1; ++i)
        printf("1"); 
    return 0; 
}
