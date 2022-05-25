/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acouliba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 07:02:16 by acouliba          #+#    #+#             */
/*   Updated: 2021/11/27 07:02:19 by acouliba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

int		decremet(int already);
int		ft_atoi2(const char *str);
char	*ft_putchar(char c);
void	ft_putstr(char *str, int *count);
char	*ft_printadress(void *addr, int plus);
char	**ft_split2(char const *s, char c);
void	ft_print_hex(unsigned long long int adrr, char *str,
			int *count, int plus);
char	*get_hex(unsigned long long int adrr, int plus);
void	myfree(char **tab);
int		start(const char *string, char *str, int *count);
int		len_nbr2(unsigned long n);
char	*ft_itoa2(unsigned long n);
int		get(char *str);
int		my_ft_strlen(char *str);
int		ft_abs(int a);
void	wr(char c, int *count);
int		ft_str_is_digit(char *str);
int		another(char *str, int *count, char l, int already);
int		another2(char *str, int *count, int already);
char	sep(char *str);
int		str_contains(char *str, char c, int max);
void	myptf(char *str, int already, int *count, char l);
void	case_c(char c, int *count, char *st);
void	case_p(void *v, int *count, char *st);
void	case_d(int a, int *count, char *st);
void	case_u(int u, int *count, char *st);
void	case_x(unsigned long long int adrr, int plus, int *count, char *st);
void	case_nbr(char *string, int *count, char *st, int already);
void	case_str_chiant(char *str, int already, int *count);
void	case_s(char *string, int *count, char *st);
int		my_print(va_list ap, char *str, int *count);
int		ft_printf(const char *string, ...);

#endif
