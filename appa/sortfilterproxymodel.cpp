#include "sortfilterproxymodel.h"
#include <QDebug>
SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
{
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    qDebug() << sourceModel()->data(index0).toString();

    return sourceModel()->data(index0).toString().contains(filterRegularExpression());
}
