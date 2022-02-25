#include "poly.h"

void main()
{
	POLY *A, *B, *C, *D;

	A = create_polynomial();
	B = create_polynomial();
	print_polynomial("\nA = ", A);
	print_polynomial("B = ", B);

	C = cpadd(A, B);
	print_polynomial("A + B = ", C);

	D = cpmult(A, B);
	print_polynomial("A * B = ", D);

	cerase(&A);
	cerase(&B);
	cerase(&C);
	cerase(&D); //A,B,C,D를 가용노드 리스트에 반환 합니다.
	garbageCollect(); //가용노드 리스트에 있는 노드들을 메모리에 반환합니다.
}