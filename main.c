#include <stdio.h>

struct num_info {
    int num; //数值，将从标准输入获得
    unsigned int times;//用于记录出现次数
    _Bool latest; //在相等的数字中，该数字是否排在最后
};
typedef struct num_info num_info;

int main() {
    unsigned int N;
    scanf("%u", &N);
    num_info number[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &((number+i)->num));
    }
    for (int i = 0; i < N; i++) {
        number[i].times = 1;
        number[i].latest = 1;
        for (int j = i - 1; j >= 0; j--) {
            if (number[j].num == number[i].num) {
                number[i].times += number[j].times;
                number[i].latest = 1;
                number[j].latest = 0;
                break;
            }
        }
    }
    num_info *p[N], *most = number, *end_p = number + N - 1;//打擂台找出现次数*最多*的数字（只找第一个）
    for (p[0] = number + 1; p[0] <= end_p; p[0]++) {
        if (p[0]->latest && p[0]->times > most->times) {
            most = p[0];
        }
    }
    /*
     * 把出现次数最多的各个数字的地址放在指针数组里
     */
    p[0]=most;
    int cnt=1;
    while (most<=end_p){
        most++;
        if(most->times==p[0]->times){
            p[cnt]=most;
            cnt++;
        }
    }
    //然后冒泡排序
    for (int i = 0; i < cnt-1; ++i) {
        for (int j = 0; j < cnt-i-1; ++j) {
            if(p[j]->num > p[j+1]->num){
                num_info * tmp;
                tmp=p[j];
                p[j]=p[j+1];
                p[j+1]=tmp;
            }
        }
    }
    //输出
    void print_num(num_info*);
    for (int i = 0; i < cnt; ++i) {
        print_num(p[i]);
    }

    return 0;
}
void print_num(num_info *p){
    printf("%d %u\n",p->num,p->times);
}