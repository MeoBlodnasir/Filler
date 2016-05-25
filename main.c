/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:33:38 by aduban            #+#    #+#             */
/*   Updated: 2016/05/25 19:41:47 by aduban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void print_piece(t_meta meta)
{
	int i = 0;
	int j = 0;
	while (i < meta.pheight)
	{
		while (j < meta.pwidth)
		{
			fprintf(stderr, "%c", meta.piece[j][i]);
			j++;
		}
		j = 0;
		i++;
		fprintf(stderr, "\n");

	}
}
void print_tab(t_meta meta)
{
	int i = 0;
	int j = 0;
	while (i < meta.height)
	{
		while (j < meta.width)
		{
			fprintf(stderr, "%c", meta.tab[j][i]);
			j++;
		}
		j = 0;
		i++;
		fprintf(stderr, "\n");

	}
}
int fill_meta(char *str, t_meta *meta)
{
	static int nb;
	if (ft_strncmp(str, "$$$", 3) == 0)
	{
		if (str[10] == '1')
		{
			meta->c = 'o';
			meta->e = 'x';
		}
		else if (str[10] == '2')
		{
			meta->c = 'x';
			meta->e = 'o';
		}
	}
	else if (ft_strncmp(str, "Plateau", 7) == 0)
	{
		fprintf(stderr, "checking plateau size..\n");
		static char **tab;
		if (tab != NULL)
			return 0;
		tab = ft_strsplit(str, ' ');
		meta->height = ft_atoi(tab[1]);
		meta->width = ft_atoi(tab[2]);
		free(tab[0]);
		free(tab[1]);
		free(tab[2]);
		free(tab);
		meta->tab = (char **)malloc(sizeof(char*) * meta->width);
		int i = 0;
		while (i < meta->width)
		{
			meta->tab[i] = (char *)malloc(sizeof(char) * meta->height);
			i++;
		}
	}
	else if (ft_isdigit(str[0]) && ft_isdigit(str[2]) &&ft_isdigit(str[1]))
	{
		fprintf(stderr, "filling tab..\n");
		char *nbp;
		nbp = ft_strsub(str, 0, 3);
		int i = 0;
		while (i < meta->width && i+4 < (int)ft_strlen(str))
		{
			meta->tab[i][ft_atoi(nbp)] = str[i+4];
			i++;
		}
	}
	else if (ft_strncmp(str, "Piece", 5) == 0)
	{
		
		fprintf(stderr, "checking piece size..\n");

		static char **tab;
		if (tab != NULL)
			return 0;
		char * str2 = ft_strsub(str, 0, ft_strlen(str) -1);
		tab = ft_strsplit(str2, ' ');
		meta->pwidth = ft_atoi(tab[2]);
		meta->pheight = ft_atoi(tab[1]);
		free(tab[0]);
		free(tab[1]);
		free(tab[2]);
		free(tab);
		meta->piece = (char **)malloc(sizeof(char*) * meta->pwidth);
		int i = 0;
		while (i < meta->pwidth)
		{
			meta->piece[i] = (char *)malloc(sizeof(char) * meta->pheight);
			i++;
		}

	}
	else if (str[0] == '*' || str[0] == '.')
	{	fprintf(stderr, "filling piece...\n");	

		int i = 0;
		while (i < meta->pwidth)
		{
			meta->piece[i][nb] = str[i];
			i++;
		}
		nb++;
		if (nb == meta->pheight)
		{
			fprintf(stderr, "piece filling complete\n");
			nb = 0;
			return 1;
		}
			fprintf(stderr, "one line piece filling complete\n");

	}
	return 0;
}


int	check_spot(int i, int j, t_meta *meta)
{
	int a = 0;
	int b= 0;
	int ok = 0;
	while (b < meta->pheight)
	{
		while (a < meta->pwidth)
		{
			if (meta->piece[a][b] == '*')
			{
			//	fprintf(stderr, "comparing mychar %c", ft_toupper(meta->c));
				if (j+a < meta->width && i+b < meta->height && (meta->tab[j+a][i+b] == meta->c ||meta->tab[j+a][i+b] == ft_toupper(meta->c))  )
				{
					ok++;
				}
				else if (j+a < meta->width && i+b < meta->height && (meta->tab[j+a][i+b] == meta->e ||meta->tab[j+a][i+b] == ft_toupper(meta->e))  )
				{
					return 0;
				}
			}
			a++;
		}
		a = 0;
		b++;
	}
	if (ok == 1)
		return 1;
	else
		return 0;
}

void	play(t_meta *meta)
{
	fprintf(stderr, "trying to play\n");
	int i = 0;
	int j = 0;
	int h = 0;
	while (i < meta->height)
	{
		while (j < meta->width)
		{
				h++;
			if (check_spot(i, j, meta) == 1){
				fprintf(stderr, "PLAYING NOW %d %d\n", i, j);
				char *xstr = ft_itoa(i);	
				char *ystr = ft_itoa(j);	
				char *tmp = ft_strjoin(xstr, " ");
				char *tmp2 = ft_strjoin(tmp, ystr);
				char *fin = ft_strjoin(tmp2, "\n");
				write(1, fin, ft_strlen(fin));
				free(xstr);
				free(ystr);
				free(tmp);
				free(tmp2);
				free(fin);
				//ft_printf("%d %d\n");
				return;
			}
			j++;
		}
		j = 0;
		i++;
	}
	fprintf(stderr, "PLAY NOT FOUND\n");
	exit(0);
}


void free_all(t_meta meta)
{
	int i = 0;
	while (i < meta.pwidth) {
		free(meta.piece[i]);
	}
	free(meta.piece);
	i = 0;
	while (i < meta.width) {
		free(meta.tab[i]);
	}
	free(meta.tab);
}

int main(void)
{
	t_meta meta;
	char *str;
	while (42)
	{
		fprintf(stderr, "NEW TURN\n");
		while (get_next_line(0, &str) == 1)
		{
			int ret = 0;
			ret  = fill_meta(str, &meta);	
			if (ret) {
				fprintf(stderr, "width  %d, height %d, mychar %c\n", meta.width, meta.height, meta.c);
				//	print_tab(meta);
				//	print_piece(meta);
				play(&meta);
			//	free_all(meta);
				ret = 0;
			}
		}
	}
	//play(&meta);
}
