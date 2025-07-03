#include <stdlib.h>
#include <math.h>
#define CTWL_OK 1 
#define CTWL_FAIL 0
typedef struct TWN {
    float data;
    struct TWN *prev;
    struct TWN *next;
} TWN;

typedef struct CTWL {
    TWN *cur;
} CTWL;

CTWL *ctwl_create_empty(void){
    CTWL *list = malloc(sizeof(CTWL));
    if(!list)
    return NULL;

    list -> cur = NULL;
    return list;
}

void ctwl_destroy(CTWL *list){
    if(!list || !list -> cur){
        free(list);
        return;
    }
    TWN *start = list -> cur;
    TWN *tmp = start -> next;
    while(tmp != start){
        TWN *next = tmp -> next;
        free(tmp);
        tmp = next;
    }
    free(start);
    free(list);
}

CTWL *ctwl_get_affine_sublist(CTWL *list, unsigned int len, unsigned int step){
    if(!list || !list -> cur || len == 0 || step == 0)
    return NULL;

    TWN **nodes = (TWN **)malloc(len * sizeof(TWN *));
    if(!nodes)
    return NULL;

    TWN *cursor = list -> cur;
    nodes[0] = cursor;

    for(unsigned int i = 1; i < len; i++){
        for(unsigned int s = 0; s < step; s++){
            cursor = cursor -> next;
            if(!cursor){
                free(nodes);
                return NULL;
            }
        }
        nodes[i] = cursor;
    }
    float diff = nodes[1] -> data - nodes[0] -> data;
    for(unsigned int i = 2; i < len; i++){
        float cur_diff = nodes[i] -> data - nodes[i - 1] -> data;
        if(fabs(cur_diff - diff) > 1e-6){
            free(nodes);
            return NULL;
        }
    } 
    
}