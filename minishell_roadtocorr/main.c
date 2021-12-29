#include "parsing.h"

unsigned int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_env				*env;
	int					ret;

	if (argc > 1 || argv[1] != NULL)
		return (0);
	g_exit_status = 0;
	env = ft_envp_to_tenv(envp);
	ret = 0;
	while (!ret)
		ret = ft_prompt(&env);
	write(1, "exit\n", 5);
	exit(g_exit_status);
	return (0);
}
