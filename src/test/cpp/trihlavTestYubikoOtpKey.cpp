#include <string>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "trihlavLib/trihlavButtonIface.hpp"
#include "trihlavLib/trihlavEditIface.hpp"
#include "trihlavLib/trihlavFactoryIface.hpp"
#include "trihlavLib/trihlavSpinBoxIface.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyViewIface.hpp"
#include "trihlavLib/trihlavOsIface.hpp"
#include "trihlavLib/trihlavLoginViewIface.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"  // Brings in Google Mock.

#include "trihlavLib/trihlavLog.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyPresenter.hpp"
#include "trihlavLib/trihlavYubikoOtpKeyConfig.hpp"
#include "trihlavLib/trihlavKeyManager.hpp"
#include "trihlavLib/trihlavSettings.hpp"
#include "trihlavLib/trihlavMainPanelViewIface.hpp"
#include "trihlavLib/trihlavKeyListPresenterIface.hpp"
#include "trihlavLib/trihlavPswdChckViewIface.hpp"

#include "trihlavMockEditIface.hpp"
#include "trihlavMockStrEdit.hpp"
#include "trihlavMockYubikoOtpKeyView.hpp"
#include "trihlavMockFactory.hpp"
#include "trihlavMockKeyListView.hpp"
#include "trihlavTestCommonUtils.hpp"

using namespace std;
using namespace trihlav;
using namespace boost;
using namespace boost::filesystem;
using ::testing::NiceMock;

string thePrivateIdStr("666");
string thePublicIdStr("666");
string theSecretKeyStr("666");
int thePublicIdLen = 666;

int main(int argc, char **argv) {
	initLog();
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}

struct TestYubikoOtpKey: testing::Test {

};

TEST_F(TestYubikoOtpKey,factoryPointers) {
	BOOST_LOG_NAMED_SCOPE("TestYubikoOtpKey_factoryPointers_Test::TestBody");
	NiceMock<MockFactory> myMockFactory;
	auto myView = myMockFactory.createKeyListView();
    BOOST_LOG_TRIVIAL(debug) << "YubikoOtpKeyViewPtr:" << myView;
    delete myView;
}

TEST_F(TestYubikoOtpKey,keyManagerInit) {
	BOOST_LOG_NAMED_SCOPE("testKeyManagerInitialisation");
	Settings mySettings(unique_path("/tmp/trihlav-tst-%%%%-%%%%-%%%%-%%%%"));
	KeyManager myKMan(mySettings);
	BOOST_LOG_TRIVIAL(debug)<< "Test lazy init. only first getter will cause"
	" initialization";
	EXPECT_TRUE(!mySettings.isInitialized());
	const path& myKManPath = mySettings.getConfigDir();
	BOOST_LOG_TRIVIAL(debug)<< "Got config. directory \"" << myKManPath << "\","
	" now we should be initialized";

	EXPECT_TRUE(mySettings.isInitialized());
	BOOST_LOG_TRIVIAL(debug)<< "Does the configuration path exists?";
	EXPECT_TRUE(exists(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "Yes, it does.";

	NiceMock<MockFactory> myMockFactory;
	YubikoOtpKeyPresenter myPresenter(myMockFactory);
	MockYubikoOtpKeyView& myYubikoOtpKeyView(
			dynamic_cast<MockYubikoOtpKeyView&>(myPresenter.getView()));
	BOOST_LOG_TRIVIAL(debug)<< "YubikoOtpKeyView  " << &myYubikoOtpKeyView;
	BOOST_LOG_TRIVIAL(debug)<< "PrivateID          '" //
	<< myYubikoOtpKeyView.m_MockEdtPrivateId.getValue() << "'.";
	EXPECT_EQ(myPresenter.getView().getSbxPublicIdLen().getValue(), 6);
	EXPECT_EQ(myPresenter.getView().getSbxPublicIdLen().getMin(), 0);
	EXPECT_EQ(myPresenter.getView().getSbxPublicIdLen().getMax(), 6);
	EXPECT_EQ(myPresenter.getView().getSbxPublicIdLen().getStep(), 1);
	EXPECT_TRUE(myPresenter.getView().getEdtPrivateId().getValue().empty());
	EXPECT_TRUE(myPresenter.getView().getEdtPublicId().getValue().empty());
	EXPECT_TRUE(remove_all(myKManPath));
	BOOST_LOG_TRIVIAL(debug)<< "testKeyManager OK";
    delete &myYubikoOtpKeyView;
}

TEST_F(TestYubikoOtpKey,addKeyPressGenerateBtnsDeleteKey) {
	BOOST_LOG_NAMED_SCOPE("testGenerateButtons");
	NiceMock<MockFactory> myMockFactory;
	YubikoOtpKeyPresenter myPresenter(myMockFactory);
	YubikoOtpKeyViewIface& myViewIface(myPresenter.getView());
	MockYubikoOtpKeyView& myYubikoOtpKeyView(
			dynamic_cast<MockYubikoOtpKeyView&>(myPresenter.getView()));
	BOOST_LOG_TRIVIAL(debug)<< "Expectations...";
	EXPECT_CALL(myYubikoOtpKeyView, show());
    BOOST_LOG_TRIVIAL(debug) << "Expectations set.";
	myPresenter.addKey();
	myViewIface.getBtnGenPrivateId().pressedSig();
	myViewIface.getBtnGenPublicId().pressedSig();
	myViewIface.getBtnGenSecretKey().pressedSig();
	myViewIface.sigDialogFinished(true);
	const string myPrivId(myViewIface.getEdtPrivateId().getValue());
	const string myPublicId(myViewIface.getEdtPublicId().getValue());
	const string mySecretKey(myViewIface.getEdtSecretKey().getValue());
	const int myPubIdLen(myViewIface.getSbxPublicIdLen().getValue());
	const auto& myCfg = myPresenter.getCurCfg();
	const path myFilename(myCfg.getFilename());
	BOOST_LOG_TRIVIAL(debug)<< "0 myPrivId   : "<< myPrivId << ".";
	BOOST_LOG_TRIVIAL(debug)<< "0 myPublicId : "<< myPublicId << ".";
	BOOST_LOG_TRIVIAL(debug)<< "0 mySecretKey: "<< mySecretKey<< ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 myPrivId   : "<< myCfg.getPrivateId() << ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 myPublicId : "<< myCfg.getPublicId() << ".";
	BOOST_LOG_TRIVIAL(debug)<< "1 mySecretKey: "<< myCfg.getSecretKey() << ".";
	EXPECT_TRUE(!myCfg.getPrivateId().empty());
	EXPECT_TRUE(!myCfg.getPublicId().empty());
	EXPECT_TRUE(!myCfg.getSecretKey().empty());
	EXPECT_TRUE(myPublicId.compare(myCfg.getPublicId()) == 0);
	EXPECT_TRUE(myPrivId.compare(myCfg.getPrivateId()) == 0);
	EXPECT_TRUE(mySecretKey.compare(myCfg.getSecretKey()) == 0);
	myPresenter.deleteKey();
	EXPECT_FALSE(exists(myFilename));
    delete &myYubikoOtpKeyView;
}

TEST_F(TestYubikoOtpKey,throwsExceptionOnWrongSysUser) {
	BOOST_LOG_NAMED_SCOPE("throwsExceptionOnWrongSysUser");
	Settings mySettings(unique_path("/tmp/trihlav-tst-%%%%-%%%%-%%%%-%%%%"));
	KeyManager myKMan(mySettings);
	YubikoOtpKeyConfig myCfg(myKMan);
	try {
		myCfg.setSysUser("");
		FAIL()<<"Failed to throw on empty system user parameter!";
	} catch (invalid_argument& ex) {
		BOOST_LOG_TRIVIAL(debug)<<ex.what();
	}
	string myLongPar(2048, 'X');
	try {
		myCfg.setSysUser(myLongPar);
		FAIL()<<"Failed to throw on long system user parameter!";
	} catch (invalid_argument& ex) {
		BOOST_LOG_TRIVIAL(debug)<<ex.what();
	}
}

TEST_F(TestYubikoOtpKey, checkPassword) {
    BOOST_LOG_NAMED_SCOPE("trihlavYubikoOtpKey::checkPassword");
    path myTestCfgFile(unique_path("/tmp/trihlav-tests-%%%%-%%%%"));
    EXPECT_FALSE(exists(myTestCfgFile));
    EXPECT_TRUE(create_directory(myTestCfgFile));
    BOOST_LOG_TRIVIAL(debug) << "Test data location: " << myTestCfgFile << ".";
    NiceMock<MockFactory> myMockFactory;
    myMockFactory.getSettings().setConfigDir(myTestCfgFile);
    KeyManager &myKeyMan(myMockFactory.getKeyManager());
    YubikoOtpKeyConfig myCfg0{createYubikoOtpKeyConfig(myKeyMan)};
    string myOtp0{myCfg0.generateOtp()};
    BOOST_LOG_TRIVIAL(debug) << "Got following OTP:" << myOtp0 << ".";
    EXPECT_TRUE(myCfg0.checkOtp(myOtp0));

    myOtp0 = myCfg0.generateOtp();
    BOOST_LOG_TRIVIAL(debug) << "Got following OTP:" << myOtp0 << ".";
    EXPECT_TRUE(myCfg0.checkOtp(myOtp0));

    myOtp0 = myCfg0.generateOtp();
    BOOST_LOG_TRIVIAL(debug) << "Got following OTP:" << myOtp0 << ".";
    EXPECT_TRUE(myCfg0.checkOtp(myOtp0));

    remove_all(myTestCfgFile);
    EXPECT_FALSE(exists(myTestCfgFile));
    //EXPECT_TRUE(false);
}

const int K_TST_STR_L = 8;

TEST_F(TestYubikoOtpKey, generateHex) {
	BOOST_LOG_NAMED_SCOPE("generateHex");
	string myTestVal("XXXXXXXXXXXXXXX");
	YubikoOtpKeyPresenter::generate(0, myTestVal);
	EXPECT_EQ(myTestVal.size(), 0);
	YubikoOtpKeyPresenter::generate(K_TST_STR_L, myTestVal);
	BOOST_LOG_TRIVIAL(debug)<< "Generated:"<<myTestVal<<".";
	EXPECT_EQ(myTestVal.size(), K_TST_STR_L * 2);
}

