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
  MESSAGE(STATUS "Tests enabled. Attempting to fetch GoogleTest...")
  IF(NOT GOOGLETEST_FETCH_URL)
    SET(GOOGLETEST_FETCH_URL "https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip")
  ENDIF()
  INCLUDE(FetchContent)
  FetchContent_Declare(
    googletest
    URL ${GOOGLETEST_FETCH_URL}
    SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/googletest"
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  # enable ctest targets
  MESSAGE(STATUS "Enabling ctest targets.")
  INCLUDE (CTest)
  ENABLE_TESTING()

  # Add include directory for 'gtest.h' include.
  SET(gtest_include_dir "${googletest-distribution_SOURCE_DIR}/googletest/include/")
  MESSAGE(STATUS "Adding googletest source dir: ${gtest_include_dir}")
  INCLUDE_DIRECTORIES(${gtest_include_dir})

  #
  # Add different front-end executables as test only libraries
  TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_BASE_DEPLIB
    SOURCES gtest_main.cc
    TESTONLY
  )
  TARGET_LINK_LIBRARIES(TESTFRAMEWORK_BASE_DEPLIB PUBLIC gtest)
  #
  # Add different front-end executables that depend on Qt as test only libraries
  IF(TPL_ENABLE_Qt6Core OR TPL_ENABLE_Qt5Core)
    # Determine which Qt targets to use
    IF(TPL_ENABLE_Qt6Core)
      SET(_QT_CORE_TARGET Qt6Core::all_libs)
    ELSE()
      SET(_QT_CORE_TARGET Qt5Core::all_libs)
    ENDIF()
    TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_QCOREAPP_DEPLIB
      SOURCES gtest_qcoreapp_main.cc
      TESTONLY
    )
    TARGET_LINK_LIBRARIES(TESTFRAMEWORK_QCOREAPP_DEPLIB PUBLIC gtest PRIVATE ${_QT_CORE_TARGET})
  ENDIF()

  IF(TPL_ENABLE_Qt6Widgets OR TPL_ENABLE_Qt5Widgets)
    # Determine which Qt targets to use
    IF(TPL_ENABLE_Qt6Widgets)
      SET(_QT_WIDGETS_TARGET Qt6Widgets::all_libs)
    ELSE()
      SET(_QT_WIDGETS_TARGET Qt5Widgets::all_libs)
    ENDIF()
    TRIBITS_ADD_LIBRARY(TESTFRAMEWORK_QAPP_DEPLIB
      SOURCES gtest_qapp_main.cc
      TESTONLY
    )
    TARGET_LINK_LIBRARIES(TESTFRAMEWORK_QAPP_DEPLIB PUBLIC gtest PRIVATE ${_QT_WIDGETS_TARGET})
  ENDIF()
ENDIF()
TRIBITS_PACKAGE_POSTPROCESS()
