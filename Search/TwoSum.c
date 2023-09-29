#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

/*
    如果数组中两个元素相加等于target
*/
int *twoSumBruteForce(int *array, int len, int target, int *retSize) {
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (array[i] + array[j] == target) {
                int *ret = malloc(sizeof(int) * 2);
                ret[0] = i;
                ret[1] = j;
                *retSize = 2;

                return ret;
            }
        }
    }

    return NULL;
}

/* 哈希表 */
struct hashTable {
    int key;
    int val;
    UT_hash_handle hh; // 基于 uthash.h 实现
};

typedef struct hashTable hashTable;

/* 哈希表查询 */
hashTable *find(hashTable *head, int key) {
    hashTable *findRet = NULL;
    HASH_FIND_INT(head, &key, findRet);

    return findRet;
}

/* 哈希表元素插入 */
void insert(hashTable **head, int key, int value) {
    hashTable *findRet = NULL;
    HASH_FIND_INT(*head, &key, findRet);

    if (!findRet) {
        hashTable *newNode = malloc(sizeof(*newNode));
        newNode->key = key;
        newNode->val = value;
        HASH_ADD_INT(*head, key, newNode);
    } else {
        findRet->val = value;
    }

    return ;
}


/* 方法二：辅助哈希表 */
int *twoSumHashTable(int *array, int numsSize, int target, int *returnSize) {
    hashTable *head = NULL;
    for (int i = 0; i < numsSize; i++) {
        hashTable *findRet = find(head, target - array[i]);

        if (findRet) {
            int *ret = malloc(sizeof(int) * 2);
            ret[0] = i;
            ret[1] = findRet->val;
            *returnSize = 2;

            return ret;
        }
        insert(&head, array[i], i);
    }

    return NULL;
}


int main() {
    int array[] = {12, 34, 78, 56, 23, 99, 39, 38, 98, 45, 76, 99};
    int len = sizeof(array) / sizeof(int);
    int target = 137;

    int retSize = 0;
    int *ret = NULL;

    ret = twoSumBruteForce(array, len, target, &retSize);

    if (retSize != 0) {
        printf("index: %d, %d\n", ret[0], ret[1]);
        printf("value: %d, %d = %d\n", array[ret[0]], array[ret[1]], array[ret[0]] + array[ret[1]]);
    } else {
        printf("search failed\n");
    }
    putchar('\n');

    if (!ret)
        free(ret);
    ret = NULL;

    ret = twoSumHashTable(array, len, target, &retSize);

    if (ret != NULL) {
        printf("index: %d, %d\n", ret[0], ret[1]);
        printf("value: %d, %d = %d\n", array[ret[0]], array[ret[1]], array[ret[0]] + array[ret[1]]);
    } else {
        printf("search failed\n");
    }

    if (!ret)
        free(ret);

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include "uthash.h"

// typedef struct my_struct {
//     int key;            /* we'll use this field as the key */
//     int value;
//     UT_hash_handle hh; /* makes this structure hashable */
// }HashNode;

// int count_user(HashNode* head);

// HashNode *find_user(HashNode *head, int user_id) {
//     HashNode *s;
//     HASH_FIND_INT(head, &user_id, s);  /* s: output pointer */
//     return s;
// }
// void add_user(HashNode **head, HashNode *node) {
//     if(!find_user(*head, node->key))
//         HASH_ADD_INT(*head, key, node);
// }
// void print_user(HashNode *head) {
//     HashNode *s;
//     printf("size is %d\n", count_user(head));
//     for (s = head; s != NULL; s = s->hh.next) {
//         printf("user id %d, name %d\n", s->key, s->value);
//     }
// }
// int count_user(HashNode *head) {
//     return HASH_COUNT(head);
// }
// int main()
// {
//     HashNode *head = NULL;
//     int array[] = {12, 34, 78, 56, 23, 99, 39, 38, 98, 45, 76, 99};
//     int len = sizeof(array) / sizeof(int);

//     for (int i = 0; i < len; i++) {
//         HashNode *node = malloc(sizeof(HashNode));
//         node->key = array[i];
//         node->value = i;
//         add_user(&head, node);
//     }

//     print_user(head);


//     return 0;
// }

