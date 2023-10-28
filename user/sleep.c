#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		fprintf(2, "usage: sleep ticks\n");	//so easy, don't need description:)D
		exit(1);
	}
	int ticks=atoi(argv[1]);	//atoi change string into int
	sleep(ticks);
	exit(0);
}
