#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


typedef struct bst bst;

struct bst{
    int value;
    bst* leftChild;
    bst* rightChild;
};

bst* bst_find(bst* root, int value){
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    if (root->value > value){
        if (root->leftChild == NULL) return NULL;

        return bst_find(root->leftChild, value);
    }
    
    if (root->rightChild == NULL) return NULL;

    return bst_find(root->rightChild, value);
}

bst* bst_insert(bst* root, int value){
    if (root == NULL) {
        bst* new_root = malloc(sizeof(bst));
        new_root->value = value;
        new_root->leftChild = NULL;
        new_root->rightChild = NULL;

        return new_root;
    }
    if (root->value == value){
        return root;
    }
    if (root->value > value){
        if (root->leftChild == NULL) {
            root->leftChild = bst_insert(root->leftChild, value);

            return root->leftChild;
        };

        return bst_insert(root->leftChild, value);
    }
    
    if (root->rightChild == NULL) {
        root->rightChild = bst_insert(root->rightChild, value);

        return root->rightChild;
    };

    return bst_insert(root->rightChild, value);
}

bst* bst_insert_bulk(bst* root, int values[], int size){
    if (size <= 0) return root;
    int i = 0;

    root = root == NULL ? bst_insert(root, values[i++]) : root;
    while(i < size){
        bst_insert(root, values[i++]);
    }

    return root;
}

void bst_remove(bst* root, int value){
    if (root == NULL) return;

    if (root->value == value){
        if (root->leftChild == NULL && root->rightChild == NULL){
            free(root);
        }
        else if (root->leftChild == NULL && root->rightChild != NULL){
            bst* rightChild = root->rightChild;
            root->value = rightChild->value;
            root->leftChild = rightChild->leftChild;
            root->rightChild = rightChild->rightChild;

            free(rightChild);
        }
        else if (root->leftChild != NULL && root->rightChild == NULL){
            bst* leftChild = root->leftChild;
            root->value = leftChild->value;
            root->leftChild = leftChild->leftChild;
            root->rightChild = leftChild->rightChild;

            free(leftChild);
        }
        else if (root->leftChild != NULL && root->rightChild != NULL){
            bst* rightChild = root->rightChild;
            if (rightChild->leftChild == NULL) {
                root->value = rightChild->value;
                root->rightChild = rightChild->rightChild;

                free(rightChild);
            } else {
                bst* rightLeftChild = rightChild->leftChild;
                bst* prevRightLeftChild = rightChild;

                while(rightLeftChild->leftChild != NULL){
                    prevRightLeftChild = rightLeftChild;
                    rightLeftChild = rightLeftChild->leftChild;
                }
                prevRightLeftChild->leftChild = NULL;
                root->value = rightLeftChild->value;
                
                free(rightLeftChild);
            }
        }
    }
    else if (root->value > value) {
        bst* child = root->leftChild;
        if (child->value == value && child->leftChild == NULL && child->rightChild == NULL){
            root->leftChild == NULL;
        }
        
        bst_remove(child, value);
    } else {
        bst* child = root->rightChild;
        if (child->value == value && child->leftChild == NULL && child->rightChild == NULL){
            root->leftChild == NULL;
        }
        
        bst_remove(child, value);
    }
}

typedef struct LL LL;
struct LL {
    bst* data;
    LL* next;
};

LL* LL_create_node(bst* data){
    LL* list = malloc(sizeof(LL));
    list->data = data;
    list->next = NULL;

    return list;
}

typedef struct Queue Queue;
struct Queue{
    LL* head;
    LL* tail;
    int size;
    void (*push)(Queue* queue, bst* data);
    bst* (*pop)(Queue* queue);
};

void queue_push(Queue* self, bst* data){
    if (self->size == 0){
        self->head = LL_create_node(data);
        self->tail = self->head;
    } else {
        self->tail->next = LL_create_node(data);
        self->tail = self->tail->next;
    }
    self->size++;
};
bst* queue_pop(Queue* self){
    if (self->size == 0 || self->head == NULL) return NULL;

    LL* head = self->head;
    bst* data = head->data;
    self->head = head->next;
    free(head);

    if (self->size == 1) {
        self->tail = NULL;
    }
    self->size--;
    
    return data;
};

Queue* new_queue(bst* nodes[]){
    Queue* queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->push = queue_push;
    queue->pop = queue_pop;

    if (nodes != NULL){
        while(*nodes != NULL){
            queue->push(queue, *nodes);
            nodes++;
        }
    }

    return queue;
};


// breadth-first search traversal
void bst_bfs_traverse(bst* root, void (*func)(bst* node)){
    Queue* queue = new_queue((bst* []){ root, NULL });

    while(queue->size > 0){
        bst* node = queue->pop(queue);

        if (node->leftChild != NULL) queue->push(queue, node->leftChild);
        if (node->rightChild != NULL) queue->push(queue, node->rightChild);

        if (func != NULL) func(node);
    }
}

// inorder, preoder, postorder also could be infix, prefix, postfix
typedef enum TRAVERSE_TYPE{
    INORDER,
    PREORDER,
    POSTORDER
} TRAVERSE_TYPE;

// depth-first search traversal
void bst_dfs_traverse(bst* root, TRAVERSE_TYPE type, void (*func)(bst* node)){
    if (root == NULL) return;

    switch (type){
        case PREORDER:
            func(root);
            bst_dfs_traverse(root->leftChild, type, func);
            bst_dfs_traverse(root->rightChild, type, func);
            break;
        case POSTORDER:
            bst_dfs_traverse(root->leftChild, type, func);
            bst_dfs_traverse(root->rightChild, type, func);
            func(root);
            break;
        case INORDER:
        default:
            bst_dfs_traverse(root->leftChild, type, func);
            func(root);
            bst_dfs_traverse(root->rightChild, type, func);
            break;
    }
}

// TODO
// look AVL tree
void bst_balance(bst* root){};

// TODO look unix tree command
void printTree(bst* root){};

void printNode(bst* node){
    printf(" %d ", node->value);
}

void removeDuplicatedAndSort(int* arr, int arrLength){
    for (int i = 0; i < arrLength; i++){
        printf("%d ", arr[i]);
    }
    puts("");

    bst* tree = bst_insert_bulk(NULL, arr, arrLength);
    bst_dfs_traverse(tree, INORDER, printNode);
    puts("");
}

int main(void){
    int arr[] = {
        109, 108, 107, 106, 105, 104, 103, 102, 101,
        109, 108, 107, 106, 2, 104, 103, 102, 101,
        112, 95, 105, 1
    };
    int arrLength = sizeof(arr) / sizeof(int);

    removeDuplicatedAndSort(arr, arrLength);

    return 0;
}
