



#include "../../../includes/executing.h"



int	builtin_cd(char **args, t_shell *sh)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*oldpwd;

	oldpwd = get_env_value(sh->env, "PWD");
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		path = get_env_value(sh->env, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
		path = get_env_value(sh->env, "OLDPWD");
	else
		path = args[1];
	if (!path || chdir(path) != 0)
		return (ft_putstr_fd("cd: invalid path\n", STDERR_FILENO), 1);
	getcwd(cwd, PATH_MAX);
	update_env_var(&sh->env, "OLDPWD", oldpwd);
	update_env_var(&sh->env, "PWD", cwd);
	return (0);
}
