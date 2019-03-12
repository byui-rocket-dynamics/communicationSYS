#include <stdio.h>

typedef struct Node
{ 
   unsigned char *data;
   Node *next;
}Node;

typedef struct LinkedList
{
   Node *pHead;
   Node *pTail;
   unsigned char lenMSB;
   unsigned char lenLSB;
}LinkedList;

void push_back(LinkedList *list, unsigned char *data)
{
   Node *temp;
   temp->data = data;
   temp->next = NULL;

   if(list->pHead == NULL)
   {
      list->pHead = temp;
      list->pTail = temp;
   }
   else if(list->pHead->next == NULL)
   {
      list->pTail = temp;
      list->pHead->next = list->pTail;
   }
   else 
   {
      
      list->pTail->next = temp;
      list->pTail = list->pTail->next;
   }
   if(list->lenLSB < 0xFF)
      list->lenLSB++;
   else 
      list->lenMSB++;
}

void push_front(LinkedList *list, unsigned char *data)
{
   Node *temp;
   temp->data = data;
   if(list->pTail == NULL && list->pTail == NULL)
   {
      list->pTail = temp;
      list->pHead = temp;
   }
   else
   {
      temp->next = list->pHead;
      list->pHead = temp;
   }
   if(list->lenLSB < 0xFF)
      list->lenLSB++;
   else 
      list->lenMSB++;
}

Node* find(struct Node *node, unsigned char *data)
{
   Node *temp;
   temp = node;
   while(temp->next != NULL)
   {
      if(temp->data = data)
         return temp;

      temp = temp->next;
   }
   return NULL;
}

void printList(LinkedList *list){
   if(list->pHead == NULL)
      return;
   Node *temp = list->pHead;
   printf("%h", temp->data);
   while(temp->next != NULL)
   {
      printf("%h", temp->data);
      temp = temp->next;
   }
}