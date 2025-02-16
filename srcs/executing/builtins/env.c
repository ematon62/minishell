



#include "../../../includes/executing.h"


int	builtin_env(t_env_lst *env)
{
	while (env)
	{
		if (env->is_env && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
