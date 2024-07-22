#include<stdio.h>
#include<malloc.h>
#include<string.h>
struct node
{
	int closeness;
	char name[50];
          char hometown[50];
          char school[50];
          char college[50];
	struct node *link;
	struct node *prev;
	struct node *down;
};
int cmpstr(char str1[], char str2[])
{
	int flag = 1;
	for (int i = 0; i < strlen(str2); i++)
	{
		if (str1[i] != str2[i])
		{
			flag = 0;
			break;
		}
	}
	return flag;
}
void valstr(char str1[], char str2[])
{
	for (int i = 0; i < strlen(str2); i++)
	{ 
		str1[i] = str2[i];
	}
	return;
}
struct node* create()
{
	struct node *d;
	d = (struct node *)malloc(sizeof(struct node));
	printf("Enter name\n");
	scanf("%s",d->name);
	printf("Enter hometown\n");
	scanf("%s",d->hometown);
	printf("Enter school name\n");
	scanf("%s",d->school);
	printf("Enter college name\n");
	scanf("%s",d->college);
	d->closeness = 3;
	d->link = NULL;
	d->prev = NULL;
	d->down = NULL;
	return d;
}
struct node * createmain(char Name[],char School[],char College[],char Hometown[])
{
	struct node *d;
	d = (struct node *)malloc(sizeof(struct node));
	valstr(d->name,Name);
	valstr(d->college,College);
	valstr(d->school,School);
	valstr(d->hometown,Hometown);
	d->closeness = 3;
	d->link = NULL;
	d->prev = NULL;
	d->down = NULL;
	return d;
}
int checkclose(struct node *Head,struct node *N)
{
	int flag;
	struct node *temp = Head;
	struct node *t = N;
	if (Head)
	{
		flag = cmpstr(temp->school,t->school);
		if (flag == 0)
		{
			t->closeness--;
		}
		flag = cmpstr(temp->college,t->college);
		if (flag == 0)
		{
			t->closeness--;
		}
		flag = cmpstr(temp->hometown,t->hometown);
		if (flag == 0)
		{
			t->closeness--;
		}
	}
	return t->closeness;
}
void insertmain(struct node **Head,struct node *N)
{
	struct node *temp;
	struct node *t = *Head;
	struct node *n;
	if(*Head == NULL)
	{
		*Head = N;
	}
	else
	{
		n = createmain(N->name,N->school,N->college,N->hometown);
		temp = *Head;
		while (temp->down)
		{
			temp = temp->down;
		}
		temp->down = n;
		n->link = createmain(t->name,t->school,t->college,t->hometown);
		n->link->closeness = n->closeness;
	}
}
void insertend(struct node **Head,struct node *n)
{
	struct node *temp;
	temp = *Head;
	while (temp->link != NULL)
	{
		temp = temp->link;
	}
	temp->link = n;
	n->prev = temp;
	insertmain(Head,n);
}
void insertmiddle(struct node **Head,struct node *n)
{
	struct node *temp,*N;
	if (*Head)
	{
		N = n;
		temp = *Head;
		while (temp != NULL)
		{
			if(N->closeness >= temp->closeness)
			{
				break;
			}
			temp = temp->link;
		}
		if(temp == NULL)
		{
			insertend(Head,n);
		}
		else
		{
			N->prev = temp->prev;
			temp->prev->link = N;
			N->link = temp;
			temp->prev = N;
			insertmain(Head,n);
		}
	}
}
void insert(struct node **Head)
{
	struct node *temp = *Head;
	struct node *t = *Head;
	struct node *n;
	n = create();
	while (temp)
	{
		n->closeness = checkclose(temp,n);
		if (n->closeness == 3 || n->closeness == 2 || n->closeness == 1)
		{
			break;
		}
		n->closeness = 3;
		temp = temp->down;
	}
	if (temp == NULL)
	{
		insertmain(Head,n);
	}
	else if (n->closeness == 3)
	{
		if (t->link)
		{
			n->link = t->link;
			t->link->prev = n;
			n->prev = t;
			t->link = n;
			insertmain(Head,n);
		}
		else
		{
			insertend(Head,n);
		}
	}
	else
	{
		insertmiddle(Head,n);
	}
	
}
void display(struct node *Head)
{
	struct node *temp = Head;
	struct node *p;
	if(Head == NULL)
	{
		printf("Nothing is present in your list\n");
	}
	else
	{
		printf("Here is your list\n");
		while(temp)
		{
			printf("%s\n",temp->name);
			temp = temp->down;
		}
	}
}
void displayfriends(struct node *Head)
{
	int flag;
	char n[50];
	struct node *temp;
	struct node *p;
	if(Head == NULL)
	{
		printf("Nothing is present in your list\n");
	}
	else
	{
		temp = Head;
		printf("Enter the name you want to search\n");
		scanf("%s",n);
		while(temp)
		{
			flag = cmpstr(temp->name,n);
			if (flag = 1)
			{
				break;
			}
			temp = temp->down;
		}
		if(temp)
		{
			if(temp->link)
			{
				printf("Here are the friends of %s\n",n);
				temp = temp->link;
				while(temp)
				{
					printf("%s\n",temp->name);
					temp = temp->link;
				}                                                                                                                                                                            
			}
			else
			{
				printf("No friends found for %s\n",temp->name);
			}
		}
		else
		{
			printf("No result found for %s\n",n);
		}
		
	}
}