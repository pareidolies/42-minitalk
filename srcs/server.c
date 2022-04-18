#include "../includes/server.h"

char	*message;

int	receive_len(int signum)
{
	static unsigned int	len = 0;
	static int		bits = 0;	

	len |= (signum == SIGUSR1);
	bits++;
	if (bits == 16)
	{
		message = malloc(len * sizeof(int));
		if (!message)
			return(-1);
		len = 0;
		bits = 0;
		return (1);
	}
	else
	{
		len = len << 1;
		return (0);
	}
}

int	receive_mssg(int signum, int pid)
{
	static unsigned char	c = 0;
	static int		bits = 0;
	static int		i = 0;

	c |= (signum == SIGUSR1);
	bits++;
	if (bits == 8)
	{
		message[i] = c;
		if (c == '\0')
		{
			ft_putnbr_fd(pid, 1);
			ft_putstr_fd(" : ", 1);
			ft_putstr_fd(message, 1);
			free(message);
			bits = 0;
			i = 0;
			ft_putstr_fd("\n\n", 1);
			ft_putstr_fd_color(LISTEN, 1, ANSI_COLOR_BLUE);
			if (kill(pid, SIGUSR1) == -1)
				ft_putstr_fd(KILL_ERROR, 2);
			return (0);
		}
		bits = 0;
		c = 0;
		i++;
	}
	else
		c = c << 1;
	return (1);
}

int main(int argc, char **argv)
{
	int	pid;

	(void) argv;
	if (argc != 1)
		ft_putstr_fd(PARAMETER_ERROR, 2);
	say_hello();
	pid = getpid();
	if (!set_sigaction())
		return (0);
	ft_putstr_fd(WELCOME_MSSG, 1);
	ft_putstr_fd(ANSI_COLOR_LIGHT_WHITE, 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd(ANSI_COLOR_RESET, 1);
	ft_putstr_fd("\n\n", 1);
	ft_putstr_fd_color(LISTEN, 1, ANSI_COLOR_BLUE);
	while (1)
		//pause();
		usleep(200);
	return (0);
}
