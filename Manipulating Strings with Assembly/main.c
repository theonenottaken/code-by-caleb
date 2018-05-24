#include <stdio.h>
#include "pstring.h"

#define MAX_LEN 20

int main() {

	Pstring p1;
	Pstring p2;
	int len;
	int opt;

	// initialize first pstring
	scanf("%s", p1.str);
	scanf("%d", &len);
	p1.len = len;

	// initialize second pstring
	scanf("%s", p2.str);
	scanf("%d", &len);
	p2.len = len;
	
	// select which function to run
	scanf("%d", &opt);
	run_func(opt, &p1, &p2);

	return 0;
}