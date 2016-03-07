#include <QApplication>
#include <stdio.h>
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  int result = 0;
  printf("Running main() from testframework/gtest_qtapp_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  int gresult = RUN_ALL_TESTS();
  result = app.exec();
  return result + gresult;
}
