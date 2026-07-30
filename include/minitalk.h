#ifndef MINITALK_H
# define MINITALK_H

# ifndef SA_RESTART
#  define SA_RESTART 0
# endif

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);

#endif
