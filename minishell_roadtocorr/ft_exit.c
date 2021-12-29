/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 09:15:23 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/28 11:21:53 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_get_exit_status(int status)
{
	int	exit_status;

	exit_status = 0;
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}

int	ft_wrong_exit_arg(char *code)
{
	int	i;

	i = 0;
	while (ft_is_digit(code[i]))
		i++;
	if (i > 3 || code[i] != '\0' || ft_atoi(code) > 255)
		return (1);
	else
		return (0);
}

int	ft_exit(t_env **env, t_cmd **cmd, char *line, char **argv)
{
	write(1, "exit\n", 5);
	if (!argv[1])
		;
	else if (ft_wrong_exit_arg(argv[1]))
	{
		g_exit_status = 2;
		write(2, "exit: ", 6);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": numeric argument required\n", 28);
	}
	else if (argv[2] != NULL)
	{
		g_exit_status = 1;
		write(2, "exit: ", 6);
		write(2, ": too many arguments\n", 21);
		return (1);
	}
	else
		g_exit_status = ft_atoi(argv[1]);
	free(line);
	ft_free_list_cmd(cmd);
	ft_free_list_env(env);
	exit(g_exit_status);
	return (g_exit_status);
}
