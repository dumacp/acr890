SOURCES   = mainwindow.cpp \
            main.cpp \
            screens/loginscreen.cpp \
            screens/homescreen.cpp \
            screens/productscreen.cpp \
            screens/recargabilletera.cpp \
            screens/recargamifare.cpp \
            screens/historyscreen.cpp \
            screens/configscreen.cpp \
            screens/dialog/dialog.cpp \
            screens/sale/animation/saleprogress.cpp \
            screens/sale/animation/mifaresaleprogress.cpp \
            screens/sale/error/saleerror.cpp \
            screens/sale/error/mifaresaleerror.cpp \
            screens/sale/success/salesuccess.cpp \
            screens/sale/success/mifaresalesuccess.cpp \
            smartCard/AcsException.cpp \
            smartCard/AcsHelper.cpp \
            smartCard/AcsKeypad.cpp \
            smartCard/AcsReader.cpp \    
            smartCard/MifareClassic.cpp \    
            
            

HEADERS   = mainwindow.h \
            screens/loginscreen.h \
            screens/sessionmanager.h \
            screens/homescreen.h \
            screens/productscreen.h \
            screens/recargabilletera.h \
            screens/recargamifare.h \
            screens/historyscreen.h \
            screens/configscreen.h \
            screens/dialog/dialog.h \
            screens/sale/animation/saleprogress.h \
            screens/sale/animation/mifaresaleprogress.h \
            screens/sale/error/saleerror.h \
            screens/sale/error/mifaresaleerror.h \
            screens/sale/success/salesuccess.h \
            screens/sale/success/mifaresalesuccess.h \
            smartCard/AcsException.h \
            smartCard/AcsHelper.h \
            smartCard/AcsKeypad.h \
            smartCard/AcsIncludes.h \
            smartCard/AcsReader.h \
            smartCard/MifareClassic.h \
            /home/nesas-14/acr890_APIs_test/include/acs_api.h \
            /home/nesas-14/acr890_APIs_test/include/acs_errno.h


# install
target.path = $$[QT_INSTALL_EXAMPLES]/tutorials/addressbook/part1
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS part1.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/tutorials/addressbook/part1
INSTALLS += target sources

QT +=  widgets network debug json
RESOURCES += resources.qrc 


symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
simulator: warning(This example might not fully work on Simulator platform)
