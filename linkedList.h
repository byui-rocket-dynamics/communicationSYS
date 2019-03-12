struct Node
{
   unsigned char *data;
   struct Node *next;
};

struct LinkedList
{
   Node *pHead;
   Node *pTail;
   unsigned char lenMSB;
   unsigned char lenLSB;
};

void push_back(struct LinkedList *list, unsigned char *data)
{
   Node *temp;
   temp->data = data;
   temp->next = nullptr;

   if(list->pHead == nullptr)
   {
      list->pHead = temp;
      list->pTail = temp;
   }
   else if(list->pHead->next == nullptr)
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

void push_front(struct LinkedList *list, unsigned char *data)
{
   Node *temp;
   temp->data = data;
   if(list->pTail == nullptr && list->pTail == nullptr)
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

struct Node* find(struct Node *node, unsigned char *data)
{
   Node *temp;
   temp = node;
   while(temp->next != nullptr)
   {
      if(temp->data = data)
         return temp;

      temp = temp->next;
   }
   return nullptr;
}