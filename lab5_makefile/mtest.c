//mtest.c
#include "test.h"
int main() {
	int boo = 2;
	int val = 0;
	val = InFoo(val); // InFoo Call
	boo = InBoo(); // InBoo Call
	InBar(); // InBar Call

	return 0;
}
