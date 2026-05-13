#include<stdio.h>
#include<stdlib.h>
#define MAXQUEUE 10
#define NAMELENGHT 41

struct queue
{
	char customer[MAXQUEUE+1][NAMELENGHT];
	int front, rear;
};

void queueInit(struct queue* q)
{
	q->front = MAXQUEUE;
	q->rear = MAXQUEUE;
}

int full(struct queue* q)
{
	if ((q->rear % MAXQUEUE == q->front) || (q->rear + 1 == q->front))
		return 1;
	else return 0;
}

int empty(struct queue* q)
{
	return((q->front == q->rear) ? 1 : 0);
}

void remove(struct queue* q)
{
	if (empty(q))
		return;
	if (q->front == MAXQUEUE)
		q->front = 0;
	else (q->front)++;
	printf("%s\n", q->customer[q->front]);
	return;
}

void insert(struct queue* q, char* newCus)
{
	if (full(q))
		return;
	if (q->rear == MAXQUEUE)
		q->rear = 0;
	else (q->rear)++;
	for (int i = 0; i < NAMELENGHT; i++)
	{
		q->customer[q->rear][i] = *(newCus + i);
		if (q->customer[q->rear][i] == '\n')
		{
			q->customer[q->rear][i] = '\0';
			break;
		}
	}
	return;
}

void currentQueue(struct queue q)
{
	if (empty(&q))
	{
		printf("Queue is currently empty.\n");
		return;
	}
	int waiting = (q.rear >= q.front ? q.rear - q.front : MAXQUEUE + 1 - q.front + q.rear);
	printf("%d customers currently in line:\n", waiting);
	for (int i = 1; i <= waiting; i++)
	{
		printf("%d: ", i);
		remove(&q);
	}
	return;
}

int main()
{
	int choice,loopnum;
	struct queue cypBank;
	queueInit(&cypBank);
	do
	{
		int waiting = (cypBank.rear >= cypBank.front ? cypBank.rear - cypBank.front : MAXQUEUE + 1 - cypBank.front + cypBank.rear);
		printf("Enter a number to make your choice:\n1: Customer Entrance.\n2: Customer Exit.\n3: Pending Customers.\n0: Exit.\n");
		scanf("%d", &choice);
		printf("\n\n\n");
		switch (choice)
		{
		case 1:
			char custName[NAMELENGHT];
			if (full(&cypBank))
			{
				printf("Queue is full. No customers can be added.\n");
				break;
			}
			printf("Enter the number of customers entering:\n");
			scanf("%d", &loopnum);
			if (loopnum > MAXQUEUE - waiting)
			{
				printf("Not enough space in queue. Try again with less people.");
				break;
			}
			while (getchar() != '\n');
			for (int i = 0; i < loopnum; i++)
			{
				printf("Enter the name of your customer (40 character limit)\n");
				for (int i = 0; i < NAMELENGHT - 1; i++)
				{
					scanf("%c", &custName[i]);
					if (custName[i] == '\n')
						break;
				}
				custName[NAMELENGHT - 1] = '\n';
				insert(&cypBank, custName);
				if (full(&cypBank))
				{
					printf("Queue is full. No more customers can be added.\n");
					break;
				}
			}
			break;
		case 2:
			if (empty(&cypBank))
			{
				printf("Queue is empty. No customers can be removed.\n");
				break;
			}
			printf("Enter the number of customers leaving:\n");
			scanf("%d", &loopnum);
			if (loopnum > waiting)
			{
				printf("Not enough people in queue. Try again with less people.");
				break;
			}
			for (int i = 0; i < loopnum; i++)
			{
				printf("Next customer: ");
				remove(&cypBank);
				if (empty(&cypBank))
				{
					printf("Queue is empty. No more customers can be removed.\n");
					break;
				}
			}
			break;
		case 3:
			currentQueue(cypBank);
			break;
		case 0:
			printf("Goodbye.");
			exit(1);
			break;
		default:
			printf("Unavailable option chosen, please try again.");
			break;
		}
		printf("\n\n\n");
	} while (choice != 0);
	return 0;
}