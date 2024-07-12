#include "valueview.h"
#include <QHeaderView>
#include "CircAdaptUI/settings.h"

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
    m_tableItems.reserve(itemArray.count());
    for (auto item : itemArray)
    {
        QJsonObject itemObj = item.toObject();
        m_tableItems.push_back( new QTableWidgetItem( ".." ) );
        m_valuesList->insertRow( m_valuesList->rowCount() );
        tableItemPtr = new QTableWidgetItem(itemObj["name"].toString());
        tableItemPtr->setToolTip(itemObj["tooltip"].toString());
        m_valuesList->setItem( m_valuesList->rowCount() - 1, 0, tableItemPtr);
        m_valuesList->setItem( m_valuesList->rowCount() - 1, 1, m_tableItems.last());
        m_valuesList->setItem( m_valuesList->rowCount() - 1, 2, new QTableWidgetItem(itemObj["unit"].toString()));
    }
}

void ValueView::updateValues(const QMap<QString, double>& lastBeatData)
{
    for (int rowIdx = 0; rowIdx < m_valuesList->rowCount(); rowIdx++)
    {
        QTableWidgetItem* item = m_valuesList->item(rowIdx, 0);
        m_valuesList->item(rowIdx, 1)->setText(QString::number(lastBeatData[item->text()], 'f', 2));
    }
}
