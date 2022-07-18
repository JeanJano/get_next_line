/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:11:22 by jsauvage          #+#    #+#             */
/*   Updated: 2022/06/16 15:10:13 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	add_to_tmp(t_list **tmp, char *buffer, int size_read)
{
	int		i;
	t_list	*current;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (size_read + 1));
	if (!new_node)
		return ;
	i = 0;
	while (buffer[i] && i < size_read)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*tmp == NULL)
	{
		*tmp = new_node;
		return ;
	}
	current = ft_lstlast(*tmp);
	current->next = new_node;
}

static void	extract_line(t_list *tmp, char **line)
{
	int	i;
	int	j;

	if (tmp == NULL)
		return ;
	generate_line(line, tmp);
	if (*line == NULL)
		return ;
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '\n')
			{
				(*line)[j++] = tmp->content[i];
				break ;
			}
			(*line)[j++] = tmp->content[i++];
		}
		tmp = tmp->next;
	}
	(*line)[j] = '\0';
}

static void	read_file(t_list **tmp, int fd)
{
	char	*buffer;
	int		size_read;

	size_read = 1;
	while (!found_nl(*tmp) && size_read != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		size_read = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*tmp == NULL && size_read == 0) || size_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[size_read] = '\0';
		add_to_tmp(tmp, buffer, size_read);
		free(buffer);
	}
}

static void	clean_tmp(t_list **tmp)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (!tmp || !clean_node)
		return ;
	clean_node->next = NULL;
	last = ft_lstlast(*tmp);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i)
				+ 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_tmp(*tmp);
	*tmp = clean_node;
}

char	*get_next_line(int fd)
{
	static t_list	*tmp = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	read_file(&tmp, fd);
	if (tmp == NULL)
		return (NULL);
	extract_line(tmp, &line);
	clean_tmp(&tmp);
	if (line[0] == '\0')
	{
		free_tmp(tmp);
		tmp = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

// #include <fcntl.h>
// #include <sys/stat.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int fd1;
// 	char *str;
// 	int i;

// 	fd = open("bible.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	i = 1;

// 	while (str)
// 	{
// 		printf("line %d : %s", i, str);
// 		free(str);
// 		str = get_next_line(fd);
// 		i++;
// 	}
// 	free(str);

// 	return (0);
// }