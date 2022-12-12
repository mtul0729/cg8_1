#include <stdio.h>
#include "stdlib.h"
struct num_info {
    int num;
    unsigned int times;
    _Bool latest;
};
typedef struct num_info num_info;

int main() {
    unsigned int N;
    scanf("%u", &N);
    num_info number[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d",&number[i].num);
    }
    for(int i=0;i<N;i++){
        number[i].times=1;
        number[i].latest=1;
        for(int j=i-1;j>=0;j--){
            if(number[j].num==number[i].num){
                number[j].times+=number[i].times;
                number[i].latest=0;
                number[j].latest=1;
                break;
            }
        }
    }
    num_info *most_p=number,*end_p=number+N;//打擂台找出现次数*最多*的数字（只找第一个）
    for (int i = 0; i < N; ++i) {
        if(number[i].latest&&number[i].times>most_p->times){
            most_p=number+i;
        } 
    }
    unsigned int most_times = most_p->times;
    //下面用链表(头插入法）记录并排序
    struct node{
        num_info * num_p; //记录number的地址
        struct node * next;
    };
    typedef struct node node_t;
    //创建链表并初始化;
    node_t *num;
    num = (node_t *)malloc(sizeof(node_t));
    if(num==NULL)return -1;//若内存分配失败则结束程序
    num->num_p=most_p;
    num->next=NULL;
    //接着记录
    for(most_p++;most_p<=end_p;most_p++){
        while(most_p->times==most_times){
            node_t *p;
            p=(node_t *) malloc(sizeof (node_t));//申请新节点
            if(p==NULL)return -1;//若内存分配失败则结束程序
            p->num_p=most_p;
            p->next=num->next;
            num->next=p;
        }
    }
    //TODO然后排序
    return 0;
}
