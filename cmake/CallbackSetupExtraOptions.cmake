##---------------------------------------------------------------------------##
## testframework/cmake/CallbackSetupExtraOptions.cmake
##---------------------------------------------------------------------------##
MACRO(TRIBITS_REPOSITORY_SETUP_EXTRA_OPTIONS)
  IF(EXISTS "${testframework_SOURCE_DIR}/setup")
    ADD_SUBDIRECTORY(${testframework_SOURCE_DIR}/setup)
  ENDIF()
ENDMACRO()
##---------------------------------------------------------------------------##
##       end of testframework/cmake/CallbackSetupExtraOptions.cmake
##---------------------------------------------------------------------------##
