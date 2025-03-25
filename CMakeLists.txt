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
  # Integrate with the vanilla google test cmake
  IF(NOT googletest-distribution_BINARY_DIR)
      MESSAGE(STATUS "Tests enabled. Attempting to fetch GoogleTest...")
      INCLUDE(FetchContent)
      FetchContent_Declare(
        googletest
        URL file://${CMAKE_CURRENT_LIST_DIR}/external/googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
      )
      # For Windows: Prevent overriding the parent project's compiler/linker settings
      SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
      FetchContent_MakeAvailable(googletest)
      # enable ctest targets
      MESSAGE(STATUS "Enabling ctest targets.")
      INCLUDE (CTest)
      ENABLE_TESTING()
  ENDIF()

  # Add include directory for 'gtest/gtest/h' include.
  SET(gtest_include_dir "${googletest-distribution_SOURCE_DIR}/googletest/include/")
  MESSAGE(STATUS "Adding googletest source dir: ${gtest_include_dir}")
  INCLUDE_DIRECTORIES(${gtest_include_dir})

  #
  # Add different front-end executables as test only libraries
  TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_BASE_DEPLIB
    SOURCES gtest_main.cc
    TESTONLY
  )
  TARGET_LINK_LIBRARIES(TESTFRAMEWORK_BASE_DEPLIB gtest)
  #
  # Add different front-end executables that depend on Qt as test only libraries
  IF(TPL_ENABLE_Qt6Core OR TPL_ENABLE_Qt5Core)
    TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_QAPP_DEPLIB
      SOURCES gtest_qapp_main.cc
      TESTONLY
    )
    TARGET_LINK_LIBRARIES(TESTFRAMEWORK_QAPP_DEPLIB gtest)
    TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_QCOREAPP_DEPLIB
      SOURCES gtest_qcoreapp_main.cc
      TESTONLY
    )
    TARGET_LINK_LIBRARIES(TESTFRAMEWORK_QCOREAPP_DEPLIB gtest)
  ENDIF()
ENDIF()
TRIBITS_PACKAGE_POSTPROCESS()
