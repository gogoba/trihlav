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

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavIFactory.hpp"
#include "trihlavLib/trihlavKeyListPresenter.hpp"
#include "trihlavLib/trihlavPswdChckPresenter.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"

namespace trihlav {

  KeyManager& IFactory::getKeyManager() const {
    BOOST_LOG_NAMED_SCOPE("IFactory::getKeyManager()");
    static KeyManager theKeyManager;
    return theKeyManager;
  }
  
IKeyListPresenter* IFactory::createKeyListPresenter() const {
  BOOST_LOG_NAMED_SCOPE("IFactory::createKeyListPresenter()");
	return new KeyListPresenter(*this);
}

IPswdChckPresenter* IFactory::createPswdChckPresenter() const {
	return new PswdChckPresenter(*this);
}

YubikoOtpKeyPresenterI* IFactory::createYubikoOtpKeyPresenter() const {
	return new YubikoOtpKeyPresenter(*this);
}

}  // namespace trihlav


