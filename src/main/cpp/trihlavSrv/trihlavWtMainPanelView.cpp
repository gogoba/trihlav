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

#include <string>
#include <boost/locale.hpp>

#include <Wt/WLineEdit.h>
#include <Wt/WMenu.h>
#include <Wt/WMessageBox.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>

#include "trihlavLib/trihlavLogApi.hpp"
#include "trihlavLib/trihlavCannotCastImplementation.hpp"
#include "trihlavLib/trihlavVersion.hpp"

#include "trihlavWtMainPanelView.hpp"
#include "trihlavWtPswdChckView.hpp"
#include "trihlavWtKeyListView.hpp"

using Wt::WNavigationBar;
using Wt::WMenu;
using Wt::WMenuItem;
using Wt::WString;
using Wt::WStackedWidget;
using Wt::WPopupMenu;
using Wt::WLineEdit;
using Wt::WWidget;
using Wt::WContainerWidget;
using Wt::WVBoxLayout;
using Wt::WString;
using Wt::StandardButton;
using Wt::Icon;

using namespace std;
using boost::locale::translate;
using boost::log::trivial::debug;

namespace trihlav {

    const string toString(const PanelName &pName) {
        if (pName == PanelName::KeyList) {
            return "KeyList";
        } else if (pName == PanelName::PswdCheck) {
            return "PswdCheck";
        } else if (pName == PanelName::Settings) {
            return "Settings";
        } else {
            return "Unknown panel";
        }
    }

    void WtMainPanelView::add(const string &pLocalizedName, const PanelName &pName,
                              KeyListViewIface &pKeyListView) {
        WtKeyListView *myKeyListView = dynamic_cast<WtKeyListView *>(&pKeyListView);
        if (myKeyListView == 0) {
            //TODO add rtti of the base type to the err msg
            throw CannotCastImplementation("WtKeyListView");
        }
        addView(pLocalizedName, pName, *myKeyListView);
    }

    void WtMainPanelView::add(const string &pLocalizedName, const PanelName &pName,
                              PswdChckViewIface &pPswdChckView) {
        WtPswdChckView *myPswdChckView =
                dynamic_cast<WtPswdChckView *>(&pPswdChckView);
        if (myPswdChckView == 0) {
            //TODO add rtti of the base type to the err msg
            throw CannotCastImplementation("WtPswdChckView");
        }
        addView(pLocalizedName, pName, *myPswdChckView);
    }

    void WtMainPanelView::addView(const std::string &pLocalizedName,
                                  const PanelName &pName, WtViewIface &pView) {
        WMenuItem *myItem = getLeftMenu()->addItem(pLocalizedName,
                                                   std::unique_ptr<Wt::WWidget>(pView.getWWidget()));
        string myUrl("/" + toString(pName));
        myItem->setLink(Wt::WLink(Wt::LinkType::InternalPath, myUrl.c_str()));
        myItem->triggered().connect(std::bind([=]() { sigShowedPanel(pName); }));
    }

    /**
     * 	Create a m_Navigation bar with a link to a web page.
     *
     */
    WtMainPanelView::WtMainPanelView() {
        m_MainPanel = new WContainerWidget();
        // Create a m_Navigation bar with a link to a web page.
        setNavigation(new WNavigationBar());
        getNavigation()->setTitle(WString(translate("TRIHLAV OTP Server")),
                                  "https://github.com/gogoba/trihlav");
        getNavigation()->setResponsive(true);
        m_MainContent = new WStackedWidget();
        setContentsStack(m_MainContent);
        m_ContentsStack->addStyleClass("contents");
        m_MainPanel->addWidget(std::unique_ptr<WWidget>(m_Navigation));
        m_MainPanel->addWidget(std::unique_ptr<WWidget>(m_ContentsStack));
        // Setup a Left-aligned menu.
        m_LeftMenu = getNavigation()->addMenu(
                unique_ptr<WMenu>(new WMenu(m_ContentsStack)),
                Wt::AlignmentFlag::Left);
        // Setup a Right-aligned menu.
        auto myRightMenu = new Wt::WMenu();
        getNavigation()->addMenu(std::unique_ptr<WMenu>(myRightMenu), Wt::AlignmentFlag::Right);
        // Create a myHelpPopup submenu for the Help menu.
        WPopupMenu *myHelpPopup = new WPopupMenu();
        myHelpPopup->addItem("Contents");
        myHelpPopup->addItem("Index");
        myHelpPopup->addSeparator();
        myHelpPopup->addItem("About");
        myHelpPopup->itemSelected().connect(std::bind([=](Wt::WMenuItem *pItem) {
            showHelpMsgBox(pItem);
        }, std::placeholders::_1));
        auto myHelpMenuItem = new WMenuItem("Help");
        myHelpMenuItem->setMenu(std::unique_ptr<WPopupMenu>(myHelpPopup));
        myRightMenu->addItem(std::unique_ptr<WMenuItem>(myHelpMenuItem));
        // Add a Search control.
        m_SearchEdit = new WLineEdit();
        m_SearchEdit->setToolTip("Enter a search item");
        m_SearchEdit->enterPressed().connect( //
                std::bind([=]() { showNotYetImplemented(); })
        );
        getNavigation()->addSearch(std::unique_ptr<WLineEdit>(m_SearchEdit), Wt::AlignmentFlag::Right);
    }

    void WtMainPanelView::showHelpMsgBox(const WMenuItem *pItem) const {
        const string myHelpText = "Showing Help: {1}\n"
                                          "Build version: " + Version::getVersion();
        Wt::WMessageBox *myMsgBox = new Wt::WMessageBox( //
                "Help",
                WString::fromUTF8(myHelpText).arg(pItem->text()),
                Icon::Information,
                StandardButton::Ok
        );
        myMsgBox->buttonClicked().connect(bind([=]() { delete myMsgBox; }));
        myMsgBox->show();
    }

    static const char *const K_NOT_IMPL = "<p>Not yet implemented, should search for: {1}</p>";

    void WtMainPanelView::showNotYetImplemented() {
        getLeftMenu()->select(1); // is the index of the "Sales"
        Wt::WMessageBox *myMsgBox = new Wt::WMessageBox( //
                "Help",
                WString::fromUTF8(K_NOT_IMPL).arg( //
                        m_SearchEdit->valueText()
                ),
                Icon::Information,
                StandardButton::Ok
        );
        myMsgBox->buttonClicked().connect(bind([=]() { delete myMsgBox; }));
        myMsgBox->show();
    }

    WtMainPanelView::~WtMainPanelView() {
        BOOST_LOG_TRIVIAL(debug) << "~WtMainPanelView()";
    }

    Wt::WWidget *WtMainPanelView::getRootWidget() {
        return m_MainPanel;
    }

} /* namespace trihlav */

