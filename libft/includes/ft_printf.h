/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: severi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:54:01 by severi            #+#    #+#             */
/*   Updated: 2022/06/06 10:41:54 by severi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

# define VALID_FORMAT "bcdfiopsuxX"
# define VALID_FLAGS "+- 0#"
# define VALID_WIDTH "0123456789"
# define VALID_PREC "0123456789"
# define VALID_SPECI "llLhh"

typedef struct s_flags
{
	int			len;
	int			spec;
	int			width;
	int			prec;
	int			sharp;
	int			minus;
	int			plus;
	int			space;
	int			zero;
}				t_flags;

typedef struct s_calc
{
	int			len1;
	int			len2;
	int			len1_static;
	int			len2_static;
	int			max;
	int			min;
	int			sum;
	int			ten_dec;
}				t_calc;

int				ft_printf(const char *format, ...);
void			ft_round(char **result, int precision);
void			fill_prec(char *ret, char *str, int size);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
void			ft_swap(char *a, char *b);
char			*ft_strrev(char *str);
int				ft_str_isdigit(char *s);
char			*ft_dftoa(double x);
char			*ft_ldftoa(long double x);
char			*ft_bin_to_int(char *vlq);
char			*ft_bin_to_dec(char *vlq);
void			calculate_float(char *mantissa, int exp, char **res);
void			calculate_float_l(char *mantissa, int exp, char **res);
int				get_exp(char *exp_str);
int				get_exp_l(char *exp_str);
char			**ft_frexp(double x);
char			**ft_frexpl(long double x);
void			vlq_calculate_info(t_calc *info, char *s1, char *s2);
void			free_res(char **res);
void			free_calc(t_calc *info);
char			*vlq_sum(char *s1, char *s2);
char			*vlq_multiply(char *s1, char *s2);
char			*vlq_power_of_two(int n);
char			*vlq_power_of_five(int n);
int				power_of_two(int n);
char			*vlq_raise_pow_ten(char *vlq, int n);
void			vlq_n_shift(char *s, int size, int shifts);
void			vlq_shift_left(char *s, int size);
void			vlq_initialize(char *vlq, int c, int size);
void			vlq_char_conv(t_calc *info, char *s1, char *s2);
void			vlq_char_conv_rev(char *s, int size);
void			vlq_char_conv_rev_both(t_calc *info, char *s1, char *s2);
int				ft_print_c_ntimes(char c, int n);
int				ft_putnchar(const char *s, size_t n);
int				ft_putcx(char c, int n);
int				ft_lookforchar(const char *s, int c);
char			*ft_basetoa(unsigned long n, unsigned long base, char sign);
int				print_before(t_flags *flags, int chars_printed, char *s,
					char c);
int				print_int(t_flags *flag, int c_p, char *s, char c);
int				print_u_int(t_flags *flag, int c_p, char *s, char c);
int				print_minus(t_flags *flag, int c_p, char *s, char c);
int				print_section(t_flags *flag, int c_p, char *s, char c);
int				print_str_w_flags(t_flags *flag, int c_p, char *s);
int				print_w_zeros(t_flags *flag, int c_p, char *s, char c);
int				print_sharp_w_spaces(t_flags *flag, int c_p, char *s, char c);
int				print_sharp_w_zeros(t_flags *flag, int c_p, char *s, char c);
int				print_normal(t_flags *flag, int c_p, char *s, char c);
size_t			count_digits(long c);
void			ft_add_zeros(char **str, int zeros);
int				print_b(t_flags *flag_s, va_list ap, int chars_printed);
int				print_c(char c);
int				print_char(t_flags *flag_s, char c, int chars_printed);
int				print_d(t_flags *flag_s, va_list ap, int chars_printed);
int				print_f(t_flags *flag_s, va_list ap, int chars_printed);
int				print_i(t_flags *flag_s, va_list ap, int chars_printed);
int				print_o(t_flags *flag_s, va_list ap, int chars_printed);
int				print_p(t_flags *flag_s, va_list ap, int chars_printed);
int				print_s(t_flags *flag_s, char *s, int chars_printed);
int				print_u(t_flags *flag_s, va_list ap, int chars_printed);
int				print_x(t_flags *flag_s, va_list ap, int chars_printed);
int				print_big_x(t_flags *flag_s, va_list ap, int chars_printed);
t_flags			*return_flags(const char *flags);
uintmax_t		unsigned_conv(t_flags *flag_s, va_list ap);
uintmax_t		signed_conv(t_flags *flag_s, va_list ap);
void			init_flags(t_flags *flag_s, const char *flags);
void			fix_overrides(t_flags *flag_s, const char c);
int				is_plus(t_flags *flag, int c_p, char **s, char c);
int				is_sharp(int c_p, char c);
int				print_sign(t_flags *flag, int c_p, char **s);
void			free_flags(t_flags *flags);
char			*shorten_chars(char *str, int start, int end);
void			ft_add_zeros(char **str, int zeros);
int				match_function(t_flags *flags, va_list ap, int c,
					int printed_c);
int				read_flags(char *flags, va_list ap);

#endif
