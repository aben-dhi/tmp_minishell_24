/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:55:05 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 06:17:43 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_strjoin_helper(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	new = NULL;
	while (s1[i])
	{
		new[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new[i] = (char)s2[j];
		i++;
		j++;
	}
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup((char *)s2));
	if (s2 == NULL)
		return (ft_strdup((char *)s1));
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = ft_calloc(sizeof(char), i);
	if (new == NULL)
		return (NULL);
	new = ft_strjoin_helper((char *)s1, (char *)s2);
	return (new);
}
