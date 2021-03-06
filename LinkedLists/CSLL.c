#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next;
} *head;

/* Function to remove loop. Used by detectAndRemoveLoop() */
void removeLoop(struct node *, struct node *);
 
/* This function detects and removes loop in the list
  If loop was there in the list then it returns 1,
  otherwise returns 0 */
int detectAndRemoveLoop(struct node *list)
{
    struct node  *slow_p = list, *fast_p = list;
 
    while (slow_p && fast_p && fast_p->next)
    {
        slow_p = slow_p->next;
        fast_p  = fast_p->next->next;
 
        /* If slow_p and fast_p meet at some point then there
           is a loop */
        if (slow_p == fast_p)
        {
            removeLoop(slow_p, list);
 
            /* Return 1 to indicate that loop is found */
            return 1;
        }
    }
 
    /* Return 0 to indeciate that ther is no loop*/
    return 0;
}
 
/* Function to remove loop.
 loop_node --> Pointer to one of the loop nodes
 head -->  Pointer to the start node of the linked list */
void removeLoop(struct node *loop_node, struct node *head)
{
   struct node *ptr1;
   struct node *ptr2;
 
   /* Set a pointer to the beging of the Linked List and
      move it one by one to find the first node which is
      part of the Linked List */
   ptr1 = head;
   while (1)
   {
     /* Now start a pointer from loop_node and check if it ever
       reaches ptr2 */
     ptr2 = loop_node;
     while (ptr2->next != loop_node && ptr2->next != ptr1)
         ptr2 = ptr2->next;
 
     /* If ptr2 reahced ptr1 then there is a loop. So break the
        loop */
     if (ptr2->next == ptr1)
        break;
 
     /* If ptr2 did't reach ptr1 then try the next node after ptr1 */
     ptr1 = ptr1->next;
   }
 
   /* After the end of loop ptr2 is the last node of the loop. So
     make next of ptr2 as NULL */
   ptr2->next = NULL;
}

void append(int num)
{
	struct node *temp, *right;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	right = (struct node *)head;
	while (right->next != head)
		right = right->next;
	right->next = temp;
	right = temp;
	right->next = head;
}

void add(int num)
{
	struct node *temp, *left;
	int cnt, i;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->data = num;
	if (head == NULL) {
		head = temp;
		head->next = head;
	} else {

		cnt = count();
		left = head;
		for(i=1; i<cnt;i++){
			left = left->next;
		}
		temp->next = head;
		head = temp;
		left->next = head;
	}
	printf ("in add head is %p, next is %p\n",head,head->next);
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
		do {
			if (temp->data < num)
				c++;
			temp = temp->next;
		printf ("head is %p, temp is %p\n",head,temp);
		}while (temp != head);
		if (c == 0) {
			printf("Adding number\n");
			add(num);
		}
		else if (c < count()) {
			printf("Adding after %d location\n", c);
			addafter(num, ++c);
		} 
		else {
			printf("Appending number\n");
			append(num);
		}
	}
}

int delete(int num)
{
	struct node *temp, *prev,*left;
	int cnt,i;
	temp = head;
	if(!head)
		return 1;
	do {
		if (temp->data == num) {
			if (temp == head) {

					cnt = count();
					left = head;
					for(i=1; i<cnt;i++){
							left = left->next;
					}

				head = temp->next;
				left->next = head;
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
	} while (temp != head);
	return 0;
}

void display(struct node *r)
{
	if (r == NULL) {
		return;
	}
	do {
		printf("%d ", r->data);
		r = r->next;
	}while (r != head);
	printf("\n");
}

void deleteall()
{
	struct node *temp, *dummy_head;


	if (head == NULL) {
		return;
	}
	dummy_head= head;
	do {
		temp = head;
		head = temp->next;
		printf ("head is %p, temp is %p\n",head,temp);
		free(temp);
	}while (head != dummy_head);
	head = NULL;
	return;
}

int count()
{
	struct node *n;
	int c = 0;
	n = head;
	do {
		n = n->next;
		c++;
	}while (n != head);
	return c;
}

void printreverse(struct node *temp)
{

	if (temp->next == head) {
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
		printf("6.Find and remove loop\n");
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
				detectAndRemoveLoop(head);
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
