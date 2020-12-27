#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stablo* poz;
struct stablo
{
	char el[50];
	poz child;
	poz sibling;
};

typedef struct STOG* pozicija;
struct STOG
{
	poz clan;
	pozicija next;
};

int mdNOVO(poz, char*);
poz cdNOVO(poz, char*);
int dirNOVO(poz);
int cddirNOVO(poz, char*);
poz tockecdNOVO(poz, char*);
int push(pozicija, poz);
poz pop(pozicija);

int main()
{
	struct stablo head;
	strcpy(head.el, "C:\\");
	head.child = NULL;
	head.sibling = NULL;
	poz temp = &head;

	char prvi[50];
	char drugi[50];
	char treci[50];
	char* buffer = (char*)malloc(1024);
	int br = 0;
	do
	{
		printf("MENU: md, cd, cd dir, cd.., dir, izlaz\n");
		fgets(buffer, 1024, stdin);
		br = sscanf(buffer, "%s %s %s", prvi, drugi, treci);

		if (br == 1)
		{
			if (strcmp(prvi, "dir") == 0)
				dirNOVO(&head);
		}
		else if (br == 2)
		{
			if (strcmp(prvi, "md") == 0)
				mdNOVO(temp, drugi);
			else if (strcmp(prvi, "cd..") == 0)
			{
				temp = tockecdNOVO(&head, drugi);
				printf("%s \n", temp->el);
			}
			else if (strcmp(prvi, "cd") == 0)
			{
				temp = cdNOVO(&head, drugi);
				printf("%s \n", temp->el);
			}
		}
		else if (br == 3)
		{
			if (strcmp(prvi, "cd") == 0 && strcmp(drugi, "dir") == 0)
			{
				cddirNOVO(&head, treci);
			}
		}
	} while (strcmp(prvi, "izlaz") != 0);

	return 0;
}

int mdNOVO(poz p, char* ime)
{
	poz temp = (poz)malloc(sizeof(struct stablo));
	temp->child = NULL;
	temp->sibling = NULL;
	strcpy(temp->el, ime);

	if (p->child == NULL)
		p->child = temp;
	else
	{
		poz dijete = p->child;
		while (dijete->sibling != NULL)
			dijete = dijete->sibling;
		dijete->sibling = temp;
	}

	return 0;
}

int dirNOVO(poz p)
{
	printf("%s \n", p->el);
	p = p->child;
	while (p != NULL)
	{
		printf("\t %s \n", p->el);
		poz q = p->child;
		while (q != NULL)
		{
			printf("\t\t %s \n", q->el);
			q = q->sibling;
		}
		p = p->sibling;
	}

	return 0;
}
poz cdNOVO(poz p, char* ime)
{
	if (strcmp(p->el, ime) == 0)
		return p;
	else
	{
		p = p->child;
		while (p != NULL)
		{
			if (strcmp(p->el, ime) == 0)
				return p;
			else
			{
				poz q = p->child;
				while (q != NULL)
				{
					if (strcmp(q->el, ime) == 0)
						return q;
					else
						q = q->sibling;
				}
				p = p->sibling;
			}
		}
		printf("Greska! Ne postoji trazeni direktorij!\n");
		return NULL;
	}
}

int cddirNOVO(poz p, char* ime)
{
	poz temp = cdNOVO(p, ime);
	dirNOVO(temp);

	return 0;
}

poz tockecdNOVO(poz p, char* ime)
{

	struct STOG stog;
	stog.next = NULL;

	if (strcmp(p->el, ime) == 0)
		printf("Greska! Ne postoji parent direktorij!\n");

	push(&stog, p);

	if (p->child == NULL)
		printf("Greska! Ne postoje direktoriji!\n");
	else
	{
		p = p->child;
		poz pocetak = p;
		while (p != NULL)
		{
			if (strcmp(p->el, ime) == 0)
				return pop(&stog);
			else
				p = p->sibling;
		}
		while (pocetak != NULL)
		{
			if (pocetak->child != NULL)
			{
				push(&stog, pocetak);
				poz q = pocetak->child;
				while (q != NULL)
				{
					if (strcmp(q->el, ime) == 0)
						return pop(&stog);
					else
						q = q->sibling;
				}
				pocetak = pocetak->sibling;
			}
			else
				pocetak = pocetak->sibling;
		}
	}
}

poz pop(pozicija p)
{
	pozicija q;
	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		return q->clan;
		free(q);
	}
	return 0;
}

int push(pozicija p, poz c)
{
	pozicija q = (pozicija)malloc(sizeof(struct STOG));
	q->clan = c;
	q->next = p->next;
	p->next = q;

	return 0;
}