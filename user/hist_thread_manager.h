#pragma once

#include "word_rank_model.h"

#include <QObject>

/**
 * @brief The HistThreadManager class performs background execution of counting of words
 */
class HistThreadManager : public QThread
{
    Q_OBJECT
public:
    HistThreadManager();
    ~HistThreadManager();
    HistThreadManager(const HistThreadManager&) = delete;
    HistThreadManager(HistThreadManager&&) = delete;

    Q_PROPERTY(double percent READ getPercent WRITE setPercent NOTIFY percentChanged)
    double getPercent() { return percent; }
    void setPercent(double percent) {
        if(this->percent == percent)
            return;
        this->percent = percent;
        emit percentChanged();
    }

    Q_PROPERTY(WordRankModel* model WRITE setModel)
    void setModel(WordRankModel *model) {
        this->model = model;
    }

    Q_INVOKABLE bool setFileUrl(QString fileUrl);
    Q_INVOKABLE void start();
    Q_INVOKABLE void cancel();

    bool event(QEvent *event) override;

signals:
    void percentChanged();

private:
    void run() override;

private:
    WordRankModel* model{nullptr};
    QUrl fileUrl{};
    double percent{};
};


