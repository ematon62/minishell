



#include "../../../includes/executing.h"


int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (perror("pwd"), 1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}