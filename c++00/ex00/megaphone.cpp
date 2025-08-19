/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwizera <mkwizera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:08:32 by mkwizera          #+#    #+#             */
/*   Updated: 2025/08/19 14:25:54 by mkwizera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        int i = 1;
        while ( i < argc)
        {
            int j = 0;
            while(argv[i][j] != '\0')
            {
                argv[i][j] =  (char)toupper(argv[i][j]);
                std::cout << argv[i][j];
                j++;
            }
            if (argv[i] != NULL)
                std::cout << " ";
            i++;
        }
        std::cout << std::endl;
    }
    else 
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    return (0);
}