#include <stdio.h>
#include "uart0.h"
#include "gpio.h"

int main () {
	union GPIO_SET0_reg data;
	data.reg = 0xDEADBEEF;

	printf ("Original:\n");
	printf ("%x\n", data.reg);
	printf ("%x\n", data.fields.set0);

	data.fields.set0 = 0x0;

	printf ("Modified:\n");
	printf ("%x\n", data.reg);
	printf ("%x\n", data.fields.set0);
	return 0;
}


