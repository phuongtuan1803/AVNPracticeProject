#include "sortfilterproxymodel.h"
#include <QDebug>
SortFilterProxyModel::SortFilterProxyModel(QObject *parent)
{
}

bool SortFilterProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    return sourceModel()->data(index0).toString().contains(filterRegularExpression());
}
