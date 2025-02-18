





#include "../../../includes/executing.h"

int	builtin_exit(char **args, t_shell *sh)
{
	int	exit_code;

	exit_code = sh->exit_status;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1])
	{
		if (!ft_isnumber(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			exit_code = 2;
		}
		else if (args[2])
			return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO), 1);
		else
			exit_code = ft_atoi(args[1]);
	}
	free_shell(sh);
	exit(exit_code);
}