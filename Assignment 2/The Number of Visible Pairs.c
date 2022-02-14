#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode
{
    int  item;
	struct _dbllistnode *next;
	struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist{
   int size;
   CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main()
{
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i,cases;
    int numP;
    scanf("%d",&cases);
    for(i=0; i<cases; i++)
    {
        while(scanf("%d",&item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n",numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value){
      //create a new node
      CDblListNode* newNode;
      newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
      newNode->item = value;

      if(ptrCDLL->size==0) //first node
      {
          newNode->next = newNode;
          newNode->pre = newNode;
          ptrCDLL->head = newNode;
      }
      else{
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
      }
      ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL){

    if(CDLL.head==NULL) return;

    CDblListNode* temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head){
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n",temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL){
    if(ptrCDLL->head==NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next!= ptrCDLL->head) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }

    free(cur);
    ptrCDLL->head =NULL;
    ptrCDLL->size =0;

}

int numMountainPairs(CDblLinkedList CDLL)
{
  int result = 0;
  int *visible = (int *)calloc(CDLL.size - 1, sizeof(int));

  CDblListNode *a = CDLL.head;
  CDblListNode *b;
  int maxbetween;
  int anum, bnum;
  for (int i = 0; i < CDLL.size; i++) {
    anum = a->item;
    // Forward
    maxbetween = 0;
    b = a->next;
    for (int j = 0; j < CDLL.size - 1; j++) {
      bnum = b->item;
      if ((anum < bnum ? anum : bnum) >= maxbetween) visible[j] = 1;
      maxbetween = maxbetween < bnum ? bnum : maxbetween;
      b = b->next;
    }
    // Backward
    maxbetween = 0;
    b = a->pre;
    for (int j = CDLL.size - 2; j > -1; j--) {
      bnum = b->item;
      if (visible[j] == 0 && (anum < bnum ? anum : bnum) >= maxbetween) visible[j] = 1;
      maxbetween = maxbetween < bnum ? bnum : maxbetween;
      b = b->pre;
    }
    // Go through and collate the results
    for (int j = 0; j < CDLL.size - 1; j++) {
      if (visible[j] == 1) {
        result++;
        visible[j] = 0;
      }
    }
    a = a->next;
  }

  free(visible);

  // We double counted (one each where each mountain was A)
  return result / 2;
}
