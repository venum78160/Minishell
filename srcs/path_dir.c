/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msebbane <msebbane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:23:49 by lbally            #+#    #+#             */
/*   Updated: 2022/09/01 15:37:30 by msebbane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_path(void)
{
	if (getcwd(NULL, 0) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", getcwd(NULL, 0));
}

char	*clean_str(char *path)
{
	int		i;
	int		j;
	char	*final;

	i = 0;
	j = 0;
	while (path[i] && !is_letter(path[i]))
		if (path[i] == ' ')
			i++;
	final = malloc(sizeof(char) * (ft_strlen(path) - i) + 1);
	while (path[i])
	{
		final[j++] = path[i];
		i++;
	}
	final[j] = '\0';
	return (final);
}

int	search_slash(char *path)
{
	int	i;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	return (i);
}

char	*add_slash(char *path)
{
	int		i;
	int		j;
	char	*new;

	new = malloc(sizeof(char) * ft_strlen(path) + 2);
	i = -1;
	j = 0;
	while (path[++i])
		new[j++] = path[i];
	new[j] = '/';
	j++;
	new[j] = '\0';
	return (new);
}

void	change_dir(char *path, t_list *alst, t_parse *parse)
{
	char	*new_path;
	char	*res;
	t_list	*new;
	t_parse	*elem;

	new = alst;
	elem = parse;
	new_path = path;
	if (!path)
	{
		while (new)
		{
			if (!ft_strcmp(new->key, "HOME"))
			res = ft_strdup(new->content);
			new = new->next;
		}
		chdir(res);
		update_env(alst, res);
	}
	else if (!ft_strcmp(path, ".."))
	{
		printf("sas3\n");
		new_path = ft_substr(getcwd(NULL, 0), 0, search_slash(getcwd(NULL, 0)));
		chdir((const char *)new_path);
		update_env(alst, new_path);
	}
	else if (!ft_strcmp(path, "~"))
	{   printf("sas2\n");
		while (new)
		{
			if (!ft_strcmp(new->key, "HOME"))
				res = ft_strdup(new->content);
			new = new->next;
		}
		chdir(res);
		update_env(alst, res);
	}
	else
	{
		printf("sas\n");
		res = add_slash(getcwd(NULL, 0));
		new_path = ft_strjoin(res, new_path);
		if (chdir(new_path) == -1)
		{
			perror("chdir");
			ft_substr(path, 3, ft_strlen(path));
		}
		else
			update_env(alst, new_path);
	}
}

// faire relatif
