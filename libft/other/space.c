/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   space.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/26 17:51:51 by krioliin       #+#    #+#                */
/*   Updated: 2019/04/05 18:31:34 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		space(char c)
{
	return (c == ' ' || c == '\n' ||
	c == '\t' || c == '\r' || c == '\f' || c == '\v');
}
