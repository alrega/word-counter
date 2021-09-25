#pragma once

#include <QtCore>

/**
 * @brief The WordRankModel class defines the model of top frequently used words
 */
class WordRankModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WordRankModel(QObject *parent = nullptr);
    ~WordRankModel() = default;
    void updateList(const QMap<QString, size_t> &data);

public: // QAbstractListModel implementation
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QMap<QString, size_t> m_data{};
    size_t m_totalCount{};
};

