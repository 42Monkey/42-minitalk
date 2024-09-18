#include "../include/minitalk.h"

/**
 *  Declare and initialize a global variable g_status
 */
volatile sig_atomic_t	g_status = 0;

/**
 * Signal handler function to set g_status to 1
 * @param signum The signal number
 */
void	handle_signal(int signum)
{
	(void)signum;
	g_status = 1;
}

/**
 * Function to display an error message and exit the program
 * @param message The error message to display
 */
void	error(const char *message)
{
	write(2, message, ft_strlen(message));
	exit (1);
}

/**
 * Function to send a byte to the server
 * @param pid The process ID of the server
 * @param byte The byte to send
 */
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

/**
 * Function to send a message to the server
 * @param pid The process ID of the server
 * @param message The message to send
 */
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

/**
 * Main function to handle command line arguments and send a message to the server
 * @param argc The number of command line arguments
 * @param argv The array of command line arguments
 * @return 0 on success
 */
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
