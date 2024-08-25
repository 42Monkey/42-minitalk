#include "../include/minitalk.h"

volatile sig_atomic_t	g_status = 0;

void	handle_signal(int signum)
{
	(void)signum;
	g_status = 1;
}

void	error(const char *message)
{
	write(2, message, ft_strlen(message));
	exit (1);
}

void	send_byte(int pid, unsigned char byte)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_status = 0;
		if ((byte & (1 << bit)) != 0)
		{
			if (kill(pid, SIGUSR2) == -1)
				error ("Error: CLIENT SIGUSR2\n");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				error ("Error: CLIENT SIGUSR1\n");
		}
		while (!g_status)
		{
		}
		bit--;
	}
}

void	send_message(int pid, const char *message)
{
	size_t	i;

	i = 0;
	while (message[i] != '\0')
	{
		send_byte(pid, (unsigned char)message[i]);
		i++;
	}
	send_byte(pid, '\0');
	send_byte(pid, '\n');
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
		error ("Error: ./client PID message\n");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		error ("Error: PID\n");
	message = argv[2];
	if (message == NULL || *message == '\0')
		error ("Error: message\n");
	if (signal(SIGUSR1, handle_signal) == SIG_ERR)
		error ("Error: signal handler\n");
	send_message(pid, message);
	return (0);
}
