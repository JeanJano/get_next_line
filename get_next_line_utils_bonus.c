/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:18:21 by jsauvage          #+#    #+#             */
/*   Updated: 2022/06/16 14:31:53 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	found_nl(t_list *tmp)
{
	int		i;
	t_list	*current;

	if (tmp == NULL)
		return (0);
	current = ft_lstlast(tmp);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *tmp)
{
	t_list	*current;

	current = tmp;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	generate_line(char **line, t_list *tmp)
{
	int	i;
	int	len;

	len = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		tmp = tmp->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	free_tmp(t_list *tmp)
{
	t_list	*current;
	t_list	*next;

	current = tmp;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
