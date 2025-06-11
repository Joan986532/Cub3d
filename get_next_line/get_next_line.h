/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:41:19 by jnauroy           #+#    #+#             */
/*   Updated: 2025/06/11 11:28:30 by npapashv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_write_right(char *buffer);
char	*ft_write_left(char *string);
int		ft_free(char *buffer, char *temp, char *string, char *sentence);
char	*ft_read_buffer(int fd, char *buffer, char *string);

#endif
