#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

typedef struct	s_flags 
{
	uint64_t hash;
	uint64_t zero;
	uint64_t minus;
	uint64_t plus;
	uint64_t space;
	uint64_t width;
}				t_flags;

int				ft_printf(const char *format, ...);
void			print_flags(t_flags *flags);

#endif