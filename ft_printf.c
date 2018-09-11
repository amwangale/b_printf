/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwangal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 23:26:28 by amwangal          #+#    #+#             */
/*   Updated: 2018/09/11 00:55:50 by amwangal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void    ft_putchar(char c)
{
    write (1, &c, 1);
}

int ft_putstr(char const *str)
{
    return (write(1, str, strlen(str)));
}

int nbr_len(int nbr, int base)
{
    int i;
    size_t base_nb;
    base_nb = base;
    i = 0;
    if (!nbr)
        return (1);
    while (nbr && ++i)
        nbr /= base_nb;
    return (i);
}

int putnbr_base(int nbr, int base)
{
    int i;
    char *str;
    int len;
    char num;
    int sign;

    i = 0;
    len = nbr_len(nbr, base);
    str = (char *)malloc(sizeof(char) * (len + 1));
    str[len] = '\0';
    while (nbr != 0)
    {
        len--;
        num = ("0123456789abcdef"[nbr % base]);
        str[len] = num;
        nbr /= base;
        i++;
    }
    return (ft_putstr(str));
}

ssize_t handle_char(char **string, va_list ap)
{
    ft_putchar(va_arg(ap, int));
    return (1);
}

ssize_t handle_str(char **string, va_list ap)
{
    char    *str;
    str = va_arg(ap, char *);
    ft_putstr(str);
    return (strlen(str));
}

ssize_t handle_int(char **string, va_list ap)
{
    int nb;
    nb = va_arg(ap, int);
    return(putnbr_base(nb, 10));
}

ssize_t handle_uns(char **string, va_list ap)
{
    unsigned int nb;
    nb = va_arg(ap, unsigned int);
    return(putnbr_base(nb, 10));
}

ssize_t handle_oct(char **string, va_list ap)
{
    int nb;
    nb = va_arg(ap, int);
    return(putnbr_base(nb, 8));
}

ssize_t handle_hex(char **string, va_list ap)
{
    int nb;
    nb = va_arg(ap, int);
    return(putnbr_base(nb, 16));
}

int handle_args(char *str, va_list ap)
{
    if (*str == 's')
        return (handle_str(&str, ap));
    else if (*str == 'c')
        return (handle_char(&str, ap));
    else if (*str == 'd')
        return (handle_int(&str, ap));
    else if (*str == 'i')
        return (handle_int(&str, ap));
    else if (*str == 'o')
        return (handle_oct(&str, ap));
    else if (*str == 'u')
        return (handle_uns(&str, ap));
    else if (*str == 'x')
        return (handle_hex(&str, ap));
    else
        return (-1);
}


int ft_printf(char *str, ...)
{
    va_list ap;
    int result;
    char *next;

    va_start(ap, str);
    while (*str)
    {
        next = strchr(str, '%');
        if (!next)
        {
            result += write(1, str, strlen(str));
            str++;
        }
        else if (next > str)
            result += write(1, str, (next - str));
        else
            result += handle_args(++str, ap);
        str++;
    }
    va_end(ap);
    return (result);
    }
    
    int main(void)
{
    ft_printf("%s", "hello");
    printf("\n%s\n", "hello");
    ft_printf("%c", 'a');
    printf("\n%c\n", 'a');
    ft_printf("%d", 100);
    printf("\n%d\n", 100);
    ft_printf("%i", 100);
    printf("\n%i\n", 100);
    ft_printf("%o", 100);
    printf("\n%o\n", 100);
    ft_printf("%u", 100);
    printf("\n%u\n", 100);
    ft_printf("%x", 100);
    printf("\n%x\n", 100);
}
