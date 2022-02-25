#include <stdio.h>
#include "stack.h"

void main()
{
	stack<int> si;
	stack<double> sd;
	int i;

	for (i = 0; i < 100; i++) {
		si.push(i);
		sd.push(i / 100.0);
	}

	printf("정수 stack: ");
	si.print();
	printf("실수 stack: ");
	sd.print();

	for (i = 0; i < 120; i++)
	{
		if (si.empty() == false)
			printf("%d\n", si.pop());

	}
}