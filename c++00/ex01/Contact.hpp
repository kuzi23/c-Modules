/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkwizera <mkwizera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:45:09 by mkwizera          #+#    #+#             */
/*   Updated: 2025/08/19 16:05:11 by mkwizera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_H
#define CONTACT_H

#include "Repertory.hpp"

class Contact {
    public:
        Contact();
        ~Contact();

        void    setName(str name);
        void    setLast(str last);
        void    setNick(str nick);
        void    setPhone(str Phone);
        void    setSecret(str secret);
        str     getName() const;
        str     getLast() const;
        str     getNick() const;
        str     getPhone() const;
        str     getSecret() const;
    
    private:
        str name;
        str last;
        str nick;
        str phone;
        str secret;
};

# endif