



#include "../../../includes/executing.h"


static void	print_export(t_env_lst *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}



// int	builtin_export(char **args, t_shell *sh)
// {
// 	char	*eq;
// 	int		ret;

// 	ret = 0;
// 	if (!args[1])
// 		return (print_export(sh->env), 0);
// 	while (*(++args))
// 	{
// 		eq = ft_strchr(*args, '=');
// 		if (!eq || !is_valid_env_key(*args))
// 		{
// 			ft_putstr_fd("export: invalid identifier\n", STDERR_FILENO);
// 			ret = 1;
// 			continue;
// 		}
// 		*eq = '\0';
// 		update_env_var(&sh->env, *args, eq + 1);
// 		*eq = '=';
// 	}
// 	return (ret);
// }
