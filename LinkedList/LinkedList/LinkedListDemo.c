#include <stdlib.h>
#include <stdio.h>


typedef int bool;
#define true 1
#define false 0
/*Declare struct of linked list*/
typedef struct Node
{
	int data;   //data type in linked list
	struct Node* pNext;   //next node of linked list
} NODE, *pNode;  //NODE == struct Node  //PNODE == struct Node*


/*Function Declare*/
int getNum(void);  //
pNode createList(void);//
void traverseList(pNode pHead);//
bool isEmpty(pNode pHead);//
int length(pNode pHead);//
bool insertNode(pNode pHead, int position, int value);
bool deleteNode(pNode pHead, int position, int* deleteValue);
void sortLinkedList(pNode pHead); //

int main()
{
	pNode pHead = NULL;
	int deleteValue = 0;
	pHead = createList(); //no loop single linked list and return head node to pHead
	printf(".......................Original Linked List.....................\n");
	traverseList(pHead);
	if (isEmpty(pHead))
	{
		printf("Linked list is empty\n");
	}
	else
	{
		printf("Linked list is not empty\n");
	}
	int len = length(pHead);

	printf("Length is %d\n", len);
	sortLinkedList(pHead);
	printf(".........................Sort Linked List.......................\n");
	traverseList(pHead);

	insertNode(pHead, 2, 10000);
	printf(".........................Insert 10000 into Linked List.......................\n");
	traverseList(pHead);
	

	if (deleteNode(pHead, 2, &deleteValue))
	{
		printf(".........................Delete 10000 from Linked List.......................\n");
		traverseList(pHead);
	}
	else
	{
		printf(".....................Delete 10000 failed.......................\n");
	}
	return 0;
}

int getNum(void)
{
	char record[121] = { 0 }; /* record stores the string */
	int number = 0;
	fgets(record, 121, stdin);
	if (sscanf_s(record, "%d", &number) != 1)
	{
		number = -1;
	}
	return number;
}
pNode createList(void)
{
	int len;  //linked list length
	int val;  //tmp store user input node value

	pNode pHead = (pNode)malloc(sizeof(NODE));

	if (NULL == pHead)
	{
		printf("Malloc memory failed...\n");
		exit(-1);
	}
	pNode pTail = pHead;
	pTail->pNext = NULL;   //pTail will point to tail node forever (if user input 0, so this line will work for that)


	printf("please input node account to create a linked list: ");   //node account
	len = getNum();
	while (len == -1)
	{
		printf("Please input valid number again: ");
		len = getNum();
	}
	
	//scanf("%d", &len);  //no validation for int code

	for (int i = 0; i < len; i++)   //
	{
		printf("please input No.%d node value: ", i + 1);
		//scanf("%d", &val);
		val = getNum();
		while (val == -1)
		{
			printf("Please input valid number again: ");
			val = getNum();
		}
		pNode pNew = (pNode)malloc(sizeof(NODE));
		if (NULL == pNew)
		{
			printf("Malloc memory failed...\n");
			exit(-1);
		}

		pNew->data = val;
		pTail->pNext = pNew;
		pNew->pNext = NULL;
		pTail = pNew;
	}
	return pHead;
}

void traverseList(pNode pHead)
{
	pNode pTmp = pHead->pNext;
	int num = 1;
	while (pTmp != NULL)
	{
		printf("No.%d node is %d\n", num, pTmp->data);
		pTmp = pTmp->pNext;
		num++;
	}

	return;
}

bool isEmpty(pNode pHead)
{
	if (NULL == pHead->pNext)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int length(pNode pHead)
{
	pNode pTmp = pHead->pNext;
	int len = 0;
	while (NULL != pTmp)
	{
		len++;
		pTmp = pTmp->pNext;
	}

	return len;
}


void sortLinkedList(pNode pHead)
{
	int i, j, t, len;
	pNode p, q;
	len = length(pHead);
	for (i = 0, p = pHead->pNext; i < len - 1; i++, p = p->pNext)
	{
		for (j = i + 1, q = p->pNext; j < len; j++, q = q->pNext)
		{
			if (p->data > q->data)
			{
				t = p->data;
				p->data = q->data;
				q->data = t;
			}
		}
	}
	return;
}


bool insertNode(pNode pHead, int position, int value)
{
	int i = 0;
	pNode p = pHead;
	while (NULL != p && i < position - 1)
	{
		p = p->pNext;
		i++;
	}

	if (i > position || NULL == p)
	{
		printf("Not valid position for linked list...\n");
		return false;
	}
	pNode pNew = (pNode)malloc(sizeof(NODE));

	if (NULL == pNew)
	{
		printf("Malloc memory failed!\n");
		exit(-1);
	}

	pNew->data = value;
	pNode q = p->pNext;
	p->pNext = pNew;
	pNew->pNext = q;

	return true;
}


bool deleteNode(pNode pHead, int position, int* deleteValue)  //this deleteValue can save into local variable and user can use it after delete it from linked list
{
	int i = 0;
	pNode p = pHead;
	while (NULL != p->pNext && i < position - 1)
	{
		p = p->pNext;
		i++;
	}

	if (i > position - 1 || NULL == p->pNext)
	{
		printf("Not valid position for linked list...\n");
		return false;
	}

	pNode q = p->pNext;
	*deleteValue = q->data;

	p->pNext = p->pNext->pNext;
	free(q);
	q = NULL;

	return true;
}