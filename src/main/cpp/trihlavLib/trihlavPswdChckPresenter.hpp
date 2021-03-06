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

#ifndef TRIHLAV_PSWD_CHCK_PRESENTER_HPP_
#define TRIHLAV_PSWD_CHCK_PRESENTER_HPP_

#include <memory>

#include "trihlavLib/trihlavGlobals.hpp"
#include "trihlavLib/trihlavPswdChckPresenterIface.hpp"

namespace trihlav {

    class FactoryIface;

    class PswdChckViewIface;

    class MessageViewIface;

/**
 * Main functionality, checks the one passwords.
 */
    class PswdChckPresenter : public PswdChckPresenterIface {
        mutable PswdChckViewIfacePtr m_View{nullptr};
        mutable MessageViewIfacePtr m_MessageView{nullptr};
    public:
        PswdChckPresenter(FactoryIface &pFactory);

        virtual ~PswdChckPresenter() override;

        PswdChckViewIface &getView() override;

        MessageViewIface &getMessageView() override;

        virtual void okPressed();

        static const char *K_MSG_TITLE;
        static const char *K_PSWD_NOT_OK;
        static const char *K_PSWD_OK;
    };

} /* namespace trihlav */

#endif /* TRIHLAV_PSWD_CHCK_PRESENTER_HPP_ */
