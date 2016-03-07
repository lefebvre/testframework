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
    }
    void TearDown()
    {
    }

protected:
}; // class QCoreAppFixture
}  // namespace testframework
