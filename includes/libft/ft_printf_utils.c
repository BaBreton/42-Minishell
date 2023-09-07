/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:50:28 by babreton          #+#    #+#             */
/*   Updated: 2023/03/30 10:00:14 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return (ft_putstr("(null)"), 6);
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nb)
{
	int		i;
	char	rev[10];
	int		j;

	i = 0;
	j = 0;
	if (nb == INT_MIN)
		return ((void)write(1, "-2147483648", 11), 11);
	if (nb < 0)
	{
		i += ft_putchar('-');
		nb *= -1;
	}
	while (nb != 0 || j == 0)
	{
		rev[j++] = nb % 10 + '0';
		nb /= 10;
	}
	while (j)
		i += ft_putchar(rev[--j]);
	return (i);
}

int	ft_puthexa(unsigned int nb, char *base)
{
	int		i;
	int		j;
	char	rev[8];

	j = 0;
	i = 0;
	while (nb != 0 || j == 0)
	{
		rev[j++] = base[nb % 16];
		nb /= 16;
	}
	while (j)
		i += ft_putchar(rev[--j]);
	return (i);
}

int	ft_adress(void *ptr)
{
	int				i;
	int				j;
	unsigned long	adress;
	char			*hex;
	char			rev[16];

	if (!ptr)
		return (ft_putstr("(nil)"), 5);
	adress = (unsigned long)ptr;
	hex = "0123456789abcdef";
	j = 0;
	i = 0;
	while (adress != 0 || j == 0)
	{
		rev[j++] = hex[adress % 16];
		adress /= 16;
	}
	i += ft_putstr("0x");
	while (j)
		i += ft_putchar(rev[--j]);
	return (i);
}

int	ft_putunbr(unsigned int nb)
{
	int		i;
	int		j;
	char	rev[10];

	j = 0;
	i = 0;
	while (nb != 0 || j == 0)
	{
		rev[j++] = nb % 10 + 48;
		nb /= 10;
	}
	while (j)
		i += ft_putchar(rev[--j]);
	return (i);
}
