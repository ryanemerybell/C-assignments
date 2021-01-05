//Ryan Bell - 10/16/16
//PID: 3605342
//NID: ry049745
//COP3502 Sean Szumlanski
//Fibonacci Code

#include "Fibonacci.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>

//There was an issue using the pow function in math.h,
//So I made my own power function
unsigned int power(unsigned int a,unsigned int b)
{
    unsigned int product = 1, i;

    if(b==0)
        return 1;
    if(a==0)
        return 0;

    for(i=1;i<=b;i++)
        product *= a;

    return product;
}

int findMax(int a, int b)
{
    if(a<b)
        return b;
    return a;
}

int findMin(int a, int b)
{
    if(a>b)
        return b;
    return a;
}

//-----------------------------------------------------------------------------------------------------

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
    //Checks if a NULL pointer was passed to hugeAdd
    if(p==NULL||q==NULL)
        return NULL;

    //Min and max array lengths for convenience
    //Temporary Length for the arithmetic, as well as sum and carry. i as a counter
    //Dynamically allocate an int array and a HI pointer
    int max = findMax(p->length,q->length), min = findMin(p->length,q->length);
    int tempLen = (max + 1);
    int i, sum;
    int carry = 0;
    int *tempArray = malloc(sizeof(int)*tempLen);
    HugeInteger *r = malloc(sizeof(HugeInteger));
    //Checks if malloc calls worked
    if(tempArray==NULL)
        return NULL;
    if(r==NULL)
    {   //To avoid a memory leak:
        free(tempArray);
        return NULL;
    }


    //Adds up all digits up to the smaller array length
    for(i=0;i<min;i++)
    {
        sum = p->digits[i] + q->digits[i] + carry;
        carry = 0;

        //To carry or not to carry; that is the question.
        if(sum>9)
        {
            tempArray[i] = sum - 10;
            carry = 1;
        }
        else
            tempArray[i] = sum;
    }

    //'carry' carries over to either for loop:
    //Continues past the smaller array
    //Depending on which HugeInt has more digits: p
    if((p->length)>(q->length))
        for(i=min;i<max;i++)
        {
            sum = p->digits[i] + carry;
            carry = 0;

            if(sum>9)
            {
                tempArray[i] = sum - 10;
                carry = 1;
            }
            else
                tempArray[i] = sum;
        }

    //or q
    else if((p->length)<(q->length))
        for(i=min;i<max;i++)
        {
            sum = q->digits[i] + carry;
            carry = 0;

            if(sum>9)
            {
                tempArray[i] = sum - 10;
                carry = 1;
            }
            else
                tempArray[i] = sum;
        }
    //NOTE: neither for loop is ran if the array lengths are equal
    //Meaning that the first for loop took care of all arithmetic

    //Case where a new digits place is added:
    //When 'carry' carries over as a 1 is the only time this happens
    if(carry == 1)
        tempArray[max] = 1;

    r->length = max+carry;
    r->digits = tempArray;

    return r;
}

HugeInteger *hugeDestroyer(HugeInteger *p)
{
    if(p!=NULL)
    {
        free(p->digits);
        free(p);
    }

    return NULL;
}

HugeInteger *parseString(char *str)
{
    if(str==NULL)
        return NULL;

    int i = 0, len = strlen(str);
    HugeInteger *h;
    h = malloc(sizeof(HugeInteger));

    if(h==NULL)
        return NULL;

    //Empty String Case
    if(len==0)
    {
        h->digits = malloc(sizeof(int));

        if(h->digits==NULL)
        {
            free(h);
            return NULL;
        }

        h->digits[0] = 0;
        h->length = 1;

        return h;
    }

    //If not:
    h->digits = malloc(sizeof(int)*len);

    if(h->digits==NULL)
    {
        free(h);
        return NULL;
    }

    h->length = len;

    //len-1-i is the opposite side of the string as i
    while(str[i]!='\0')
    {
        h->digits[i] = str[len-1-i] - '0';
        i++;
    }

    return h;
}

HugeInteger *parseInt(unsigned int n)
{
    int digs = 1, i = 1, track, keepTrack = 0;
    HugeInteger *h;

    h = malloc(sizeof(HugeInteger));
    if(h==NULL)
        return NULL;

    while(n%power(10,i)!=n)
    {
        digs++;
        i++;
        if(i==10)
            break;
    }

    h->length = digs;
    h->digits = malloc(sizeof(int)*digs);
    if(h->digits==NULL)
    {
        free(h);
        return NULL;
    }


    for(i=1;i<digs;i++)
    {
        track = n%power(10,i) - keepTrack;
        keepTrack += track;
        h->digits[i-1] = track/power(10,i-1);
    }

    //I kept this last iteration outside my for loop for efficiency
    track = n - keepTrack;
    h->digits[digs-1] = track/power(10,digs-1);

    return h;
}

unsigned int *toUnsignedInt(HugeInteger *p)
{
    //Make sure p is useful
    if(p==NULL||p->digits==NULL)
        return NULL;


    //Checking if p exceeds UINT_MAX
    if(p->length>10)
        return NULL;
    if(p->length==10)
    {
        if(p->digits[9]>4)
            return NULL;
        if(p->digits[9]==4)
        {
            if(p->digits[8]>2)
                return NULL;
            if(p->digits[8]==2)
            {
                if(p->digits[7]==9)
                {
                    if(p->digits[6]>4)
                        return NULL;
                    if(p->digits[6]==4)
                    {
                        if(p->digits[5]==9)
                        {
                            if(p->digits[4]>6)
                                return NULL;
                            if(p->digits[4]==6)
                            {
                                if(p->digits[3]>7)
                                    return NULL;
                                if(p->digits[3]==7)
                                {
                                    if(p->digits[2]>2)
                                        return NULL;
                                    if(p->digits[2]==2)
                                    {
                                        if(p->digits[1]==9)
                                        {
                                            if(p->digits[0]>5)
                                                return NULL;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int i;
    unsigned int *u;
    u = malloc(sizeof(unsigned int));

    //Check the malloc call
    if(u==NULL)
        return NULL;

    //Start at 0
    *u = 0;

    //Increment u by each digit in its correct digits place
    for(i=0;i<p->length;i++)
        *u += p->digits[i]*power(10,i);

    return u;
}

HugeInteger *fib(int n)
{
    if(n<2)
        return parseInt(n);

    HugeInteger *temp, *first, *second;
    int i;

    //Me being clever. bwahahaha
    first = parseInt(0);
    second = parseInt(1);

    for(i=1;i<n;i++)
    {
        //The point of temp is to free each 'j-2' as I go through my for loop
        //where j is the greatest HugeInteger I've currently created

        //Look how damn clever I am. I only need two HugeIntegers to keep track of for fib
        //Using this trick. It's a back and forth addition that saves memory

        //Even i
        if(i%2==0)
        {
            temp = second;
            second = hugeAdd(first,second);
            free(temp->digits);
            free(temp);
        }

        //Odd i
        if(i%2==1)
        {
            temp = first;
            first = hugeAdd(first,second);
            free(temp->digits);
            free(temp);
        }
    }


    //I'm so smart. The parity of n determines whether to assign to first or second r
    if(n%2==0)
    {
        free(second->digits);
        free(second);
        return first;
    }
    if(n%2==1)
    {
        free(first->digits);
        free(first);
        return second;
    }


    //I believe that hugeAdd is an O(k) function, where k is the number of digits
    //Of the bigger HugeInteger pointer passed to it.
    //parseInt is also O(k). In total, about n O(k) are called
    //Meaning that fib is O(kn) =^)
}

double difficultyRating(void)
{
    return 2;
}

double hoursSpent(void)
{
    return 15;
}
