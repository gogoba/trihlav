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

#include <boost/locale.hpp>

#include <Wt/WDialog>
#include <Wt/WTableView>
#include <Wt/WFitLayout>
#include <Wt/WGridLayout>
#include <Wt/WScrollArea>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WModelIndex>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include "trihlavWtListModel.hpp"

#include "trihlavWtPushButton.hpp"
#include "trihlavWtSysUserListIView.hpp"

namespace {
static const Wt::WLength K_DLG_H(40.0, Wt::WLength::Unit::FontEm);
static const Wt::WLength K_DLG_W(30.0, Wt::WLength::Unit::FontEm);
}

namespace trihlav {

using Wt::WTableView;
using Wt::WDialog;
using Wt::WLength;
using Wt::WGridLayout;
using Wt::WFitLayout;
using Wt::WScrollArea;

using Wt::WHBoxLayout;
using Wt::WVBoxLayout;
using Wt::WModelIndexSet;

using boost::locale::translate;
using U = Wt::WLength::Unit;

/**
 * Holds the operating system user list data.
 */
class WtSysUserListModel: public WtListModel<std::string, std::string> {
public:
	WtSysUserListModel() :
			WtListModel<std::string, std::string>( {
					{ translate("System login") }, { translate("Full name") } }) {
	}
};

WtSysUserListView::WtSysUserListView() :
		itsDtaMdl(new WtSysUserListModel), //
		itsSysUserTable(new WTableView) //
{
	BOOST_LOG_NAMED_SCOPE("WtSysUserListView::WtSysUserListView");
	getDlg().setCaption(translate("Add key").str());
	getDlg().setObjectName("WtSysUserListView");
	getDlg().resize(K_DLG_W, K_DLG_H);
	WVBoxLayout* myContentLayout = new WVBoxLayout;
	{
		itsSysUserTable->setObjectName("SysUserTable");

		itsSysUserTable->setModel(itsDtaMdl);
		itsSysUserTable->setAlternatingRowColors(true);
		itsSysUserTable->setCanReceiveFocus(true);
		itsSysUserTable->setColumnResizeEnabled(true);
		itsSysUserTable->setSelectionMode(Wt::SingleSelection);
		myContentLayout->addWidget(itsSysUserTable);
		itsSysUserTable->selectionChanged().connect(this,
				&WtSysUserListView::selectionChanged);

	}
	getDlg().contents()->setLayout(myContentLayout);
	getDlg().contents()->setOverflow(Wt::WContainerWidget::OverflowHidden);
	getDlg().setResizable(true);
	getDlg().finished().connect(this, &WtSysUserListView::finishedSlot);
}

void WtSysUserListView::show(const SysUsers& pUsers) {
	BOOST_LOG_NAMED_SCOPE("WtSysUserListView::show");
	int myCnt = 0;
	itsDtaMdl->clear();
	for (const SysUser& myUser : pUsers) {
		myCnt++;
		BOOST_LOG_TRIVIAL(debug)<<"User: " << myUser.itsLogin;
		itsDtaMdl->addRow(
				WtSysUserListModel::Row_t(std::string(myUser.itsLogin),
						std::string(myUser.itsFullName)));
	}
	BOOST_LOG_TRIVIAL(debug)<<"System users loaded.";
	getDlg().setModal(true);
	getDlg().show();
}

void WtSysUserListView::finishedSlot(WDialog::DialogCode pCode) {
	BOOST_LOG_NAMED_SCOPE("WtSysUserListView::finishedSlot");
	if(pCode == WDialog::DialogCode::Accepted)
		acceptedSig();
}

/**
 * @return a list of ids of the selected keys.
 */
int WtSysUserListView::getSelected() {
	WModelIndexSet mySelected { itsSysUserTable->selectedIndexes() };
	if (mySelected.empty()) {
		return -1;
	}
	return mySelected.begin()->row();
}

const WtSysUserListView::UserRow_t&
WtSysUserListView::getRow(int pId) const {
	return itsDtaMdl->getRow(pId);
}

void WtSysUserListView::selectionChanged() {
	BOOST_LOG_NAMED_SCOPE("WtSysUserListView::selectionChanged");
	this->selectionChangedSig(getSelected());

}

}
/* namespace trihlav */
