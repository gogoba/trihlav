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

#include <Wt/WGridLayout>

#include "trihlavWtLoginView.hpp"
#include "trihlavWtStrEdit.hpp"
#include "trihlavWtLabel.hpp"

using Wt::WGridLayout;
using U = Wt::WLength::Unit;
using Wt::WLength;

namespace trihlav {

WtLoginView::WtLoginView() //
:
		itsEdtUserName(new WtStrEdit)  //
				, itsEdtPassword(new WtStrEdit) //
				, itsLblUserName(new WtLabel("User name")) //
				, itsLblPassword(new WtLabel("Password")) //
{
	getDlg().setWidth(WLength(32, U::FontEm));
	WGridLayout* myTopLayout = new WGridLayout;
	{
		itsLblUserName->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(itsLblUserName,0,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsEdtUserName,0,1,1,1,Wt::AlignMiddle);
	}
	{
		itsLblPassword->setWidth(WLength(9.0,U::FontEm));
		myTopLayout->addWidget(itsLblPassword,2,0,1,1,Wt::AlignRight|Wt::AlignMiddle);
		myTopLayout->addWidget(itsEdtPassword,2,1,1,1,Wt::AlignMiddle);
	}
	getDlg().contents()->setLayout(myTopLayout);
}

StrEditIface& WtLoginView::getEdtUserName() {
	return *itsEdtUserName;
}

StrEditIface& WtLoginView::getEdtPassword() {
	return *itsEdtPassword;
}

LabelIface& WtLoginView::getLblUserName() {
	return *itsLblUserName;
}

LabelIface& WtLoginView::getLblPassword() {
	return *itsLblPassword;
}

} /* namespace trihlav */
