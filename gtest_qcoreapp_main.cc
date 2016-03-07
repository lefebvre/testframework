#include <QCoreApplication>
#include <stdio.h>
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);
  int result = 0;
  printf("Running main() from testframework/gtest_qtcoreapp_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  int gresult = RUN_ALL_TESTS();
  result = app.exec();
  return result + gresult;
}
