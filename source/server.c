#include "../include/minitalk.h"

void	error(const char *message)
{
	write(2, message, ft_strlen(message));
	exit (1);
}

void	handle_signal(int signal, siginfo_t *info, void *ucontext)
{
	static int	bit;
	static int	current;

	(void)ucontext;
	if (signal == SIGUSR2)
	{
		current |= (1 << (7 - bit));
	}
	bit++;
	if (bit == 8)
	{
		write(1, &current, 1);
		bit = 0;
		current = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		error ("Error: No acknowledgement to client\n.");
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	pid = getpid();
	ft_putstr_fd("SERVER PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error ("Error: SERVER SIGUSER1\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		error ("Error: SERVER SIGUSER2\n");
	while (1)
	{
		pause();
	}
	return (0);
}
