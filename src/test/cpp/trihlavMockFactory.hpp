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
#ifndef TRIHLAV_MOCK_FACTORY_HPP_
#define TRIHLAV_MOCK_FACTORY_HPP_

#include <memory>
#include <gmock/gmock.h>

#include "trihlavLib/trihlavFactoryIface.hpp"

#include "trihlavMockOs.hpp"

namespace trihlav {

class MockYubikoOtpKeyView;
class MockYubikoOtpKeyPresenter;
class MockKeyListView;

/**
 * @brief Mock factory.
 */
struct MockFactory: virtual public FactoryIface {

	testing::NiceMock< MockOs > m_MockOs;

	MOCK_METHOD0(createMainPanelView,MainPanelViewIfacePtr ());
	MOCK_METHOD0(createKeyListPresenter,KeyListPresenterIfacePtr () );
	MOCK_METHOD0(createKeyListView,KeyListViewIfacePtr () );
	MOCK_METHOD0(createPswdChckView,PswdChckViewIfacePtr () );
	MOCK_METHOD0(createYubikoOtpKeyView,YubikoOtpKeyViewIfacePtr () );
	MOCK_METHOD0(createMessageView, MessageViewIfacePtr () );
	MOCK_METHOD0(createSysUserListView,SysUserListViewIfacePtr () );
	MOCK_METHOD0(createLoginView,LoginViewIfacePtr() );
	MOCK_METHOD0(getOsIface,OsIface& () );
	MockFactory();
	virtual ~MockFactory(){}
};


}

#endif /* TRIHLAV_MOCK_FACTORY_HPP_ */
