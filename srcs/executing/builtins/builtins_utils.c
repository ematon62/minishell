
#include "../../../includes/executing.h"

int	is_valid_env_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 0;
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	return (1);
}

void	update_env_var(t_env_lst **env, char *key, char *value)
{
	t_env_lst	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}
	add_env_var(env, key, value);
}

