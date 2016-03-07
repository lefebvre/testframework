#include <QApplication>
#include "gtest/gtest.h"
namespace testframework
{
class QAppFixture : public ::testing::Test
{
public:
  QAppFixture(){}
  ~QAppFixture()
  {
     qApp->quit();
  }
protected:
}; // class QAppFixture
}  // namespace testframework


