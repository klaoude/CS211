#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

//#define DEBUG

typedef struct Stack
{
	struct Stack* next;
	int val;
} Stack;

Stack* vStack;
Stack* opStack;

void Push(Stack** p, int val)
{
	#ifdef DEBUG
	printf("	Push %d\n", val);
	#endif
	Stack* new = malloc(sizeof(Stack));
	new->val = val;
	new->next = *p;
	*p = new;
}

int Pop(Stack** p)
{
	if(*p == NULL)
		return 0;

	int ret = (*p)->val;

	Stack* old = *p;
	*p = (*p)->next;

	#ifdef DEBUG
	printf("	Pop %p : %d\n", old, ret);
	#endif

	free(old);

	return ret;
}

void Read(Stack* p)
{
	Stack* tmp = p;
	while(tmp != NULL)
	{
		#ifdef DEBUG
		printf("%d -> ", tmp->val);
		#endif
		tmp = tmp->next;
	}
	#ifdef DEBUG
	puts("");
	#endif
}

void Clear(Stack** p)
{
	Stack* tmp = *p;
	while(tmp != NULL)
		Pop(&tmp);
	*p = NULL;
}

#endif