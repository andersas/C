#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

#include <bsd/unistd.h>


void diagnostics(int status) {

     if (WIFEXITED(status)) {
          printf("Called exit(%i).\n",WEXITSTATUS(status));
     }

     if (WIFSIGNALED(status)) {
          printf("Killed by signal %i.\n", WTERMSIG(status));
     }
     if (WCOREDUMP(status)) {
          printf("Core dumped.\n");
     }

     if (WIFSTOPPED(status)) {
          printf("Stopped (=paused) by signal %i.\n", WSTOPSIG(status));
     }

     if (WIFCONTINUED(status)) {
          printf("Resumed  by delivery of SIGCONT.\n");
     }
}

int is_error(int status) {

	if (WIFEXITED(status))
		if (WEXITSTATUS(status) == 0)
			return 0;
	return 1;
	
}

pid_t respawn_here_on_crash() {

	const pid_t parpid = getpid();
	pid_t childpid = 0;
	pid_t pid;

	char buf[16];
	int status;
	prctl(PR_GET_NAME,&buf);

	prctl(PR_SET_NAME,"watcher");
	setproctitle("-watcher");

	for(;;) {
		pid = childpid;
		if ((childpid = fork()) == 0) { // Start the process
			prctl(PR_SET_NAME,buf);
			setproctitle(NULL);
			return pid; // old child pid
		}

		if (childpid < 0) {
			perror("fork");
		} else {
			while((pid = waitpid(childpid,&status,0)) != childpid) {
				if (pid < 0 && errno == ECHILD) 
					break;
			}
		}

		if (pid == childpid) {
			if (is_error(status)) { // child exited normally.
				diagnostics(status);
			} else {
				exit(0);
			}
		}
		// child crashed
		printf("Child crashed, restarting...\n");
		sleep(1);
	}



}

void watchdog(int timeout) {

	if (timeout <= 0) return;

	int starttime = time(NULL);

	pid_t parpid = getpid();

	pid_t childpid = fork();
	if (childpid < 0) {
		perror("watchdog: fork");
		return;
	}

	if (childpid != 0) {
		return;
	}

	while (time(NULL) - starttime < timeout && getppid() == parpid) {
		sleep(1);
	}

	if (getppid() == parpid) {
		printf("Watchdog: process time exceeded\n");
		kill(parpid, SIGXCPU);
		sleep(1);
		if (getppid() == parpid) {
			kill(parpid,SIGKILL);
		}
	}

	exit(0);

}


int main(int argc, char **argv, char **envp) {
	
	int *p;

	setproctitle_init(argc,argv,envp);

	if (respawn_here_on_crash() > 0) {
		printf("Crash detected, process restarted.\n");
	}

	// do something
	watchdog(2);
	sleep(10);

	printf("Woke up, doing risky stuff...\n");
	p = (int *) 201213;

	*p = 2; // crash

	exit(0);


}
