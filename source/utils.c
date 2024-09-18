#include "../include/minitalk.h"

/**
 * Calculates the length of a string by iterating through each character until the null terminator is reached.
 *
 * @param s The input string.
 * @return The number of characters in the string.
 */
size_t	ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return (i);
}

/**
 * Converts a string to an integer.
 *
 * @param nptr The input string.
 * @return The converted integer.
 */
int	ft_atoi(const char *nptr)
{
    int	i;
    int	sign;
    int	result;

    i = 0;
    sign = 1;
    result = 0;
    while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
        i++;
    if (nptr[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (nptr[i] == '+')
        i++;
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        result = result * 10 + (nptr[i] - '0');
        i++;
    }
    return (sign * result);
}

/**
 * Outputs an integer to the given file descriptor.
 *
 * @param n The integer to output.
 * @param fd The file descriptor to write to.
 */
void	ft_putnbr_fd(int n, int fd)
{
    if (n == -2147483648)
    {
        ft_putstr_fd("-2147483648", fd);
        return ;
    }
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        n = -n;
    }
    if (n >= 10)
    {
        ft_putnbr_fd(n / 10, fd);
    }
    ft_putchar_fd(n % 10 + '0', fd);
}

/**
 * Outputs a character to the given file descriptor.
 *
 * @param c The character to output.
 * @param fd The file descriptor to write to.
 */
void	ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

/**
 * Outputs a string to the given file descriptor.
 *
 * @param s The string to output.
 * @param fd The file descriptor to write to.
 */
void	ft_putstr_fd(char *s, int fd)
{
    int	i;

    i = 0;
    while (s[i])
    {
        write(fd, &s[i], 1);
        i++;
    }
}
