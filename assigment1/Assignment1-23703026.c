#include<stdio.h>
#include<stdlib.h>
#define STACKSIZE 10

struct stack {
	int top;
	int items[STACKSIZE];
};

void initialize(struct stack* p)
{
	p->top = -1;
}

int empty(struct stack* p)
{
	if (p->top == -1)
		return 1;
	else
		return 0;
}

int pop(struct stack* p)
{
	int position;
	if (empty(p))
	{
		printf("The stack is empty-underflow");
		exit(1);
	}
	position = p->top;
	p->top--;
	return (p->items[position]);
}

void push(struct stack* p, int value)
{
	if (p->top == STACKSIZE - 1)
	{
		printf("The stack is full-overflow");
		return;
	}
	++(p->top);
	p->items[p->top] = value;
	return;
}

int stacktop(struct stack* p)
{
	int TopOfStack = pop(p);
	push(p, TopOfStack);
	return TopOfStack;
}

int main()
{
	struct stack nmbrsOrdr, tempStck, cloneS, orderEntered, enterOrdered;
	int i, j, inpt, comp, inOrder;
	char option = ' ';

	while (1)
	{
		printf("\
Hello and welcome dear student.\n\
Press y to enter a new set of numbers.\n\
Press n other number to exit.\n");
		option = getchar();

		switch (option)
		{
		case 'y':
			//New set of numbers
			initialize(&nmbrsOrdr);
			initialize(&tempStck);
			initialize(&cloneS);
			initialize(&orderEntered);
			initialize(&enterOrdered);
			printf("Enter the 10 numbers. Press space or enter between each number.\n");
			for (i = 0; i < STACKSIZE; i++)
			{
				scanf("%d", &inpt);
				push(&nmbrsOrdr, inpt);
				push(&cloneS, inpt);
				push(&enterOrdered, inpt);
				printf("%d number(s) have been entered\n", i + 1);
			}
			printf("\n\n\n");
			//Checking if it's in order
			comp = pop(&nmbrsOrdr);
			inOrder = 1;
			while (!empty(&nmbrsOrdr))
			{
				if (comp >= stacktop(&nmbrsOrdr))
				{
					push(&tempStck, comp);
					comp = pop(&nmbrsOrdr);
				}
				else
				{
					inOrder = 0;
					break;
				}
			}
			if (inOrder != 0)
			{
				push(&tempStck, comp);
				printf("The numbers are in the correct order, which is:\n");
				while (!empty(&tempStck))
					printf("%d ", pop(&tempStck));
				printf("\n\n\n");
			}
			else
			{
				printf("The numbers are not ordered correctly. This is the order you entered:\n");
				while (!empty(&enterOrdered))
					push(&orderEntered, pop(&enterOrdered));
				while (!empty(&orderEntered))
					printf("%d ", pop(&orderEntered));
				push(&orderEntered, inpt);
				initialize(&nmbrsOrdr);
				for (i = 0; i < STACKSIZE - 1; i++)
				{
					comp = pop(&cloneS);
					for (j = i; j < STACKSIZE - 1; j++)
					{
						if (comp >= stacktop(&cloneS))
							push(&nmbrsOrdr, pop(&cloneS));
						else
						{
							push(&nmbrsOrdr, comp);
							comp = pop(&cloneS);
						}

					}
					push(&cloneS, comp);
					while (!empty(&nmbrsOrdr))
						push(&cloneS, pop(&nmbrsOrdr));
				}
				printf("\nAnd this is the correct order:\n");
				while (!empty(&cloneS))
					printf("%d ", pop(&cloneS));
				printf("\n\n\n");
			}
			break;
		case 'n':
			printf("Goodbye");
			exit(1);
			break;
		default:
			printf("Incorrect input. Try again:\n");
			continue;
		}//End of switch
		while (getchar() != '\n');
	}//End of while loop
	return 0;
}