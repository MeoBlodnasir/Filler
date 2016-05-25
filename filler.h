/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:38:53 by aduban            #+#    #+#             */
/*   Updated: 2016/05/25 16:28:50 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
#include "get_next_line.h"

typedef struct s_meta
{
	char	c;
	char 	e;
	int		width;
	int		height;
	int pwidth;
	int pheight;
	char **tab;
	char **piece;
}				t_meta;

#endif
