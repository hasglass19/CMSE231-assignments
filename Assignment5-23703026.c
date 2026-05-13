#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NAMESIZE 20

struct nodetype {
	char number[NAMESIZE];
	char name[NAMESIZE];
	struct nodetype* left;
	struct nodetype* right;
};

typedef struct nodetype* NODEPTR;

NODEPTR getnode(void)
{
	NODEPTR p;
	p = (NODEPTR)malloc(sizeof(struct nodetype));
	return(p);
}

NODEPTR newBranch(char x[], char n[])
{
	NODEPTR p;
	p = getnode();
	strncpy(p->number, x, NAMESIZE - 2);
	p->number[NAMESIZE - 1] = '\0';
	strncpy(p->name, n, NAMESIZE-2);
	p->name[NAMESIZE - 1] = '\0';
	p->right = NULL;
	p->left = NULL;
	return(p);
}

void intrav(NODEPTR agac)
{
	if (agac != NULL)
	{
		intrav(agac->left);
		printf("Name: %s. Number: %s\n", agac->name, agac->number);
		intrav(agac->right);
	}
}

void revorder(NODEPTR agac)
{
	if (agac != NULL)
	{
		revorder(agac->right);
		printf("Name: %s. Number: %s\n", agac->name, agac->number);
		revorder(agac->left);
	}
}

int newFriend(NODEPTR* tree, char num[], char name[])
{
	NODEPTR q, p, v;

	q = NULL;
	p = *tree;
	while (p != NULL)
	{
		if (strcmp(name,p->name)==0)
			return 1;
		q = p;
		if (strcmp(name, p->name)<0)
			p = p->left;
		else
			p = p->right;
	}
	v = newBranch(num,name);

	if (q == NULL)
		*tree = v;
	else
		if (strcmp(name, q->name) < 0)
			q->left = v;
		else
			q->right = v;
	return 2;
}

void bSearch(NODEPTR agac,char target[])
{
	if (agac == NULL)
	{
		printf("\nFriend not in tree\n");
		return;
	}
	if (strcmp(target, agac->name) == 0)
	{
		printf("\nFriend found:\nName: %s\nNumber: %s\n", agac->name, agac->number);
		return;
	}
	if (strcmp(target, agac->name) > 0)
		bSearch(agac->right, target);
	else
		bSearch(agac->left, target);
}

int main()
{
	char choice = ' ',inName[NAMESIZE],inNum[NAMESIZE];
	NODEPTR friendTree=NULL;
	while (1)
	{
		printf("\nEnter a number to choose an option:\n\
1. Add a new friend.\n\
2. Search for a telephone number.\n\
3. List the names and phone numbers of all friends. (Ascending Order)\n\
4. List the names and phone numbers of all friends. (Descending Order)\n\
0. Exit.\n");
		scanf("%c", &choice);
		switch (choice)
		{
		case '1':
			printf("\n\nEnter the name and number:\nName: ");
			scanf("%19s", &inName);
			inName[NAMESIZE - 1] = '\0';
			printf("Number: ");
			scanf("%19s", &inNum);
			inNum[NAMESIZE - 1] = '\0';
			printf("%s", (newFriend(&friendTree, inNum, inName) == 1 ? "Friend already in tree.\n" : "Friend added.\n"));
			break;
		case '2':
			printf("\n\nEnter the friend you want to find:\n");
			scanf("%19s", &inName);
			inName[NAMESIZE - 1] = '\0';
			bSearch(friendTree, inName);
			break;
		case '3':
			printf("\n\n");
			intrav(friendTree);
			break;
		case '4':
			printf("\n\n");
			revorder(friendTree);
			break;
		case '0':
			printf("\n\nGoodbye.\n");
			exit(1);
			break;
		default:
			printf("\n\nIncorrect option chosen. Try again.\n");
			break;
		}
		printf("\n\n");
		while (getchar() != '\n');
	}
}