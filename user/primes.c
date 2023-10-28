#include "kernel/types.h"
#include "user/user.h"
int ps[2];
void prime(int *ps)
{
	int p, n, cs[2];
	int num = read(ps[0], &p, sizeof(p));
	pipe(cs);
	if (!num)
	{	
		close(ps[0]);
		exit(0);
	}
	else
	{
		printf("prime %d\n", p);
	}
	int pid = fork();
	if(pid < 0)
	{
		printf("fork error! \n");
		close(ps[0]);
		close(cs[0]);
		close(cs[1]);
		exit(1);
	}
	else if(pid > 0)
	{
		close(cs[0]);
		while(read(ps[0], &n, sizeof(n)))
		{
			if (n%p != 0)
			{
				write(cs[1], &n, sizeof(n));
			}
		}
		close(ps[0]);
		close(cs[1]);
		wait(0);
		exit(0);
	}
	else
	{
		close(ps[0]);
		close(cs[1]);
		prime(cs);
		close(cs[0]);
		exit(0);
	}
}
int main()
{
	pipe(ps);
	for (int i = 2; i < 36; i++)
	{
		write(ps[1], &i, sizeof(i));
	}
	int pid = fork();
	if(pid < 0)
	{
		printf("fork error !\n");
		close(ps[0]);
		close(ps[1]);
		exit(1);
	}
	else if(pid > 0)	//parent
	{
		close(ps[0]);
		close(ps[1]);
		wait(0);
		exit(0);
        }
        else	//child
        {
		close(ps[1]);
		prime(ps);
		close(ps[0]);
		exit(0);
	}
}

