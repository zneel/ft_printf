#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>

#define HASH		'#'
#define ZERO		'0'
#define MINUS		'-'
#define PLUS		'+'
#define SPACE		' '
#define SPECIFIER	'%'
#define ASTERISK	'*'

typedef struct	s_flags 
{
	uint_fast8_t hash;
	uint_fast8_t zero;
	uint_fast8_t minus;
	uint_fast8_t plus;
	uint_fast8_t space;
}				t_flags;

int				ft_printf(const char *format, ...);
void			print_flags(t_flags *flags);

#endif