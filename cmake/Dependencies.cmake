IF(TPL_ENABLE_Qt6Core OR TPL_ENABLE_Qt5Core)
  IF(USE_QT6)
    SET(QT_DEP Qt6Widgets Qt6Core)
  ELSEIF(USE_QT5)
    SET(QT_DEP Qt5Widgets Qt5Core)
  ENDIF()

  # allow for tests to be disabled and no testing harness to be compiled.
  TRIBITS_PACKAGE_DEFINE_DEPENDENCIES(
    LIB_REQUIRED_TPLS ${QT_DEP}
  )
ELSE()
  TRIBITS_PACKAGE_DEFINE_DEPENDENCIES()
ENDIF()

