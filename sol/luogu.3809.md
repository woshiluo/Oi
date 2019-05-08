## SA 后缀数组入门 -- Luogu  P3809 【模板】后缀排序

> 题目链接: <https://www.luogu.org/problemnew/show/P3809>

### 后缀数组

后缀数组用于解决各种玄学字符串问题，准确来说，它是一种思想

基于后缀数组有很多好玩~~毒瘤~~的东西

目前已知的求后缀数组的方法有

- 倍增法 (本博客所讲述) -- $O(n \log(n))$
- DC3 -- $O(n)$
- - DC3 虽然从复杂度分析的角度而言比倍增快，但配合各种常数问题，在信息学竞赛中反而容易被卡……
- SA - IS  算法 -- $O(n)$ 
- - 可以参考这篇 Luogu 日报: https://www.luogu.org/blog/ShadowassIIXVIIIIV/on-hou-zhui-shuo-zu-sa-is-suan-fa

因为我太菜了，所以我就讲倍增求法

### 倍增求后缀数组

与其说倍增求后缀数组，倒不如说是 倍增 + 基数排序 求后缀数组

我们先从归并排序讲起

#### 基数排序

基数排序，用于给形如 $(a, b)$ 的二元组排序（$a$ 为第一关键字，$b$ 为第二关键字）

可以做到在近似 $O(n)$ 的复杂度完成

通过灵活的运用基数排序，可以比绝大多数的排序算法更加优秀

因此也被用来在快速排序模板中占领效率 rk1

#### 倍增的用处

我们发现如果我们直接暴力求倍增数组，重复的前缀被计算了多次

如果我们一开设长度为 $1$ 字串为一个单位，排完序后设长度为二为一个单位，我们就会发现这个可以基数排序

之后设长度为 $4$ 为一个单位，依然可以基数排序，以此类推，便可以做到后缀排序

这个过程，也就是倍增

倍增 $O(\log(n))$

基数排序 $O(n)$ 

套起来 $O(n \log(n))$ 

### 代码

```cpp
#include <cstdio>
#include <cstring>

const int N = 1e6 + 1e5;

int len, Max_char;
int sa[N], tp[N], rank[N], rank_cnt[N];
char str[N];
// Max_char 基数排序最大项
// sa[i] 如上文所述
// tp[i] 第二关键字
// rank[ sa[i] ] = i 从第 i 个字母开始的排名
// rand_cnt[i] 统计 rank 的和，基数排序用

// 基数排序
void sort(){
    memset(rank_cnt, 0, sizeof(rank_cnt));
    // 统计 rank_cnt
    for(int i = 1; i <= len; i++)
        rank_cnt[ rank[i] ] ++;
    // 前缀
    for(int i = 1; i <= Max_char; i++)
        rank_cnt[i] += rank_cnt[i - 1];
    // 计算出 sa
    for(int i = len; i > 0; i--)
        sa[ rank_cnt[ rank[ tp[i] ] ] -- ] = tp[i];	
}

void get_sa(){
    Max_char = 'z' - '0' + 2;
    // 长度为 1 的预处理
    for(int i = 1; i <= len; i++){
        rank[i] = str[i] - '0' + 1;
        tp[i] = i;
    }
    sort();
    // 倍增
    for(int l = 1, tmp_cnt; tmp_cnt < len; l <<= 1, Max_char = tmp_cnt){
        tmp_cnt = 0;
        // 处理第二关键字
        for(int i = 1; i <= l; i++)
            tp[ ++ tmp_cnt ] = len - l + i;
        for(int i = 1; i <= len; i++){
            if( sa[i] > l )
                tp[ ++ tmp_cnt ] = sa[i] - l;
        }
        sort();
        
        memcpy(tp, rank, sizeof(rank));
        rank[ sa[1] ] = tmp_cnt = 1;
        for(int i = 2; i <= len; i++){
            // 判断重复（判断一个二元组）
            rank[ sa[i] ] = ( tp[ sa[i] ] == tp[ sa[i - 1] ] && tp[ sa[i] + l ] == tp[ sa[i - 1] + l ]) ? tmp_cnt: ++ tmp_cnt;
        }
    }
}

int main(){
    scanf("%s", str + 1);
    len = strlen(str + 1);
    
    get_sa();

    // 输出
    for(int i = 1; i <= len; i++)
        printf("%d ", sa[i]);
}
```



