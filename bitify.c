/* this file belongs to `bitify` http://github.com/amery/bitify
 *
 * Copyright (c) 2010, Alejandro Mery <amery@geeks.cl>
 * All rights reserved. See COPYING for details.
 ***/

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <libgen.h>

#define errf(...)	fprintf(stderr, __VA_ARGS__)
#define print(s)	fputs(s, stdout)

static int bitify(const char *arg0, char **argv) {
	uint32_t value = 0;
	register int i;

	for (i=0; argv[i]; i++) {
		char *endptr = NULL;
		long int bit = strtol(argv[i], &endptr, 10);

		if (*endptr != '\0' || bit < 0 || bit > 32) {
			errf("%s: %s: invalid bit\n", arg0, argv[i]);
			return 1;
		} else if (bit != 0) {
			value |= 1 << (bit - 1);
		}
	}

	printf("%u\n", value);
	return 0;
}

static int unbitify(const char *arg0, char **argv) {
	register int i, j;

	for (i=0; argv[i]; i++) {
		char *endptr = NULL;
		long long int value = strtoll(argv[i], &endptr, 10);

		if (*endptr != '\0' || value < 0 || value > 0xffffffffLL) {
			errf("%s: %s: invalid value\n", arg0, argv[i]);
			return 1;
		} else if (value == 0) {
			print("0\n");
		} else {
			int first = 1;
			for(j=1; value != 0; j++) {
				if (value & 1) {
					printf(" %u"+first, j);
					first = 0;
				}
				value >>= 1;
			}
			print("\n");
		}
	}
	return 0;
}

struct {
	const char *arg0;
	int (*f)(const char *, char **);
} progs[] = {
	{ "bitify", bitify },
	{ "unbitify", unbitify },
	{ NULL, NULL }
};

int main(int argc, char **argv)
{
	register int i = 0;
	const char *arg0 = basename(argv[0]);

	/* demux */
	for (i=0; progs[i].arg0; i++) {
		if (strcmp(arg0, progs[i].arg0) == 0)
			return progs[i].f(arg0, argv+1);
	}

	errf("%s: unknown command.\n", arg0);
	return -1;
}
