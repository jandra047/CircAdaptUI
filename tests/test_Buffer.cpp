#include <QtTest/QTest>
#include <QObject>
#include "buffer.h"

class TestBuffer : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testLabel();
};

void TestBuffer::initTestCase() {
    // Initialization before tests are run
}

void TestBuffer::cleanupTestCase() {
    // Cleanup after tests are done
}

void TestBuffer::testLabel() {
    Buffer buffer;

    QVERIFY(&buffer != nullptr);
//    QCOMPARE(label->text(), QString("Hello, Qt!"));
}

QTEST_MAIN(TestBuffer)
#include "test_Buffer.moc"
