/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manykhac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:02:42 by manykhac          #+#    #+#             */
/*   Updated: 2022/06/14 14:22:54 by manykhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buff)
{
	int		len;
	char	*str;

	str = (char *) malloc ((sizeof(char) * BUFFER_SIZE + 1));
	if (!str)
		return (NULL);
	len = 1;
	while (len != 0 && ft_strchr(buff, '\n') == 0)
	{
		len = read(fd, str, BUFFER_SIZE);
		if (len == -1)
		{
			free (str);
			return (NULL);
		}
		str[len] = '\0';
		buff = ft_strjoin(buff, str);
	}
	free (str);
	return (buff);
}

char	*search_line(char *buff)
{
	char	*str;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	str = (char *) malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (buff[i] != '\n' && buff[i])
	{
		str[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*new_buff(char *buff)
{
	char	*str;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (!buff[i])
	{
		free (buff);
		return (NULL);
	}
	str = (char *) malloc(sizeof(char) * (ft_strlen(buff) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (buff[i] != '\0')
		str[j++] = buff[i++];
	str[j] = '\0';
	free (buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*serial_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = read_line(fd, buff);
	if (!buff)
		return (NULL);
	serial_line = search_line(buff);
	buff = new_buff(buff);
	return (serial_line);
}
