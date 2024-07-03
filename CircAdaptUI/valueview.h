#ifndef VALUEVIEW_H
#define VALUEVIEW_H

#include <QWidget>
#include <QLabel>
#include <QSettings>
#include <QTableWidgetItem>
#include <QGridLayout>


class ValueView : public QWidget
{
    Q_OBJECT

public:

    explicit ValueView( QWidget * parent = nullptr );

    ~ValueView() {};

private:
    void setupTableItems();

    QTableWidget* m_valuesList;

    QVector<QTableWidgetItem*> m_TableItems;
};

#endif // VALUEVIEW_H
