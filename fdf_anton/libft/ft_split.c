/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserdyuk <aserdyuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 07:09:47 by aserdyuk          #+#    #+#             */
/*   Updated: 2021/06/11 18:27:08 by aserdyuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	if (s == 0 || s[0] == 0)
		return (0);
	if (s[0] != c)
		words++;
	i = 1;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static void	free_arr(char **s, int j)
{
	int	i;

	i = 0;
	while (s[i] && i < j)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	word_length(const char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

void	split_line(char const *s, char **arr, char c, int words)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (j < words)
	{
		k = 0;
		arr[j] = malloc(word_length(s, c, i) + 1);
		if (arr[j] == NULL)
			free_arr(arr, j);
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			arr[j][k] = s[i];
			i++;
			k++;
		}
		arr[j][k] = '\0';
		j++;
	}
	arr[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
	{
		free(arr);
		return (NULL);
	}
	arr[words] = 0;
	split_line(s, arr, c, words);
	return (arr);
}
