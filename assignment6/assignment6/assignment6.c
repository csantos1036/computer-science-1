//
//  main.c
//  assignment6-friendship
//
//  Created by Carolina Santos.
//  Copyright © 2020 Carolina Santos. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This value will define the maximum length of our string
#define SIZE 100

typedef struct user_bst user_bst;
typedef struct friend_bst friend_bst;

// Stuct for user_bst tree nodes
struct user_bst {
    user_bst *l, *r, *p;
    char * name;
    int numFriends;
    friend_bst * friends;
};

// Stuct for friend_bst tree nodes
struct friend_bst {
    friend_bst *l, *r, *p;
    char * name;
};

//user_bst prototypes
user_bst * createUser(char *, char *);
user_bst * insertUser(user_bst *, char *, char *);
void freeAll(user_bst *);
int containsUser(user_bst *, char *);
user_bst * locate(user_bst *, char *);

//friend_bst prototypes
void inOrderPrintFriends(friend_bst *);
void swapFriend(friend_bst *, friend_bst *);
friend_bst * createFriend(char *);
friend_bst * insertFriend(friend_bst *, char *);
friend_bst * removeFriend(friend_bst *, char *);
int containsFriend(friend_bst *, char *);

// Query Protoypes
user_bst * addQuery(user_bst *, char *, char *); // Executes when the user inputs ADD
user_bst * removeQuery(user_bst *, char *, char *); // Executes when the user inputs REMOVE

int main()
{
    int q; // Number of queries
    char query[7]; // Query selection
    char firstName[SIZE + 1]; // First user input name
    char secondName[SIZE + 1]; // Second user input name
    
    user_bst * root = NULL;

    // Asking for user input on the number of queries
    scanf("%d", &q);
            
    // Check to make sure number of queries is less than 500000
    while (q > 500000)
    {
        scanf("%d", &q);
    }
        
    while (q > 0 )
    {
        scanf("%s", query);
        scanf("%s", firstName);
            
        if (strcmp(query, "ADD") == 0)
        {
            scanf("%s", secondName);
            // Check to make sure the two names are not the same and the string does not exceed the maximum length
            if(strcmp(firstName, secondName) != 0  && (strlen(secondName) < (SIZE + 1)))
            {
                root = addQuery(root, firstName, secondName);
                root = addQuery(root, secondName, firstName);
            }
        }
        else if(strcmp(query, "REMOVE") == 0)
        {
            scanf("%s", secondName);
            // Check to make sure the two names are not the same
            if(strcmp(firstName, secondName) != 0 )
            {
                root = removeQuery(root, firstName, secondName);
                root = removeQuery(root, secondName, firstName);
            }
        }
        else if(strcmp(query, "LIST") == 0)
        {
            // Create temporary user_bst node to locate the desired user
            user_bst * tmp = locate(root, firstName);
            if(containsUser(tmp, firstName))
            {
                // Check to see whether user has friends or not
                if(tmp->numFriends == 0)
                {
                    printf("0\n");
                }
                else
                {
                    int val = tmp->numFriends;
                    printf("%d\n", val);
                    inOrderPrintFriends(tmp->friends);
                }
            }
            // If the desired user is the root of the user_bst
            else if(containsUser(root, firstName))
            {
                if(root->numFriends == 0)
                {
                    printf("0\n");
                }
                else
                {
                    int val = root->numFriends;
                    printf("%d\n", val);
                    inOrderPrintFriends(root->friends);
                }
            }
            else
            {
                // If name doesnt exist, return 0
                printf("0\n");
            }
        }
        q--;
    }
    
    freeAll(root);
    
    return 0;
}

void inOrderPrintFriends(friend_bst * rt)
{
    if (rt == NULL) return;
    inOrderPrintFriends(rt->l);
    printf("%s\n", rt->name);
    inOrderPrintFriends(rt->r);
}

// Function to check if a user is contained within user_bst tree with a given root
int containsUser(user_bst * rt, char * name)
{
    if (!rt) return 0; // BASE CASE
    if (strcmp(rt->name, name) == 0) return 1; // FOUND THE NODE
    if (strcmp(rt->name, name) < 0) return containsUser(rt->r, name); // RECURSIVE CASE 1
    return containsUser(rt->l, name); // RECURSIVE CASE 2
}

// Function to check if a friend is contained within friend_bst tree with a given root
int containsFriend(friend_bst * rt, char * name)
{
    if (!rt) return 0; // BASE CASE
    if (strcmp(rt->name, name) == 0) return 1; // FOUND THE NODE
    if (strcmp(rt->name, name) < 0) return containsFriend(rt->r, name); // RECURSIVE CASE 1
    return containsFriend(rt->l, name); // RECURSIVE CASE 2
}

// Function to return the user node contained within user_bst tree with a given root
user_bst * locate(user_bst * rt, char * val)
{
    if (!rt) return NULL; // BASE CASE
    if (strcmp(rt->name, val) == 0) return rt; // FOUND THE NODE
    if (strcmp(rt->name, val) < 0) return locate(rt->r, val); // RECURSIVE CASE 1
    return locate(rt->l, val); // RECURSIVE CASE 2
}

// Function to recursively free the entire tree
void freeAll(user_bst * rt)
{
    if (rt)
    {
        freeAll(rt->l);
        freeAll(rt->r);
        free(rt);
    }
}

// Function to create a user
user_bst * createUser(char * name1, char * name2)
{
    user_bst * ret = malloc(sizeof(user_bst));
    ret->l = ret->r = ret->p = NULL;
    ret->name = malloc(strlen(name1) + 1);
    strcpy(ret->name, name1);
    ret->numFriends = 1;
    ret->friends = createFriend(name2);
    return ret;
}

// Function to create a friend
friend_bst * createFriend(char * name)
{
    friend_bst * ret = malloc(sizeof(friend_bst));
    ret->l = ret->r = ret->p = NULL;
    ret->name = malloc(strlen(name) + 1);
    strcpy(ret->name, name);
    return ret;
}

// Function to swap nodes after removing a friend
void swapFriend(friend_bst * a, friend_bst * b)
{
    char * tmp = malloc(strlen(a->name) + 1);
    strcpy(tmp, a->name);
    strcpy(a->name, b->name);
    strcpy(b->name, tmp);
}

friend_bst * removeFriend(friend_bst * rt, char * name)
{
    if (rt == NULL)
    {
        return rt; // can't remove anything
    }
    if (strcmp(rt->name, name) < 0)
    {
        removeFriend(rt->r, name);
        return rt;
    }
    else if (strcmp(rt->name, name) > 0)
    {
        removeFriend(rt->l, name);
        return rt;
    }

    // 0/1 child
    friend_bst * ch = NULL;
    int is2Child = 1;
    if (rt->r == NULL)
    {
        is2Child = 0;
        ch = rt->l;
    }
    else if (rt->l == NULL)
    {
        is2Child = 0;
        ch = rt->r;
    }
    if (!is2Child)
    {
        friend_bst * p = rt->p;

        // Handle the parent's child pointer
        if (p != NULL)
        {
            if (p->r == rt)
            {
                // We were on the right
                p->r = ch;
            }
            else
            {
                // We were on the left
                p->l = ch;
            }
        }

        // Handle the child's parent pointer
        if (ch != NULL)
        {
            ch->p = p;
        }

        // Free the root
        free(rt);

        // Return the new root of the subtree
        return ch;
    }

    // We are in the 2 child case :(
    friend_bst * replacement = rt->r;
    while (replacement->l != NULL)
        replacement = replacement->l;

    swapFriend(replacement, rt);
    removeFriend(replacement, name);
    
    return rt;
}

// Function to insert some value into some tree with a given root
// Non-recursive
user_bst * insertUser(user_bst * rt, char * name1, char * name2)
{
    // The empty tree case
    if (rt == NULL)
    {
        return createUser(name1, name2);
    }

    // Store current location
    user_bst * cur = rt;

    // Move the current location down
    // until we have inserted the value
    int inserted = 0;
    while(!inserted)
    {
        // Check which side of the node the
        // current data needs to be inserted on
        if (strcmp(name1, cur->name) < 0)
        {
            // Smaller value
            // Go to left
            if (cur->l)
            {
                // A child exists
                cur = cur->l;
            }
            else
            {
                // Spot is open
                cur->l = createUser(name1, name2);
                cur->l->p = cur ; // update parent pointer
                inserted = 1; // flag that we have inserted
            }
        }
        else if (strcmp(name1, cur->name) > 0)
        {
            // Larger value (or equal)
            // Go to right
            if (cur->r)
            {
                // A child exists
                cur = cur->r;
            }
            else
            {
                // Spot is open
                cur->r = createUser(name1, name2);
                cur->r->p = cur;
                inserted = 1;
            }
        }
        else
        {
            // Duplicate
            inserted = 1; // don't insert, but say we did...
        }
    }

    // The root has not changed...
    return rt;
}

// Function to insert some value into some tree with a given root
// Non-recursive
friend_bst * insertFriend(friend_bst * rt, char * name)
{
    // The empty tree case
    if (rt == NULL)
    {
        return createFriend(name);
    }
    
    // Store current location
    friend_bst * cur = rt;

    // Move the current location down
    // until we have inserted the value
    int inserted = 0;
    while(!inserted)
    {
        // Check which side of the node the
        // current data needs to be inserted on
        if (strcmp(name, cur->name) < 0)
        {
            // Smaller value
            // Go to left
            if (cur->l)
            {
                // A child exists
                cur = cur->l;
            }
            else
            {
                // Spot is open
                cur->l = createFriend(name);
                cur->l->p = cur ; // update parent pointer
                inserted = 1; // flag that we have inserted
            }
        }
        else if (strcmp(name, cur->name) > 0)
        {
            // Larger value (or equal)
            // Go to right
            if (cur->r)
            {
                // A child exists
                cur = cur->r;
            }
            else
            {
                // Spot is open
                cur->r = createFriend(name);
                cur->r->p = cur;
                inserted = 1;
            }
        }
        else
        {
            // Duplicate
            inserted = 1; // don't insert, but say we did...
        }
    }

    // The root has not changed...
    return rt;
}

user_bst * addQuery(user_bst * rt, char * name1, char * name2)
{
    // Checks to see if user exists already, if not create new user_bst node
    if (!containsUser(rt, name1))
    {
        rt = insertUser(rt, name1, name2);
    }
    else if (containsUser(rt, name1))
    {
        user_bst * tmp;
        tmp = locate(rt, name1);
        if(!containsFriend(tmp->friends, name2))
        {
            //printf("inserting friend: %s\n", name2);
            tmp->friends = insertFriend(tmp->friends, name2);
            tmp->numFriends++;
        }
    }
    return rt;
}

user_bst * removeQuery(user_bst * rt, char * name1, char * name2)
{
    if (containsUser(rt, name1))
    {
        user_bst * tmp;
        tmp = locate(rt, name1);
        if(containsFriend(tmp->friends, name2))
        {
            tmp->friends = removeFriend(tmp->friends, name2);
            tmp->numFriends--;
        }
    }
    return rt;
}

