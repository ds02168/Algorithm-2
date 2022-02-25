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

	printf("���� stack: ");
	si.print();
	printf("�Ǽ� stack: ");
	sd.print();

	for (i = 0; i < 120; i++)
	{
		if (si.empty() == false)
			printf("%d\n", si.pop());

	}
}