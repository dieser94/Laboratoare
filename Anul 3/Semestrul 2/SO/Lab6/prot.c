/**
 * SO, 2017
 * Lab #6
 *
 * Task #5, lin
 *
 * Changing page access protection
 */
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "utils.h"

static int pageSize;
static struct sigaction old_action;
char *p;
int how[3] = { PROT_NONE, PROT_READ, PROT_WRITE };

static void segv_handler(int signum, siginfo_t *info, void *context)
{
	char *addr;
	int rc;
	
	addr = (char*) info->si_addr;
	/* Calling the old signal handler by default for TODO 1 */
	/* Comment this line when solving TODO 2 */
	if(signum  != SIGSEGV){
		old_action.sa_sigaction(signum, info, context);
		return;
	}
	int page = (addr-p) / pageSize;
	/* TODO 2 - check if the signal is SIGSEGV */
	/* TODO 2 - obtain from siginfo_t the memory location
	 * which caused the page fault
	 */

	if(page > 2 || page < 0){
		old_action.sa_sigaction(signum, info, context);
		return;
	
	}
	/* TODO 2 - obtain the page which caused the page fault
	 * Hint: use the address returned by mmap
	 */

	/* TODO 2 - increase protection for that page */
	if(how[page] == PROT_NONE){
		rc = mprotect(p+page*pageSize, pageSize, PROT_READ);
		how[page] = PROT_READ;
	}
	else if(how[page] == PROT_READ){
		rc = mprotect(p+page*pageSize, pageSize, PROT_WRITE);
		how[page] = PROT_WRITE;
	}

}

static void set_signal(void)
{
	struct sigaction action;
	int rc;

	action.sa_sigaction = segv_handler;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGSEGV);
	action.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &action, &old_action);
	DIE(rc == -1, "sigaction");
}

static void restore_signal(void)
{
	struct sigaction action;
	int rc;

	action.sa_sigaction = old_action.sa_sigaction;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGSEGV);
	action.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &action, NULL);
	DIE(rc == -1, "sigaction");
}

int main(void)
{
	int rc;
	char ch;

	pageSize = getpagesize();

	/* TODO 1 - Map 3 pages with the desired memory protection
	 * Use global 'p' variable to keep the address returned by mmap
	 * Use mprotect to set memory protections based on global 'how' array
	 * 'how' array keeps protection level for each page
	 */

	p = mmap(0, 3*pageSize, PROT_NONE , MAP_SHARED | MAP_ANONYMOUS, 0, 0);
	rc = mprotect(p, pageSize, PROT_NONE);
	rc = mprotect(p + pageSize, pageSize, PROT_READ);
	rc = mprotect(p + pageSize * 2, pageSize, PROT_WRITE);

	set_signal();

	/* TODO 1 - Access these pages for read and write */
	ch = p[0];
	ch = p[pageSize];
	ch = p[pageSize*2];

	p[0] = 'X';
	p[pageSize] = 'X';
	p[pageSize*2] = 'X';

	restore_signal();

	/* TODO 1 - unmap */
	rc = munmap(p, pageSize*3);
	DIE(rc == -1, "munmap");

	return 0;
}
