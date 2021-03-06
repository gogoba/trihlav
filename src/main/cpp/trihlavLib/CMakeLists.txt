# Basic functionality

GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/trihlavVersion.cpp")

INCLUDE_DIRECTORIES(.. ${PAM_INCLUDE_DIR})

ADD_LIBRARY(trihlavApi SHARED trihlavWrongConfigValue.cpp
        trihlavYubikoOtpKeyConfig.cpp trihlavYubikoOtpKeyConfig.cpp
        trihlavWrongConfigValue.hpp trihlavWrongConfigValue.cpp
        trihlavKeyManager.cpp trihlavKeyManager.hpp
        trihlavVersion.cpp
        trihlavYubikoOtpKeyPresenter.cpp trihlavYubikoOtpKeyPresenter.hpp
        trihlavFailedCreateConfigDir.cpp trihlavFailedCreateConfigDir.hpp
        trihlavCannotWriteConfigDir.cpp trihlavCannotWriteConfigDir.hpp
        trihlavLog.cpp trihlavLog.hpp
        trihlavPresenterBase.cpp trihlavPresenterBase.hpp
        trihlavMainPanelPresenter.cpp trihlavMainPanelPresenter.hpp
        trihlavMainPanelViewIface.hpp
        trihlavCannotWriteConfigDir.cpp trihlavCannotWriteConfigDir.hpp
        trihlavFactoryIface.cpp trihlavFactoryIface.hpp
        trihlavPswdChckPresenter.cpp trihlavPswdChckPresenter.hpp
        trihlavPswdChckPresenterIface.hpp
        trihlavPswdChckViewIface.cpp trihlavPswdChckViewIface.hpp
        trihlavKeyListPresenterIface.hpp trihlavKeyListPresenter.cpp trihlavKeyListPresenter.hpp
        trihlavKeyListViewIface.cpp trihlavKeyListViewIface.hpp
        trihlavYubikoOtpKeyViewIface.cpp trihlavYubikoOtpKeyViewIface.hpp
        trihlavCannotCastImplementation.cpp trihlavCannotCastImplementation.hpp
        trihlavMessageViewIface.cpp trihlavMessageViewIface.hpp
        trihlavEmptyPublicId.cpp trihlavEmptyPublicId.hpp
        trihlavWidgetIface.cpp trihlavWidgetIface.hpp
        trihlavOsIface.cpp trihlavOsIface.hpp
        trihlavSpinBoxIface.cpp trihlavSpinBoxIface.hpp
        trihlavSysUserListPresenter.cpp trihlavSysUserListPresenter.hpp
        trihlavSysUserListViewIface.cpp trihlavSysUserListViewIface.hpp
        trihlavTupleList.hpp trihlavUTimestamp.hpp
        trihlavDialogViewIface.cpp trihlavDialogViewIface.hpp
        trihlavLogApi.hpp trihlavSettings.cpp trihlavSettings.hpp
        trihlavLoginPresenter.cpp trihlavLoginPresenter.hpp trihlavLabelIface.cpp
        trihlavLabelIface.hpp trihlavLoginViewIface.hpp trihlavLoginViewIface.cpp
        trihlavCanOsAuthPresenter.cpp trihlavCanOsAuthPresenter.hpp
        trihlavCreateX509.cpp trihlavGlobals.hpp trihlavButtonIface.hpp
        trihlavConstants.hpp trihlavAddYubikoKeyPresenterIface.cpp
        trihlavAddYubikoKeyPresenterIface.cpp trihlavEditIface.hpp
        trihlavGetUiFactory.hpp trihlavGlobals.hpp trihlavRec2StrVisitor.hpp
        trihlavViewIface.hpp)

INSTALL(TARGETS trihlavApi LIBRARY DESTINATION lib)
