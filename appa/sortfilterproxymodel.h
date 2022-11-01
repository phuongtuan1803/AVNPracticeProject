#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H
#include <QSortFilterProxyModel>

class SortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortFilterProxyModel(QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:

};
#endif // SORTFILTERPROXYMODEL_H
