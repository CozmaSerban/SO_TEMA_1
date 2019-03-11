#include "compare.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	char *name;
	int value;
} info;
typedef struct {
	info info;
	struct node *ptr;
} node;

void
init_queue(node **front, node **rear)
{
	(*front) = (*rear) = NULL;
}

void
insert(char *name, int priority, node **front, node **rear, node **front1,
	int *count, int *err)
{
	node *temp;
	node *aux;

	if ((*rear) == NULL) {
		(*rear) = (node *) malloc(1 * sizeof(node));
	if ((*rear) == NULL) {
		(*err) = 12;
		return;
	}
	(*rear)->info.name = (char *) malloc(2000);
	if ((*rear)->info.name == NULL) {
		(*err) = 12;
		return;
	}
	(*rear)->ptr = NULL;
	strcpy((*rear)->info.name, name);
	(*rear)->info.value = priority;
	(*front) = (*rear);
	} else {
		temp = (node *) malloc(1 * sizeof(node));
		if (temp == NULL) {
			(*err) = 12;
			return;
		}
		temp->info.name = (char *) malloc(2000);
		if (temp->info.name == NULL) {
			(*err) = 12;
			return;
		}
		temp->info.value = priority;
		strcpy(temp->info.name, name);
		if (compare(temp->info.value, (*front)->info.value) > 0) {
			temp->ptr = (*front);
			(*front) = temp;
		} else {
			(*front1) = (*front);
			while ((*front1) != NULL) {
				if (compare(temp->info.value,
					(*front1)->info.value) > 0) {
					aux->ptr = temp;
					temp->ptr = (*front1);
					break;
				}

				if ((*front1)->ptr == NULL) {
					(*front1)->ptr = temp;
					temp->ptr = NULL;
					break;
				}
				aux = (*front1);
				(*front1) = (*front1)->ptr;
			}
		}
	}
	(*count)++;
}



void
pop(node **front, node **front1, int *count, node **rear)
{
	(*front1) = (*front);
	if ((*front1) == NULL)
		return;

	if ((*front1)->ptr != NULL) {
		(*front1) = (*front1)->ptr;
		free((*front)->info.name);
		free((*front));
		(*front) = (*front1);
	} else {
		free((*front1)->info.name);
		free((*front1));
		(*front) = NULL;
		(*front1) = NULL;
		(*rear) = NULL;
	}
	(*count)--;
}


char *
top(node **front, node **rear)
{
	if (((*front) != NULL) && ((*rear) != NULL))
		return ((*front)->info.name);
	else
		return "";
}

int
words(const char *sentence)
{
	int count = 0, i, len;
	char lastC;

	len = strlen(sentence);
	if (len > 0)
		lastC = sentence[0];
	for (i = 0; i <= len; i++) {
		if ((sentence[i] == ' ' || sentence[i] == '\0') && lastC != ' ')
			count++;

		lastC = sentence[i];
	}
	return count;
}

int
main(int argc, char *argv[])
{
	int i = 0;
	char prioritate[20000], nume[20000];
	node *front, *rear, *front1;
	int count = 0;
	FILE *f;
	char line[20002];
	int err = 0;
	char nl = '\n';
	char *pch;

	init_queue(&front, &rear);
	if (argc == 1) {
		while (fgets(line, 20001, stdin) != NULL) {
			if (strstr(line, "top") != NULL &&
				strlen(line) == 4) {
				strcpy(nume, top(&front, &rear));
				if (strcmp(nume, "") != 0)
					printf("%s\n", nume);
				else
					putchar(nl);
			}
			if (strstr(line, "pop") != NULL &&
					strlen(line) == 4)
				pop(&front, &front1, &count, &rear);

			if (strstr(line, "insert") != NULL &&
					words(line) == 3) {

				strcpy(prioritate, "");
				pch = strtok(line, " ");
				while (pch != NULL) {
					strcpy(nume, prioritate);
					strcpy(prioritate, pch);
					pch = strtok(NULL, " ");
				}
				insert(nume, atoi(prioritate), &front,
						&rear, &front1, &count, &err);
				if (err == 12)
					exit(12);
			}
		}
	}

	for (i = 0; i < argc - 1; i++) {
		f = fopen(argv[i + 1], "r");
		if (f == NULL)
			continue;
		while (fgets(line, 20001, f) != NULL) {
			if (strstr(line, "top") != NULL &&
					strlen(line) == 4) {
				strcpy(nume, top(&front, &rear));
				if (strcmp(nume, "") != 0)
					printf("%s\n", nume);
				else
					putchar(nl);
			}
			if (strstr(line, "pop") != NULL &&
					strlen(line) == 4)
				pop(&front, &front1, &count, &rear);

			if (strstr(line, "insert") != NULL &&
					words(line) == 3) {

				strcpy(prioritate, "");
				pch = strtok(line, " ");
				while (pch != NULL) {
					strcpy(nume, prioritate);
					strcpy(prioritate, pch);
					pch = strtok(NULL, " ");
				}
				insert(nume, atoi(prioritate), &front,
						&rear, &front1, &count, &err);
				if (err == 12)
					exit(12);
			}
		}
		fclose(f);
	}
	front1 = front;
	while (front1 != NULL) {
		front1 = front1->ptr;
		free(front->info.name);
		free(front);
		front = front1;
	}
}
