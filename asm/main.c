#include <asm/unistd.h>             /* __NR_write */
#include <unistd.h>                 /* STDOUT_FILENO */
#include <string.h>                 /* strlen() */

#define STDOUT STDOUT_FILENO

int main(int argc, char* argv[])
{
	char* c = "coucou";
	int res;

	__asm__ (
		"movl %2, %%ebx;"
		"int $0x80;"

		:"=a" (res)
		:"0" (__NR_write), "I" (STDOUT), "c" (c), "d" (strlen(c))
		:"ebx"
	);

	/*asm volatile (
		"mov [rbp-0x4], edi"
		"mov [rbp-0x10], rsi"
		"lea rdi, [rip+0x94]"
		"call 0x550"
		"mov eax, 0x0"
		"leave"
		"ret"
	);*/

	return 0;
}