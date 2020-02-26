##---------------------------------------------------------------------------##
## testframework/CMakeLists.txt
## Jordan Lefebvre
## Monday March 7 10:19:18 2016
##---------------------------------------------------------------------------##


#
# Project designed around header only test classes
#
TRIBITS_PACKAGE(testframework)

# only if testing is enabled do we want to compile harnesses
IF(${PROJECT_NAME}_ENABLE_TESTS)
  #
  # Add different front-end executables as test only libraries
  TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_BASE_DEPLIB
    SOURCES gtest_main.cc
    TESTONLY
  )
  #
  # Add different front-end executables that depend on Qt as test only libraries
  IF(TPL_ENABLE_Qt5Core OR TPL_ENABLE_QT)
    TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_QAPP_DEPLIB
      SOURCES gtest_qapp_main.cc
      TESTONLY
    )
    TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_QCOREAPP_DEPLIB
      SOURCES gtest_qcoreapp_main.cc
      TESTONLY
    )
  ENDIF()
ENDIF()

TRIBITS_PACKAGE_POSTPROCESS()
