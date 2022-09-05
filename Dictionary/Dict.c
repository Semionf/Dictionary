#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable:4996)

void add(int, int);
struct Dictionary* search(int);
void removeNode(int);
void deleteList();

typedef struct Dictionary {
	int key; 
	int value;
	struct Dictionary* next;
	struct Dictionary* prev;
}Dictionary;

Dictionary* head, * tail;

int main()
{
	int key, value;
	char ch = 0;
	while (ch != 'Q')
	{
		printf("Press 1 for add, 2 for Search, 3 for remove, Q to quit: \n");
		ch = getch();
		switch (ch)
		{
		case '1':
			printf("Enter Key and Value: ");
			scanf("%d%d", &key, &value);
			add(key, value);
			break;
		case '2':
		{
			Dictionary* temp;
			printf("Enter a key to Search for a value: ");
			scanf("%d", &key);
			temp = search(key);
			if (!temp)
			{
				break;
			}
			printf("Value is %d\n", temp->value);
		}
		break;
		case '3':
		{
			printf("Enter key to delete: ");
			scanf("%d", &key);
			removeNode(key);
			break;
		}
		case 'Q':
			break;
		default:
			printf("Wrong input.\n");
			break;
		}
	}
	deleteList();
}

void add(int key, int value)
{
	Dictionary* sub = (Dictionary*)malloc(sizeof(Dictionary));
	Dictionary* curr = head;
	sub->key = key;
	sub->value = value;
	sub->next = sub->prev = NULL;
	if (!head)
	{
		head = tail = sub;
	}
	else {
		while (curr)
		{
			if (curr->key == key)
			{
				curr->value = sub->value;
				free(sub);
				return;
			}
			curr = curr->next;
		}
		tail->next = sub;
		sub->prev = tail;
		sub->next = NULL;
		tail = sub;
		return;
	}
}

struct Dictionary* search(int key)
{
	Dictionary* curr = head;
	if (!curr)
	{
		printf("Dictionary is empty.\n");
		return NULL;
	}
	while (curr)
	{
		if (curr->key == key)
		{
			return curr;
		}
		curr = curr->next;
	}
	printf("No such key.\n");
	return NULL;
}

void removeNode(int key)
{
	Dictionary* curr = head;
	Dictionary* node = search(key); //345
	if (!node)
	{
		return;
	}
	if (!node->prev && !node->next)
	{
		free(node);
		head = tail = NULL;
		return;
	}
	else if (!node->next)
	{
		tail = tail->prev;
		tail->next = NULL;
		free(node);
		return;
	}
	else if (!node->prev)
	{
		head = head->next;
		head->prev = NULL;
		free(node);
		return;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
		return;
	}
}

void deleteList()
{
	Dictionary* curr = head;
	while (head)
	{
		curr = head;
		head = head->next;
		free(curr);
	}
}