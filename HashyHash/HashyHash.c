//Ryan Bell - 12/4/16
//PID: 3605342
//NID: ry049745
//COP3502 Sean Szumlanski
//HashyHash Code

#include "HashyHash.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//-----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------| Helper Functions |-----------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------

int nextPrime(int n)
{
	int i, root, keepGoing = 1;

	if (n % 2 == 0)
		++n;

	while (keepGoing)
	{
		keepGoing = 0;
		root = sqrt(n);

		for (i = 3; i <= root; i++)
		{
			if (n % i == 0)
			{
				// Move on to the next candidate for primality. Since n is odd, we
				// don't want to increment it by 1. That would give us an even
				// integer greater than 2, which would necessarily be non-prime.
				n += 2;
				keepGoing = 1;

				// Leave for-loop. Move on to next iteration of while-loop.
				break;
			}
		}
	}

	return n;
}

//-----------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------| Assignment Functions |----------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
HashTable *makeHashTable(int capacity)
{
    int i;
    HashTable *h = malloc(sizeof(HashTable));
    if (h == NULL)
        return NULL;

    //If the argument to this function is invalid
    if (capacity <= 0)
        capacity = DEFAULT_CAPACITY;

    //Initialize all members of the struct
    h->array = malloc(sizeof(int)*capacity);
    if(h->array == NULL)
    {
        free(h);
        return NULL;
    }
    h->capacity = capacity;
    h->size = 0;
    h->hashFunction = NULL;
    h->probing = LINEAR;
    //There have not been any operations or collisions yet:
    h->stats.opCount = 0;
    h->stats.collisions = 0;

    for(i=0; i<capacity; i++)
        h->array[i] = UNUSED;

    return h;
}

HashTable *destroyHashTable(HashTable *h)
{
    if(h != NULL)
        free(h->array);

    free(h);

    return NULL;
}

int setProbingMechanism(HashTable *h, ProbingType probing)
{
    if(h == NULL)
        return HASH_ERR;
    if(probing != LINEAR && probing != QUADRATIC)
        return HASH_ERR;

    h->probing = probing;

    return HASH_OK;
}

int setHashFunction(HashTable *h, unsigned int (*hashFunction)(int))
{
    if(h == NULL)
        return HASH_ERR;

    h->hashFunction = hashFunction;

    return HASH_OK;
}

int isAtLeastHalfEmpty(HashTable *h)
{
    if(h == NULL)
        return 0;

    //If the size of the table (aka: the amount of elements in it) is less than or equal
    //to half of the table's capacity, then the table is at least half empty.
    //This also takes care of the case when the table's capacity is an odd number
    //e.g. capacity = 13, so capacity/2 = 13/2 = 6. Only if size <=6 if the table half empty
    if( (h->size) <= ( (h->capacity)/2 ) )
        return 1;

    //If 1 is not returned by now, the table is not at least half empty
    return 0;
}

int expandHashTable(HashTable *h)
{
    //Don't EVEN think about continuing within this function without passing these conditions
    if(h == NULL || h->array == NULL)
        return HASH_ERR;

    //2 Arrays: a new and an old (h->array) one. The old one will be checked for non-empty
    //elements of which will be re-hashed into the new one
    int i, newcap = (h->capacity)*2 + 1, oldcap = h->capacity;
    int *oldarray = h->array;

    //Give h a new array of a size dependent on the probing type
    if(h->probing == LINEAR)
    {
        h->array = malloc(sizeof(int)*newcap);
        h->capacity = newcap;
    }

    if(h->probing == QUADRATIC)
    {
        newcap = nextPrime(newcap);
        h->array = malloc(sizeof(int)*newcap);
        h->capacity = newcap;
    }

    //Check the malloc call
    if(h->array == NULL)
    {
        //give h its original array back
        h->array = oldarray;
        return HASH_ERR;
    }

    //Initialize all members of the new array to UNUSED
    //IMPORTANT: Also, reset the table's size to 0, because elements will be re-inserted
    for(i=0; i<newcap; i++)
        h->array[i] = UNUSED;
    h->size = 0;

    //Check for non-UNUSED and non-DIRTY members of the old array and re-hash them into the new array
    for(i=0; i<oldcap; i++)
        if((oldarray[i] != UNUSED) && (oldarray[i] != DIRTY))
        {
            //Note: it will never be the case that, within these particular insert() calls,
            //expandHashTable() will be called, since the capacity of the array has already
            //been expanded by this point. this avoids infinite recursion
            insert(h, oldarray[i]);

            //IMPORTANT: each time insert() is called, the opCount is incremented,
            //but opCount should not change within expandHashTable()
            //thus, decrement opCount each time insert() is called to balance this out
            //However, insertion DOES take care of the incrementation of the amount of
            //collisions that are caused as a result of re-hashing the elements
            h->stats.opCount--;
        }

    //Useless to me now
    free(oldarray);

    return HASH_OK;
}

int insert(HashTable *h, int key)
{
    int index, hval, collisions = 0;

    //These conditions will cause an error
    if(h == NULL || h->hashFunction == NULL)
        return HASH_ERR;

    //Expand the table if it is not half empty
    if(!isAtLeastHalfEmpty(h))
        if(expandHashTable(h) == HASH_ERR)
            return HASH_ERR;

    //The first index to be checked is the same from linear and quadratic probing
    //"hval" is used to keep track of this original index; modding is here as a safety measure
    index = hval = (h->hashFunction(key))%(h->capacity);

    //The probing:
    //-------------
    //If collisions exceeds the table capacity, then something went wrong
    while(collisions < h->capacity)
    {
        //If a cell is neither UNUSED or DIRTY, then it is occupied
        if(h->array[index] != UNUSED && h->array[index]!= DIRTY)
        {
            collisions++;

            //NOTE: the amount of incrementation of hval for linear and quadratic probing
            //will be equal to the amount of collisions (linear) or the amount of
            //collisions squared (quadratic) in this insertion

            //Linear probing
            if(h->probing == LINEAR)
                index = (hval + collisions)%(h->capacity);
            //Quadratic probing
            if(h->probing == QUADRATIC)
                index = (hval + collisions*collisions)%(h->capacity);
        }
        //At this point, an UNUSED or DIRTY index is found
        else
        {
            //the while loop can be exited after insertion
            h->array[index] = key;
            break;
        }
    }

    //If the while loop was exited due to this, there was an error
    if(collisions >= h->capacity)
        return HASH_ERR;
    //otherwise, we experience this many collisions
    else
        h->stats.collisions += collisions;

    //Insertion increments these two:
    h->size++;
    h->stats.opCount++;

    return HASH_OK;
}

int search(HashTable *h, int key)
{
    //These conditions will cause an error
    if(h == NULL || h->hashFunction == NULL)
        return -1;

    int index, hval, collisions = 0;
    index = hval = (h->hashFunction(key))%(h->capacity);

    //Counts as an operation regardless of if key is found or not
    h->stats.opCount++;

    //If collisions exceeds capacity, then the key is not in the table; break and return
    while(collisions < h->capacity)
    {
        //Key is not found at the index
        if(h->array[index] != key)
        {
            //Empty spot is hit; break and return
            if(h->array[index] == UNUSED)
                break;

            //If not key and not empty, we have a collision
            collisions++;

            //NOTE: the amount of incrementation of hval for linear and quadratic probing
            //will be equal to the amount of collisions (linear) or the amount of
            //collisions squared (quadratic) in this insertion
            //Linear probing
            if(h->probing == LINEAR)
                index = (hval + collisions)%(h->capacity);
            //Quadratic probing
            if(h->probing == QUADRATIC)
                index = (hval + collisions*collisions)%(h->capacity);
        }
        //At this point, the key is found
        else
        {
            h->stats.collisions += collisions;
            return index;
        }
    }

    h->stats.collisions += collisions;

    //If the key is not found
    return -1;
}

int delete(HashTable *h, int key)
{
    //These conditions will cause an error
    if(h == NULL || h->hashFunction == NULL)
        return -1;

    //Note that search will increment the collision and op counters
    int index = search(h,key);

    //Key is found
    if(index != -1)
    {
        //Size is decremented, the index is marked with a dirty-bit, and return the deleted index
        h->size--;
        h->array[index] = DIRTY;
        return index;
    }

    //Otherwise, key is not there (or search() malfunctioned) and cannot be deleted
    return -1;
}

double difficultyRating(void)
{
    return 2.0;
}

double hoursSpent(void)
{
    return 15;
}

