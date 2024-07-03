#include "valueview.h"
#include <QHeaderView>
#include "settings.h"

ValueView::ValueView(QWidget* parent) :
    QWidget( parent ),
    m_valuesList ( new QTableWidget(this) )
{
    setLayout(new QGridLayout());
    layout()->addWidget(m_valuesList);
    m_valuesList->setColumnCount(3);
    // m_valuesList->setRowCount(3);
    m_valuesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList headers { tr("Name"), tr("Value"), tr("Unit")};
    m_valuesList->setHorizontalHeaderLabels(headers);
    m_valuesList->horizontalHeader()->setVisible(true);
    m_valuesList->horizontalHeader()->setCascadingSectionResizes(true);
    m_valuesList->horizontalHeader()->setStretchLastSection(true);

    setupTableItems();
}

void ValueView::setupTableItems()
{
    QTableWidgetItem *  tableItemPtr = nullptr;
    const QJsonArray itemArray = Settings::instance().ValueView();
    for (auto item : itemArray)
    {
        QJsonObject itemObj = item.toObject();
        m_valuesList->insertRow( m_valuesList->rowCount() );
        tableItemPtr = new QTableWidgetItem(itemObj["name"].toString());
        tableItemPtr->setToolTip(itemObj["tooltip"].toString());
        m_valuesList->setItem( m_valuesList->rowCount() - 1, 0, tableItemPtr);
        m_valuesList->setItem( m_valuesList->rowCount() - 1, 2, new QTableWidgetItem(itemObj["unit"].toString()));
    }
}
