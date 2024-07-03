#include "valueview.h"
#include <QHeaderView>

ValueView::ValueView(QWidget* parent) :
    QWidget( parent ),
    m_valuesList ( new QTableWidget(this) )
{
    setLayout(new QGridLayout());
    layout()->addWidget(m_valuesList);
    m_valuesList->setColumnCount(3);
    m_valuesList->setRowCount(3);
    m_valuesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList headers { tr("Name"), tr("Value"), tr("Unit")};
    m_valuesList->setHorizontalHeaderLabels(headers);
    m_valuesList->horizontalHeader()->setVisible(true);
    m_valuesList->horizontalHeader()->setCascadingSectionResizes(true);
    m_valuesList->horizontalHeader()->setStretchLastSection(true);
}
