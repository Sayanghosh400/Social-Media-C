#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "mylinkedlist.h"
int main()
{
          struct node *head = NULL;
          int choice;
          while (1)
          {
                    printf("Press 1 to insert\nPress 2 to display the user names\nPress 3 to display any of the user's friendlist\n");
                    scanf("%d",&choice);
                    switch (choice)
                    {
                    case 1:
                              insert(&head);
                              break;
                    case 2:
                              display(head);
                              break;
                    case 3:
                              displayfriends(head);
                              break;
                    default:
                              printf("Wrong Input\n");
                              break;
                    }
          }
}