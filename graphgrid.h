#ifndef GRAPHGRID_H
#define GRAPHGRID_H

#include <QWidget>
#include <QGridLayout>
#include "buffer.h"

class GraphGrid : public QWidget
{
    Q_OBJECT
    enum ColType {
        REFERENCE,
        SNAPSHOT,
        CURRENT
    };
    const QVector<QString> types = {"REFERENCE", "SNAPSHOT", "CURRENT"};

public:
    GraphGrid(int, int, QWidget*);
    void setRowVisible(int, bool);
public slots:
    void updateGraphs(Buffer&);

private:
    QGridLayout gridLayout;

    int rows;
    int cols;
};
#endif // GRAPHGRID_H
