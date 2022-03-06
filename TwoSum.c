#include <stdio.h>
#include "uthash.h"

#define SUM_NUM_SIZE 2

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashTable;

HashTable *hashTable;

HashTable *HashFind(int key)
{
    HashTable *item;
    HASH_FIND_INT(hashTable, &key, item);
    return item;
}

void HashInsert(int key, int val)
{
    HashTable *item = HashFind(key);
    if (item == NULL) {
        HashTable *tmpItem = (HashTable *)malloc(sizeof(HashTable));
        tmpItem->key = key;
        tmpItem->val = val;
        HASH_ADD_INT(hashTable, key, tmpItem);
    } else {
        item->val = val;
    }
}

void HashClear(void)
{  
    HashTable *currentItem;
    HashTable *tmpItem;  

    HASH_ITER(hh, hashTable, currentItem, tmpItem) {  
        HASH_DEL(hashTable,currentItem); 
        free(currentItem); 
    }
  
    HASH_CLEAR(hh, hashTable);
}  

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    hashTable = NULL;
    for (int i = 0; i < numsSize; i++) {
        HashTable *item = HashFind(target - nums[i]);
        if (item != NULL) {
            int *ret = (int *)malloc(sizeof(int) * SUM_NUM_SIZE);
            ret[0] = item->val;
            ret[1] = i;
            *returnSize = SUM_NUM_SIZE;
            HashClear();
            return ret;
        }
        HashInsert(nums[i], i);
    }

    *returnSize = 0;
    HashClear();
    return NULL;
}

int main()
{
    int nums[] = {2,7,11,15};
    int numsSize = sizeof(nums);
    int target = 18;
    int returnSize = 0;

    int *retPos = twoSum(nums, numsSize, target, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("retPos[%d] = %d \n", i, retPos[i]);
    }
}