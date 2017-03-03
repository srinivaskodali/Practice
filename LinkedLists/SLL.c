#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next;
} *head;

void append(int num)
{
	struct node *temp, *right;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	right = (struct node *)head;
	while (right->next != NULL)
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = NULL;
}

void add(int num)
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	if (head == NULL) {
		head = temp;
		head->next = NULL;
	} else {
		temp->next = head;
		head = temp;
	}
}

void addafter(int num, int loc)
{
	int i;
	struct node *temp, *left, *right;
	right = head;
	for (i = 1; i < loc; i++) {
		left = right;
		right = right->next;
	}
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	left->next = temp;
	left = temp;
	left->next = right;
	return;
}

void insert(int num)
{
	int c = 0;
	struct node *temp;
	temp = head;
	if (temp == NULL) {
		add(num);
	} else {
		while (temp != NULL) {
			if (temp->data < num)
				c++;
			temp = temp->next;
		}
		if (c == 0)
			add(num);
		else if (c < count())
			addafter(num, ++c);
		else
			append(num);
	}
}

int delete(int num)
{
	struct node *temp, *prev;
	temp = head;
	while (temp != NULL) {
		if (temp->data == num) {
			if (temp == head) {
				head = temp->next;
				free(temp);
				return 1;
			} else {
				prev->next = temp->next;
				free(temp);
				return 1;
			}
		} else {
			prev = temp;
			temp = temp->next;
		}
	}
	return 0;
}

void display(struct node *r)
{
	if (r == NULL) {
		return;
	}
	while (r != NULL) {
		printf("%d ", r->data);
		r = r->next;
	}
	printf("\n");
}

void deleteall()
{
	struct node *temp;
	while (head != NULL) {
		temp = head;
		head = temp->next;
		free(temp);
	}
	return;
}

int count()
{
	struct node *n;
	int c = 0;
	n = head;
	while (n != NULL) {
		n = n->next;
		c++;
	}
	return c;
}

void printreverse(struct node *temp)
{

	if (temp->next == NULL) {
		printf("%d ", temp->data);
		return;
	}
	printreverse(temp->next);
	printf("%d ", temp->data);

}

void reverselist(struct node **head_ref)
{
	struct node *prev = NULL;
	struct node *current = *head_ref;
	struct node *next;
	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

void recursiveReverse(struct node** head_ref)
{
    struct node* first;
    struct node* rest;
      
    /* empty list */
    if (*head_ref == NULL)
       return;   
 
    /* suppose first = {1, 2, 3}, rest = {2, 3} */
    first = *head_ref;  
	printf("first is %p\n", (void *)first);
    rest  = first->next;
	printf("rest is %p\n", (void *)rest);
	printf("\n");
 
    /* List has only one node */
    if (rest == NULL)
       return;   
 
    /* reverse the rest list and put the first element at the end */
    recursiveReverse(&rest);
	printf("Before first is %p\n", (void *)first);
	printf("Before first->next->next is %p\n", (void *)first->next->next);
    first->next->next  = first;  
	printf("after first is %p\n", (void *)first);
	printf("after first->next->next is %p\n", (void *)first->next->next);
     
    /* tricky step -- see the diagram */
	printf("before first->next is %p\n", (void *)first->next);
    first->next  = NULL;          
	printf("after first->next is %p\n", (void *)first->next);
     
 
    /* fix the head pointer */
	printf("before head is %p\n", (void *)*head_ref);
    *head_ref = rest;              
	printf("after head is %p\n", (void *)head_ref);
	printf("\n");
}
int main()
{
	int i, num;
	struct node *n;
	head = NULL;
	printf("size of node is %d\n", sizeof(struct node));
	while (1) {
		printf("\nList Operations\n");
		printf("===============\n");
		printf("1.Insert\n");
		printf("2.Display\n");
		printf("3.Size\n");
		printf("4.Delete\n");
		printf("5.Print reverse\n");
		printf("6.Reverse list using traditional method\n");
		printf("7.Reverse list using recursive method\n");
		printf("8.Exit\n");
		printf("Enter your choice : ");
		if (scanf("%d", &i) <= 0) {
			printf("Enter only an Integer\n");
			exit(0);
		} else {
			switch (i) {
			case 1:
				printf("Enter the number to insert : ");
				scanf("%d", &num);
				insert(num);
				break;
			case 2:
				if (head == NULL) {
					printf("List is Empty\n");
				} else {
					printf("Element(s) in the list are : ");
				}
				display(head);
				break;
			case 3:
				printf("Size of the list is %d\n", count());
				break;
			case 4:
				if (head == NULL)
					printf("List is Empty\n");
				else {
					printf("Enter the number to delete : ");
					scanf("%d", &num);
					if (delete(num))
						printf("%d deleted successfully\n", num);
					else
						printf("%d not found in the list\n", num);
				}
				break;
			case 8:
				if (head == NULL)
					printf("List is Empty\n");
				else {
					deleteall();
				}

				return 0;
			case 5:
				if (head == NULL)
					printf("List is Empty\n");
				else {
					printreverse(head);
					printf("\n");
				}
				break;
			case 6:
				reverselist(&head);
				break;

			case 7:
				recursiveReverse(&head);
				break;
			default:
				printf("Invalid option\n");
			}
		}
	}
	return 0;
}
