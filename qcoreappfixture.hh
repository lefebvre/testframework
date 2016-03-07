#include <QCoreApplication>
#include "gtest/gtest.h"

namespace testframework
{
class QCoreAppFixture : public ::testing::Test
{
public:
  QCoreAppFixture(){}
  ~QCoreAppFixture()
  {
     qApp->quit();
  }
protected:
}; // class QCoreAppFixture
}  // namespace testframework
