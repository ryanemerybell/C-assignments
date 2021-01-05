#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Fibonacci.h"

// print a HugeInteger (without a newline character)
void hugePrint(HugeInteger *p)
{
	int i;

	if (p == NULL || p->digits == NULL)
	{
		printf("(null pointer)");
		return;
	}

	for (i = p->length - 1; i >= 0; i--)
		printf("%d", p->digits[i]);
}

int main(void)
{
	HugeInteger *p, *q, *r;

	// calculate INT_MAX + 1
	p = parseInt(3);
	q = parseInt(4);
	r = hugeAdd(p, q);

	printf("%d\n",p->digits[0]);
	printf("%d\n",q->digits[0]);
	printf("%d\n",r->digits[0]);
	fflush(stdout);
	// demonstrate overflow
	//printf("Overflow style:\n%d + %d = %d\n\n", INT_MAX, 1, INT_MAX + 1);

	// print result of INT_MAX + 1 with HugeIntegers
	//printf("HugeInteger style:\n");
	//hugePrint(p);
	//printf("\n");
	//hugePrint(q);
	//printf("\n");
	//hugePrint(r);
	printf("\n\n");

	// free memory
	hugeDestroyer(p);
	hugeDestroyer(q);
	hugeDestroyer(r);


	// now calculate UINT_MAX + 1
	//p = parseInt(UINT_MAX);
	//q = parseInt(1);
	//r = hugeAdd(p, q);

	// demonstrate overflow
	//printf("Overflow style:\n%u + %u = %u\n\n", UINT_MAX, 1, UINT_MAX + 1);

	// print result of UINT_MAX + 1 with HugeIntegers
	//printf("HugeInteger style:\n");
	//hugePrint(p);
	//printf(" + ");
	//hugePrint(q);
	//printf(" = ");
	//hugePrint(r);
	//printf("\n");

	// free memory
	//hugeDestroyer(p);
	//hugeDestroyer(q);
	//hugeDestroyer(r);


	return 0;
}

