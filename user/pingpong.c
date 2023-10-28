#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) 
{
	int pid;
	int ps[2], cs[2];	//parent sends, child sends
	char buf[] = {"hi!"};
	pipe(ps);
	pipe(cs);

	if(fork() > 0)	//parent
	{
		pid = getpid();
		close(ps[1]);
		close(cs[0]);
		write(ps[0], buf, 1);
		read(cs[1], buf, 1);
		printf("%d: received pong\n", pid);
		exit(0);
	}
	else if(fork() == 0)	//child
	{
		pid = getpid();
		close(ps[0]);
		close(ps[1]);
		read(ps[1], buf, 1);
		printf("%d: received ping\n", pid);
		write(cs[0], buf, 1);
		exit(0);
	} 
	else	//check error
	{
		printf("fork error\n");
		close(ps[0]);
		close(ps[1]);
		close(cs[0]);
		close(cs[1]);
		exit(1);
	}

}
