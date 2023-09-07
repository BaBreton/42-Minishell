/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:54:13 by babreton          #+#    #+#             */
/*   Updated: 2023/06/08 14:07:40 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		count_print;
	int		i;
	va_list	args;

	i = -1;
	count_print = 0;
	va_start(args, format);
	while (format[++i])
		count_print += brain(&i, format[i], format[i + 1], args);
	return (count_print);
}

int	brain(int *i, char now, char next, va_list args)
{
	int	count_print;

	if (now == '%' && next)
	{
		count_print = check_args(next, args);
		(*i)++;
	}
	else
		return (write(1, &now, 1), 1);
	return (count_print);
}

int	check_args(char next, va_list args)
{
	int	j;
	int	count_print;

	j = -1;
	while (FORMAT[++j])
	{
		if (next == FORMAT[j])
			count_print = thumb(FORMAT[j], args);
	}
	return (count_print);
}

int	thumb(char thumbnail, va_list args)
{
	if (thumbnail == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (thumbnail == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (thumbnail == '%')
		return (ft_putchar('%'));
	if (thumbnail == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (thumbnail == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (thumbnail == 'X')
		return (ft_puthexa(va_arg(args, unsigned int), "0123456789ABCDEF"));
	if (thumbnail == 'x')
		return (ft_puthexa(va_arg(args, unsigned int), "0123456789abcdef"));
	if (thumbnail == 'p')
		return (ft_adress(va_arg(args, void *)));
	if (thumbnail == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	return (-1);
}

int	ft_putchar(int c)
{
	return (write(1, &c, 1), 1);
}

/*int	main(void)
{
	int ret;

	ret = ft_printf(" %s %% %% ", "nik");
	printf("\nValeur mon printf : %d\n", ret);
	ret = printf(" %s %% %% ", "nik");
	printf("\nValeur printf basique : %d", ret);
	return 0;
}*/