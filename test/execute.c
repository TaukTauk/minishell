# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <term.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

int main(int ac, char **av, char **envp) {
	printf("av[1]===> %s\n", av[1]);
	char **arg;
	int i;
	i = 0;
	int j = 0;
	arg = (char **)malloc(sizeof(char *) * ac + 1);
	if (!arg)
		return (1);
	while (av[++i])
	{
		arg[j] = ft_strdup(av[i]);
		j++;
	}
	arg[j] = NULL;
	
	if (execve(av[1], av, envp) == -1)
	{
		if (access(av[1], F_OK) == 0 && access(av[1], X_OK) != 0)
			ft_putstr_fd("permission denied: ", 2);
		else
			ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(av[1], 2);
	}
}