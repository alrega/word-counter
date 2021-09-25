#include "word_rank_model.h"

#include <algorithm>

WordRankModel::WordRankModel(QObject *parent) : QAbstractListModel(parent)
{
}

void WordRankModel::updateList(const QMap<QString, size_t> &data)
{
    beginResetModel();
    m_data = data;
    size_t total = 0;
    for(auto it = data.constBegin(); it!=data.constEnd(); it++)
        total += it.value();
    m_totalCount = total;
    endResetModel();
}


QHash<int, QByteArray> WordRankModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Qt::UserRole + 1] = "count";
    roles[Qt::UserRole + 2] = "total";

    return roles;
}

int WordRankModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}


QVariant WordRankModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    QVariant result{};
    if(0 <= row && row < m_data.count())
    {
        auto it = m_data.begin();
        for(int i = 0; i < row; i++)
            ++it;
        switch (role) {
        case Qt::DisplayRole:
            result.setValue(it.key());
            break;
        case Qt::UserRole + 1:
            result.setValue(it.value());
            break;
        case Qt::UserRole + 2:
            result.setValue(m_totalCount);
            break;
        }
    }
    return result;
}
