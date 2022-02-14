#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}


void in2PreLL(char* infix, LinkedList *inExpLL)
{
  // Process the infix string into a stack first
  Stack infixRev;
  infixRev.size = 0;
  infixRev.head = NULL;

  Stack temp;
  temp.size = 0;
  temp.head = NULL;

  int i = 0;
  while (infix[i] != '\0'){
    push(&infixRev, infix[i]);
    i++;
  }

  // Now read the characters of the stack (i.e. in reverse order)
  char c;
  int currnum;
  int currplace;
  while (!isEmptyStack(infixRev)){
    char c = peek(infixRev);
    pop(&infixRev);
    if (c == ')') {
      push(&temp, c);
    } else if (c == '(') {
      while (peek(temp) != ')') {
        insertNode(inExpLL, (int)peek(temp), OPT);
        pop(&temp);
      }
      pop(&temp);
    } else if (c == '*' || c == '/') {
      push(&temp, c);
    } else if (c == '+' || c == '-') {
      while (!isEmptyStack(temp) && peek(temp) != '+' && peek(temp) != '-' && peek(temp) != ')') {
        insertNode(inExpLL, (int)peek(temp), OPT);
        pop(&temp);
      }
      push(&temp, c);
    } else {
      currnum = c - '0';
      currplace = 10;
      while (!isEmptyStack(infixRev) && peek(infixRev) != '+' && peek(infixRev) != '-' && peek(infixRev) != '*' && peek(infixRev) != '/' && peek(infixRev) != '(' && peek(infixRev) != ')'){
        currnum += (peek(infixRev) - '0') * currplace;
        currplace *= 10;
        pop(&infixRev);
      }
      insertNode(inExpLL, currnum, OPERAND);
    }
  }

  while (!isEmptyStack(temp)){
    insertNode(inExpLL, (int)peek(temp), OPT);
    pop(&temp);
  }
}
