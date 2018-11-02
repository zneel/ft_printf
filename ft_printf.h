#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>


#define	HASH			(1U << 0U)
#define	ZERO			(1U << 1U)
#define	LEFT			(1U << 2U)
#define	PLUS			(1U << 3U)
#define	SPACE			(1U << 4U)
#define UPPERCASE		(1U << 5U)
#define F_C             (1U << 6U)
#define F_S             (1U << 7U)
#define F_L             (1U << 8U)
#define F_LL            (1U << 9U)
#define F_P             (1U << 10U)

int				    ft_printf(const char *format, ...);
int					ft_atoi(const char *s);
int					ft_isdigit(int c);
void				ft_putstr(char const *s);
void				ft_putchar(char c);
void				ft_putnbr(long long n);
size_t				ft_nbrlen(int nb);
size_t				ft_strlen(const char *s);

#endif