#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode{
    BTNode* node;
    struct _queuenode *next;
}QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space,int left);
//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode * node);
int dequeue(Queue *qPtr);
BTNode* getFront(Queue q);
int isEmptyQueue(Queue q);

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2);

int main()
{
    BTNode* root = (BTNode*) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode* node;
    enqueue(&q,root);

    int nodeV;
    char opL, opR;

    while(!isEmptyQueue(q)){
            scanf("%d %c %c",&nodeV,&opL,&opR);
            node = getFront(q);dequeue(&q);
            node->nodeV = nodeV;

            if(opL != '@'){
                node->left = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->left);
            }
            else node->left =NULL;
            if(opR != '@'){
                node->right = (BTNode*) malloc(sizeof(BTNode));
                enqueue(&q,node->right);
            }
            else
                node->right = NULL;
    }

    int v1,v2;
    scanf("%d %d",&v1,&v2);
    int cost = twoNodesCost(root,v1,v2);

    printBTNode(root,0,0);

    printf("Distance is %d\n",cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node){
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

BTNode* getFront(Queue q){
    return q.head->node;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}
void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->nodeV);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

int mkPath(Queue *q, BTNode* root, int nodeV1) {
  if (root->nodeV == nodeV1 || (root->left != NULL && mkPath(q, root->left, nodeV1)) || (root->right != NULL && mkPath(q, root->right, nodeV1))) {
    enqueue(q, root);
    return 1;
  }
  return 0;
}

int twoNodesCost(BTNode* node, int nodeV1,int nodeV2)
{
  Queue q1, q2;
  q1.head = NULL;
  q1.tail = NULL;
  q1.size = 0;
  q2.head = NULL;
  q2.tail = NULL;
  q2.size = 0;

  mkPath(&q1, node, nodeV1);
  mkPath(&q2, node, nodeV2);

  // Now we sum the bigger one till the sizes are equal (size is depth from the root).
  int res = 0;
  while (q1.size > q2.size) {
    res += getFront(q1)->nodeV;
    dequeue(&q1);
  }
  while (q2.size > q1.size) {
    res += getFront(q2)->nodeV;
    dequeue(&q2);
  }
  // Now q1 and q2 are equal. Keep adding both until we reach the LCA.
  while (getFront(q1)->nodeV != getFront(q2)->nodeV) {
    res += getFront(q1)->nodeV;
    res += getFront(q2)->nodeV;
    dequeue(&q1);
    dequeue(&q2);
  }
  // LCA is reached, so both fronts will contain the same number.
  return res + getFront(q1)->nodeV;
}
