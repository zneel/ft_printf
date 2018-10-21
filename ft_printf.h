#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>


#define	HASH			(0x01U << 0x00U)
#define	ZERO			(0x01U << 0x01U)
#define	LEFT			(0x01U << 0x02U)
#define	PLUS			(0x01U << 0x03U)
#define	SPACE			(0x01U << 0x04U)
#define UPPERCASE		(0x01U << 0x05U)
#define F_C             (0x01U << 0x06U)
#define F_S             (0x01U << 0x07U)
#define F_L             (0x01U << 0x08U)
#define F_LL            (0x01U << 0x09U)
#define F_P             (0x01U << 0x0AU)

int				ft_printf(const char *format, ...);

#endif