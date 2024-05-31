#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

class ProxyModel : public QSortFilterProxyModel
{
public:
    ProxyModel(QObject* parent = nullptr) : QSortFilterProxyModel(parent) {}

protected:
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override
    {
        QVariant leftData = sourceModel()->data(left);
        QVariant rightData = sourceModel()->data(right);

        if (leftData.typeId() == QMetaType::QString && rightData.typeId() == QMetaType::QString)
        {
            QString leftString = leftData.toString().remove(',');
            QString rightString = rightData.toString().remove(',');

            bool conversionSuccess;
            int leftInt = leftString.toInt(&conversionSuccess);
            if (!conversionSuccess)
                return leftString < rightString;

            int rightInt = rightString.toInt(&conversionSuccess);
            if (!conversionSuccess)
                return leftString < rightString;

            return leftInt < rightInt;
        }

        return QSortFilterProxyModel::lessThan(left, right);
    }
};

#endif // PROXYMODEL_H
