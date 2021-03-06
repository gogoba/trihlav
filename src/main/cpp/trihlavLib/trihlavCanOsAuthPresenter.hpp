/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 der GNU General Public License, wie von der Free Software Foundation,
 Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 veröffentlichten Version, weiterverbreiten und/oder modifizieren.

 Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
 OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
 Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 Siehe die GNU General Public License für weitere Details.

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
 */

#ifndef TRIHLAV_CAN_OS_AUTH_PRESENTER_HPP_
#define TRIHLAV_CAN_OS_AUTH_PRESENTER_HPP_

#include <memory>

#include "trihlavLib/trihlavPresenterBase.hpp"

namespace trihlav {

    class FactoryIface;

    class LoginPresenter;

/**
 * This presenter is able to authenticate the user in underlying
 * operating system, in Linux for example it uses PAM. It is meant 2 be
 * overloaded in a is-a relationship.
 */
    class CanOsAuthPresenter : public PresenterBase {
    protected:

        /**
         * Handles the userl login dialog.
         */
        std::unique_ptr<LoginPresenter> m_LoginPresenter;

        /**
         * Login dialog finished with success.
         */
        virtual void userAccepted(bool pStatus);

        /**
         * will be called when the OS authenticates the user.
         */
        virtual void doProtectedAction(bool pStatus)=0;

    public:

        /// Do nothing, be lazy.
        CanOsAuthPresenter(FactoryIface &pFactory);

        /// Just to be virtual...
        virtual ~CanOsAuthPresenter();

        /**
         * Governing presenter calls this to execute the (in most cases username and password)protected
         */
        virtual void protectedAction();

        LoginPresenter &getLoginPresenter();
    };

} /* namespace trihlav */

#endif /* TRIHLAV_CAN_OS_AUTH_PRESENTER_HPP_ */
