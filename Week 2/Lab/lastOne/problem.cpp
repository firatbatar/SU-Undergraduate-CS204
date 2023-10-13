#include <stdio.h>
#include <cmath>

//The function update sets 
//a = a + b
//b = |a - b|
//Please complete the function

void update(int* a, int* b) {
	int aVal = *a

	*a = *a + *b;
	*b = abs(aVal - *b);

	//if (aVal < bVal) *b *= -1;
}

int main() {
	int a, b;
	int* pa = &a, * pb = &b;

	scanf("%d %d", &a, &b); //reads two integers from the command line, store it in a and b
	update(pa, pb);
	printf("%d\n%d", a, b); //output the new values of a and b

	return 0;
}
