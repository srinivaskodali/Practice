#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int data;
	int key;

	struct node *next;
	struct node *prev;
};

//this link always point to first Link
struct node *head = NULL;

//this link always point to last Link 
struct node *last = NULL;

struct node *current = NULL;

//is list empty
bool isEmpty()
{
	return head == NULL;
}

int length()
{
	int length = 0;
	struct node *current;

	for (current = head; current != NULL; current = current->next) {
		length++;
	}

	return length;
}

//display the list in from first to last
void displayForward()
{

	//start from the beginning
	struct node *ptr = head;

	//navigate till the end of the list
	printf("\n[ ");

	while (ptr != NULL) {
		printf("(%d,%d) ", ptr->key, ptr->data);
		ptr = ptr->next;
	}

	printf(" ]");
}

//display the list from last to first
void displayBackward()
{

	//start from the last
	struct node *ptr = last;

	//navigate till the start of the list
	printf("\n[ ");

	while (ptr != NULL) {

		//print data
		printf("(%d,%d) ", ptr->key, ptr->data);

		//move to next item
		ptr = ptr->prev;
		printf(" ");
	}

	printf(" ]");
}

//insert link at the first location
void insertFirst(int key, int data)
{

	//create a link
	struct node *link = (struct node *)malloc(sizeof(struct node));
	link->key = key;
	link->data = data;

	if (isEmpty()) {
		//make it the last link
		last = link;
	} else {
		//update first prev link
		head->prev = link;
	}

	//point it to old first link
	link->next = head;

	//point first to new first link
	head = link;
}

//insert link at the last location
void insertLast(int key, int data)
{

	//create a link
	struct node *link = (struct node *)malloc(sizeof(struct node));
	link->key = key;
	link->data = data;

	if (isEmpty()) {
		//make it the last link
		last = link;
	} else {
		//make link a new last link
		last->next = link;

		//mark old last node as prev of new link
		link->prev = last;
	}

	//point last to new last node
	last = link;
}

//delete first item
struct node *deleteFirst()
{

	//save reference to first link
	struct node *tempLink = head;

	//if only one link
	if (head->next == NULL) {
		last = NULL;
	} else {
		head->next->prev = NULL;
	}

	head = head->next;
	//return the deleted link
	return tempLink;
}

//delete link at the last location

struct node *deleteLast()
{
	//save reference to last link
	struct node *tempLink = last;

	//if only one link
	if (head->next == NULL) {
		head = NULL;
	} else {
		last->prev->next = NULL;
	}

	last = last->prev;

	//return the deleted link
	return tempLink;
}

//delete a link with given key

struct node *delete(int key)
{

	//start from the first link
	struct node *current = head;
	struct node *previous = NULL;

	//if list is empty
	if (head == NULL) {
		return NULL;
	}
	//navigate through list
	while (current->key != key) {
		//if it is last node

		if (current->next == NULL) {
			return NULL;
		} else {
			//store reference to current link
			previous = current;

			//move to next link
			current = current->next;
		}
	}

	//found a match, update the link
	if (current == head) {
		//change first to point to next link
		head = head->next;
	} else {
		//bypass the current link
		current->prev->next = current->next;
	}

	if (current == last) {
		//change last to point to prev link
		last = current->prev;
	} else {
		current->next->prev = current->prev;
	}

	return current;
}

bool insertAfter(int key, int newKey, int data)
{
	//start from the first link
	struct node *current = head;

	//if list is empty
	if (head == NULL) {
		return false;
	}
	//navigate through list
	while (current->key != key) {

		//if it is last node
		if (current->next == NULL) {
			return false;
		} else {
			//move to next link
			current = current->next;
		}
	}

	//create a link
	struct node *newLink = (struct node *)malloc(sizeof(struct node));
	newLink->key = newKey;
	newLink->data = data;

	if (current == last) {
		newLink->next = NULL;
		last = newLink;
	} else {
		newLink->next = current->next;
		current->next->prev = newLink;
	}

	newLink->prev = current;
	current->next = newLink;
	return true;
}

#if 1
void insert(int key, int num)
{
	int c = 0;
	struct node *temp;
	temp = head;
	int oldkey;
	if (temp == NULL) {
		insertFirst(key, num);
	} else {
		while (temp != NULL) {
			if (temp->key < key) {
				oldkey = temp->key;
				c++;
			}
			temp = temp->next;
		}
		if (c == 0)
			insertFirst(key, num);
		else if (c < length())
			insertAfter(oldkey, key, num);
		else
			insertLast(key, num);
	}
}
#endif
main()
{
#if 1
	int i, num, key;
	struct node *n;
	head = NULL;
	while (1) {
		printf("\nList Operations\n");
		printf("===============\n");
		printf("1.Insert\n");
		printf("2.Display\n");
		printf("3.Size\n");
		printf("4.Delete\n");
		printf("5.Print reverse\n");
		printf("6.Exit\n");
		printf("Enter your choice : ");
		if (scanf("%d", &i) <= 0) {
			printf("Enter only an Integer\n");
			exit(0);
		} else {
			switch (i) {
			case 1:
				printf("Enter the key to insert : ");
				scanf("%d", &key);
				printf("Enter the number to insert : ");
				scanf("%d", &num);
				insert(key, num);
				break;
			case 2:
				if (head == NULL) {
					printf("List is Empty\n");
				} else {
					printf("Element(s) in the list are : ");
				}
				displayForward();
				break;
			case 3:
				printf("Size of the list is %d\n", length());
				break;
			case 4:
				if (head == NULL)
					printf("List is Empty\n");
				else {
					printf("Enter the key to delete : ");
					scanf("%d", &num);
					if (delete(num))
						printf
						    ("%d deleted successfully\n",
						     num);
					else
						printf
						    ("%d not found in the list\n",
						     num);
				}
				break;
			case 6:
				if (head == NULL)
					printf("List is Empty\n");
				else {
//                                      deleteall();
				}

				return 0;
			case 5:
				if (head == NULL)
					printf("List is Empty\n");
				else {
					displayBackward();
					printf("\n");
				}
				break;
			default:
				printf("Invalid option\n");
			}
		}
	}
	return 0;
#endif
#if 0
	insert(1, 10);
	insert(3, 30);
	insert(4, 1);
	insert(6, 56);
	insert(2, 20);
	insert(5, 40);

	printf("\nList (First to Last): ");
	displayForward();

	printf("\n");
	printf("\nList (Last to first): ");
	displayBackward();

	printf("\nList , after deleting first record: ");
	deleteFirst();
	displayForward();

	printf("\nList , after deleting last record: ");
	deleteLast();
	displayForward();

	printf("\nList , insert after key(4) : ");
	insertAfter(4, 7, 13);
	displayForward();

	printf("\nList  , after delete key(4) : ");
	delete(4);
	displayForward();
#endif
}
