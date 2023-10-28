#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("xargs : minum amount of args is 2 !\n");
		exit(1);
	}
	if (argc - 1 >= MAXARG)
	{
		printf("xargs : minum amount of args is %d !\n", MAXARG);
	}
	char buf[512], *xargs[MAXARG];
	for (int i = 1; i < argc; i++)
		xargs[i-1] = argv[i];
	while (1) 
	{
		int index = argc - 1;
		gets(buf, 64);
		if (buf[0] == 0)
			break;
		xargs[index] = buf;
		index++;
		for (char *p = buf; *p; p++) 
		{
			if (*p == ' ')
			{
				*p = 0;
				xargs[index] = p + 1;
				index++;
			}
			else if (*p == '\n')
			{
				*p = 0;
			}
		}
		int pid = fork();
		if (pid == 0)
		{
			exec(argv[1], xargs);
		}
		else if (pid < 0)
		{
			printf("fork error! \n");
			exit(1);
		}
		else
		{
			wait(0);
		}
    }
	wait(0);
	exit(0);
}
