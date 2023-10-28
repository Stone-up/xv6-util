#include "kernel/types.h"
#include "user/user.h"


 
void prime(int* a, int cnt)
{
 
	if (cnt == 0) 
	{	
		exit(0);
	}
    
	printf("prime %d\n", a[0]);
	int fd[2];	//0:read, 1:write
	pipe(fd);	
	int pid = fork();
	if (pid < 0)	//check error
	{
		printf("fork error\n");
		exit(1);
	}
	else if (pid == 0)	//child
	{
		close(fd[1]);
        	int tmp = 0;
		int buf[64] = {'\0'};
		while (1)
		{
			int numr = read(fd[0], &buf[tmp], 4);
			if (numr == 4) 
				tmp++;
			if (numr == 1 && buf[tmp] == '\n') 
				break;
		}
		close(fd[0]);
		prime(buf, tmp);
		exit(0);
	} 
	
	else	//parent
	{
		close(fd[0]);
		for(int i = 0; i < cnt; i++) 
		{
		    if (a[i] % a[0] == 0) //not primes
			continue; 
		    else 
			write(fd[1], &a[i], 4);
		}
		char b = '\n';
		write(fd[1], &b, 1);
		close(fd[1]);
		wait(0);
		exit(0);
	}
}
 
int main()
{
	int buf[34];
	for (int i = 0; i < 34; i++)
	{
		buf[i] = i + 2;
	}
	prime(buf, 34);
	return 0;
}
