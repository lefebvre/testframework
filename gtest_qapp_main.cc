#include <QApplication>
#include <QThread>
#include <stdio.h>
#include "gtest/gtest.h"

class Thread : public QThread
{
private:

    int mArgc;
    char ** mArgv;
public:
    Thread(int& argc, char ** argv)
    {
        mArgc = argc;
        mArgv = argv;
        result = 0;
    }
    int result;

    void run() {
        printf("Running main() from testframework/gtest_qtapp_main.cc\n");
        testing::InitGoogleTest(&mArgc, mArgv);
        result = RUN_ALL_TESTS();
    }
}; // class Thread
int main(int argc, char **argv) {
  QApplication app(argc, argv);
  int result = 0;
  Thread thread(argc, argv);
  thread.start();
  app.connect(&thread
          , SIGNAL(finished())
          , SLOT(quit()));
  result = app.exec();
  return result + thread.result;
}
