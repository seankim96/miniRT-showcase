/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:50:42 by seungjuk          #+#    #+#             */
/*   Updated: 2025/06/26 16:07:44 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	swap(void *a, void *b, size_t size)
{
	void	*temp;

	temp = ft_calloc(1, size);
	ft_memcpy(temp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, temp, size);
	free(temp);
}

static int	partition(void *start, int l_h[2], \
					size_t size, t_bool (*comparator)(void *a, void *b))
{
	void	*pivot;
	void	*current;
	int		i;
	int		j;

	j = l_h[0];
	i = l_h[0] - 1;
	pivot = (char *)start + l_h[1] * size;
	while (j < l_h[1])
	{
		current = (char *)start + j * size;
		if (comparator(current, pivot) == true)
		{
			i++;
			swap((char *)start + i * size, current, size);
		}
		j++;
	}
	swap((char *)start + (i + 1) * size, pivot, size);
	return (i + 1);
}

void	quick_sort(void *start, int l_h[2], \
					size_t size, t_bool (*comparator)(void *a, void *b))
{
	int	pivot_index;
	int	low;
	int	high;

	low = l_h[0];
	high = l_h[1];
	if (low > high)
		return ;
	pivot_index = partition(start, (int [2]){low, high}, size, comparator);
	quick_sort(start, (int [2]){low, pivot_index - 1}, size, comparator);
	quick_sort(start, (int [2]){pivot_index + 1, high}, size, comparator);
}
