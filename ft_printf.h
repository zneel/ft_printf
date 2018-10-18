#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

typedef struct	s_flags 
{
	uint_fast64_t hash;
	uint_fast64_t zero;
	uint_fast64_t minus;
	uint_fast64_t plus;
	uint_fast64_t space;
	uint_fast64_t width;
}				t_flags;

int				ft_printf(const char *format, ...);
void			print_flags(t_flags *flags);

#endif