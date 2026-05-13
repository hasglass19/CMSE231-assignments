#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define COUNTLENGTH 40

struct node
{
	char countries[COUNTLENGTH];
	struct node* next;
};

typedef struct node* NODEPTR;

NODEPTR getnode(void)
{
	NODEPTR p;
	p = (NODEPTR)malloc(sizeof(struct node));
	p->countries[0] = '\0';
	p->next = NULL;
	return(p);
}

void freenode(NODEPTR p)
{
	free(p);
}

void insertEnd(NODEPTR p,char x[])
{
	if (p == NULL)
	{
		printf("\nError: Node doesn't exist.\n");
		return;
	}
	if (p->countries[0] == '\0')
	{
		strncpy(p->countries, x, COUNTLENGTH - 1);
		p->countries[COUNTLENGTH - 1] = '\0';
		return;
	}
	NODEPTR  q = getnode();
	strncpy(q->countries, x, COUNTLENGTH - 1);
	q->countries[COUNTLENGTH - 1] = '\0';
	while (p->next != NULL)
		p = p->next;
	p->next = q;
}

void deleteNext(NODEPTR p)
{
	if (p == NULL || p->next == NULL)
		return;
	NODEPTR q;
	q = p->next;
	p->next = q->next;
	freenode(q);
}

void removeDups(NODEPTR p)
{
	if (p == NULL || p->next == NULL)
	{
		printf("\nDuplicates Removed.\n");
		return;
	}
	NODEPTR l=p, prev,crrnt;
	while (l != NULL)
	{
		prev = l;
		crrnt = l->next;
		while (crrnt != NULL)
		{
			if (strcmp(l->countries, crrnt->countries) == 0)
			{
				deleteNext(prev);
				crrnt = prev->next;
			}
			else
			{
				prev = crrnt;
				crrnt = crrnt->next;
			}
		}
		l = l->next;
	}
	printf("\nDuplicates Removed.\n");
}

void display(NODEPTR l)
{
	NODEPTR p;
	for (p = l; p != NULL; p = p->next)
	{
		printf("%s\n", p->countries);
	}
	printf("\n\n");
}

void insertCirc(NODEPTR* pq, char x[])
{
	NODEPTR p, q, l;
	p = getnode();
	strncpy(p->countries, x, COUNTLENGTH - 1);
	p->countries[COUNTLENGTH - 1] = '\0';
	if (*pq == NULL||(*pq)->next==NULL)
	{
		p->next = p;
		*pq = p;
	}
	else
	{
		q = *pq;
		for (l = (*pq)->next; l != (*pq) && strcmp(l->countries, x) < 0; l = l->next)
			q = l;
		if (l == (*pq) && strcmp(l->countries, x) < 0)
		{
			p->next = l->next;
			l->next = p;
			*pq = p;
		}
		else
		{
			p->next = q->next;
			q->next = p;
		}
	}
}

void mainToCirc(NODEPTR mainL, NODEPTR* circL)
{
	for (NODEPTR p = mainL; p != NULL; p = p->next)
		insertCirc(circL, p->countries);
}

void displayCirc(NODEPTR p,char x[])
{
	NODEPTR q = p;
	do
	{
		if (strcmp(q->countries, x) == 0)
		{
			printf("\nThe list of countries:\n");
			do
			{
				printf("%s\n", q->countries);
				q = q->next;
			} while (q != p->next);
			exit(1);
		}
		q = q->next;
	} while (q != p);
	printf("\nCountry not in the list. Try again.\n");
}

int main()
{
	NODEPTR mainLL = getnode();
	NODEPTR circLL = NULL;
	char choice='a';
	char entered[COUNTLENGTH];
	printf("Enter a country.\n");
	for (int i = 0; i < COUNTLENGTH != '\n'; i++)
	{
		scanf("%c", &entered[i]);
		if (entered[i] == '\n')
		{
			entered[i] = '\0';
			break;
		}
	}
	insertEnd(mainLL, entered);
	while (choice != '0')
	{
		printf("\nPress 1 to enter another country.\nPress 2 to display the current list.\nPress 3 to finalise and order the countries.\nPress 0 to exit.\n");
		scanf("%c", &choice);
		while (getchar() != '\n');
		switch (choice)
		{
		case '1':
			printf("\nEnter a country:\n");
			for (int i = 0; i < COUNTLENGTH != '\n'; i++)
			{
				scanf("%c", &entered[i]);
				if (entered[i] == '\n')
				{
					entered[i] = '\0';
					break;
				}
			}
			insertEnd(mainLL, entered);
			break;
		case '2':
			printf("\n\n");
			display(mainLL);
			break;
		case '3':
			removeDups(mainLL);
			mainToCirc(mainLL, &circLL);
			while (1)
			{
				printf("\nEnter the starting country:\n");
				for (int i = 0; i < COUNTLENGTH != '\n'; i++)
				{
					scanf("%c", &entered[i]);
					if (entered[i] == '\n')
					{
						entered[i] = '\0';
						break;
					}
				}
				displayCirc(circLL, entered);
			}
			break;
		case '0':
			exit(1);
		default:
			printf("\nIncorrect choice entered. Try again.\n");
			break;
		}
	}
	return 0;
}