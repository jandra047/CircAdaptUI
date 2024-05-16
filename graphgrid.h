#ifndef GRAPHGRID_H
#define GRAPHGRID_H

#include <QWidget>
#include <QGridLayout>
#include "buffer.h"

class TestGrid : public QWidget
{
    Q_OBJECT
    enum ColType {
        REFERENCE,
        SNAPSHOT,
        CURRENT
    };
    const QVector<QString> types = {"REFERENCE", "SNAPSHOT", "CURRENT"};

public:
    TestGrid(int, int, QWidget*);
public slots:
    void updateGraphs(Buffer&);

private:
    QGridLayout gridLayout;

    int rows;
    int cols;
};
#endif // GRAPHGRID_H
