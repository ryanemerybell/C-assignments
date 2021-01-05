//Ryan Bell - 11/6/16
//PID: 3605342
//NID: ry049745
//COP3502 Sean Szumlanski
//KindredSpirits Code

#include "KindredSpirits.h"
#include <stdio.h>
#include <stdlib.h>

//For a linked list. i thought "pack" sounded cool, and node is already taken
typedef struct pack
{
    int data;
    struct pack *next;
}pack;



//-----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------| Helper Functions |-----------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------


//I stole this helper function from the test cases :^). I gave it a new name as well
node *new_node(int data)
{
	node *n = malloc(sizeof(node));
	//I added this in to make sure the malloc call worked
	if (n == NULL)
        return NULL;

	n->data = data;
	n->left = n->right = NULL;

	return n;
}

pack *new_pack(int data)
{
    //Same thing as new_node but for my pack-struct
    pack *n = malloc(sizeof(pack));
	if (n == NULL)
        return NULL;

	n->data = data;
	n->next = NULL;

	return n;
}

//Note: In the following 3 functions, my head pointer is being passed by reference. This is
//so that the address of the pack that head points to can be manipulated regardless of
//where i am recursively. The return type of these functions aren't too necessary;
//they exist only for returning NULL when an error/base case occurs

//Also: my traversals will be written into my linked list backwards, like a stack
//this is convenient as it avoids the issue of maintaining a tail pointer, and
//comparing two traversals that are backwards are identical to comparing them forwards
pack *headInsert(pack **head, int data)
{
    //head is the top of my "stack"

    //a NULL double pointer should never be passed to this function
    //but, return NULL just in case, to avoid a seg fault
    if(head == NULL)
        return NULL;

    //If the linked list is empty, start one
    if (*head == NULL)
    {
        *head = new_pack(data);
        return *head;
    }

    //make a new pack with the data passed
    pack *p = new_pack(data);

    //this is similar to "push", the new node points to the current head,
    //and then the head changes to that new node. hence, head insertion
    p->next = *head;
    (*head) = p;

    return *head;
}

pack *preorder(node *root, pack **head)
{
    //preorder = MLR

    //base case
    if (root == NULL)
        return NULL;

    //head is the top of my "stack"
    //recursive calls, insert the middle, then left, right
    headInsert(head, root->data);
    preorder(root->left, head);
    preorder(root->right, head);

    return *head;
}

pack *postorder(node *root, pack **head)
{
    //postorder = LRM

    //base case
    if (root == NULL)
        return NULL;

    //head is the top of my "stack"
    //recursive calls, left, right, and then insert the middle
    postorder(root->left, head);
    postorder(root->right, head);
    headInsert(head, root->data);

    return *head;
}

int listCmp(pack *a, pack *b)
{
    //Returns 1 if lists are identical, 0 otherwise

    //traverses each list until either pack becomes null
    while (a != NULL && b != NULL)
    {
        //if at any point the data at two congruent positions
        //in each list do NOT equal, then the lists are not identical
        if(a->data != b->data)
            return 0;

        a = a->next;
        b = b->next;
    }

    //If at the end of traversing, if one pack is null and the other isn't,
    //then the lists are not the same length and therefore cannot be identical
    if(a == NULL && b != NULL)
        return 0;
    if(a != NULL && b == NULL)
        return 0;

    //note that if there is no proof that the lists aren't identical, then the lists must be identical.
    //this includes the trivial case of both lists being null
    return 1;
}



//-----------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------| Assignment Functions |----------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------

int isReflection(node *a, node *b)
{
    //Both nodes are NULL
    //trees/subtrees are reflections of one another
    if(a == NULL && b == NULL)
        return 1;

    //Make sure neither node is NULL
    //Avoids a seg fault
    else if(a != NULL && b != NULL)
    {
        //Trees cannot be reflections of one another
        //if the data at each mirrored node are not equal
        if(a->data != b->data)
            return 0;
        //Here's the clever recursive call. Two binary trees can only be reflections of one another if both:
        //the right subtree from one is a reflection of the left subtree from the other and vice-versa
        else
            return (isReflection(a->left, b->right) && isReflection(a->right, b->left));

    }
    //If it is not the case where either: both a and b are NULL, or
    //are not NULL, then they cannot be reflections of one another
    else
        return 0;
}

node *makeReflection(node *root)
{
    //If the tree or subtree is rooted at NULL,
    //its reflection is also NULL !
    if (root == NULL)
        return NULL;

    //If not, create a new node with identical data to the root of
    //the tree or subtree passed
    node *r = new_node(root->data);

    //Then recursively call this process. As stated in my 'isReflection' function, two trees
    //or subtrees are only reflections of one another if the right subtree from one is a
    //reflection of the left subtree from the other and vice-versa, hence this setup:
    r->left = makeReflection(root->right);
    r->right = makeReflection(root->left);

    return r;
}

int kindredSpirits(node *a, node *b)
{
    //the recursiveness of this function comes from calling preorder() and postorder().
    //since listCmp(), preorder() and postorder() are all O(n) [due to head insertion],
    //kindredSpirits itself is also O(n) :^)

    //pre and post must be double pointers for preorder() and postorder() to function properly
    pack **pre, **post;

    //of course, they need space for what they are pointing to
    pre = malloc(sizeof(pack*));
    post = malloc(sizeof(pack*));

    //----------------------

    //Initialize the linked lists to NULL
    *pre = NULL;
    *post = NULL;

    //does the preorder of a match the postorder of b?
    preorder(a,pre);
    postorder(b,post);

    //if so, return 1
    if(listCmp(*pre,*post))
        return 1;

    //----------------------

    //Initialize the linked lists to NULL
    *pre = NULL;
    *post = NULL;

    //does the preorder of b match the postorder of a?
    preorder(b,pre);
    postorder(a,post);

    //if so, return 1
    if(listCmp(*pre,*post))
        return 1;

    //----------------------

    //if all else fails, the trees are not kindred spirits
    return 0;

    //This function basically just compares the preorder of a to the
    //postorder of b and vice-versa. if either is identical, then
    //the trees are kindred spirits :^)
    //otherwise, they are not :^( hopefully they will find true love with some other tree.
}

double difficultyRating(void)
{
    //This assignment was soooo easy
    return 1.0;
}

double hoursSpent(void)
{
    //It was still easy even though it took a while
    return 20;
}
