/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:22:22 by lfiorell          #+#    #+#             */
/*   Updated: 2025/04/23 17:28:56 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const *argv[])
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		print_usage();
		return (1);
	}
	data = init(argc, (char **)argv);
	if (!data)
	{
		print_usage();
		return (1);
	}
	return (0);
}
