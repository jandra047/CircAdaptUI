#include <QtTest/QTest>
#include <QObject>
#include "modelwrapper.h"
#include "buffer.h"

class TestWrapper : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLabel();
    void testW();
};

void TestWrapper::initTestCase() {
    // Initialization before tests are run
}

void TestWrapper::cleanupTestCase() {
    // Cleanup after tests are done
}

void TestWrapper::testLabel() {
}

void TestWrapper::testW() {
    Buffer buffer;
    ModelWrapper mw(buffer);
    QVERIFY(QThread::currentThread() != mw.get_thread());
}

QTEST_MAIN(TestWrapper)
#include "test_Wrapper.moc"
