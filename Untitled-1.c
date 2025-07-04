#include <stdlib.h>
#include <math.h>
#include <stdio.h>
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
    TWN *curr = start -> next;
    while(curr != start){
        TWN *tmp = curr;
        curr = curr -> next;
        free(tmp);
    }
    free(start);
    free(list);
}
TWN *ctwl_insert_right(CTWL* list, float val){

    TWN* node = (TWN *)malloc(sizeof(TWN));
    if(!node)
    return NULL;

    node -> data = val;

    if(!list -> cur){
        node -> next = node;
        node -> prev = node;
        list -> cur = node;
    }
    else{
         TWN *next = list -> cur -> next;
        list -> cur -> next = node;
        node -> prev = list -> cur;
        node -> next = next;
        next -> prev = node;
    }
}

void ctwl_print(CTWL *list){
    if(!list || !list -> cur){
        printf("list prazdny\n");
        return;
    }
    TWN *start = list -> cur;
    TWN *temp = start;
    do{
        if(temp == list -> cur)
            printf("[%g]", temp -> data);
        else
            printf("%g ", temp -> data);
        temp = temp -> next;
    }while(temp != start);
    printf("\n");
}

CTWL *ctwl_get_affine_sublist(CTWL *list, unsigned int len, unsigned int step){
    if(!list || !list -> cur || len == 0 || step == 0)
    return NULL;

    TWN *current = list -> cur;
    float prev = current -> data;

    current = current -> next;
    for(unsigned int i = 1; i < step; i++)
current = current -> next;

    float diff = current -> data - prev;
    prev = current -> data;
    
    TWN *temp = current;
    for(unsigned int i = 2; i < len; i++){
        for(unsigned int s = 0; s < step; s++)
            temp = temp -> next;

        float cur_diff = temp -> data - prev;
        if(fabs(cur_diff - diff) > 1e-6)
            return NULL;
            prev = temp -> data;
    }
    CTWL *result = ctwl_create_empty();
    if(!result)
    return NULL;

    current = list -> cur;
    for(unsigned int i = 0; i < len; i++){
        ctwl_insert_right(result, current -> data);
        for(unsigned int j = 0; j <step; j++)
            current = current -> next;
    }
    return result;
} 
int main(){
    CTWL *list = ctwl_create_empty();
    ctwl_insert_right(list, 2);
    ctwl_insert_right(list, 4);
    ctwl_insert_right(list, 6);
    ctwl_insert_right(list, 8);
    ctwl_insert_right(list, 10);
    ctwl_insert_right(list, 12);
    printf("orig: ");
    ctwl_print(list);
    CTWL * affine = ctwl_get_affine_sublist(list, 5, 3);
    if(affine){
        printf("affine sublist");
        ctwl_print(affine);
        ctwl_destroy(affine);
    }
    else{
        printf("nie je affine sublist");

    }
    ctwl_destroy(list);
    return 0;
    
}