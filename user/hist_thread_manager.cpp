#include "hist_thread_manager.h"
#include "dictionary.h"

//#include <filesystem>

class HistUpdateEvent : public QEvent
{
public:
    HistUpdateEvent(QMap<QString, size_t> data, double percent) : QEvent(QEvent::User), data(std::move(data)), percent(percent) {}
    QMap<QString, size_t> data;
    double percent;
};

HistThreadManager::HistThreadManager()
{
    qDebug() << __func__;
}

HistThreadManager::~HistThreadManager()
{
    qDebug() << __func__;
    if(QThread::isRunning())
    {
        qWarning() << "Worker thread id:" << QThread::currentThreadId() << " is running.";
        QThread::requestInterruption();
        QThread::sleep(1);
        if(QThread::isRunning())
        {
            qCritical() << "Worker thread id:" << QThread::currentThreadId() << " is still running.";
            QThread::terminate();
        }
    }
}

bool HistThreadManager::setFileUrl(QString fileUrl)
{
    QUrl url{fileUrl};
    if(!url.isLocalFile())
    {
        return false;
    }
    this->fileUrl=url;
    return true;
}

void HistThreadManager::start()
{
    qDebug() << __func__;
    QThread::start();
}

void HistThreadManager::cancel()
{
    qDebug() << __func__;
    QThread::requestInterruption();
    QThread::wait(1000);
    if(QThread::isRunning())
    {
        qCritical() << "Failed to stop worker thread " << QThread::currentThreadId();
    }
}

void HistThreadManager::run()
{
    // Note, this method is running in non-UI thread
    std::string filePath = QDir::toNativeSeparators(fileUrl.toLocalFile()).toStdString();
    qDebug() << __func__ << filePath.c_str();

    //const auto fileSize = std::filesystem::file_size({filePath});
    size_t fileSize = 0;
    {
        std::ifstream inp(filePath);
        inp.seekg(0, std::ios::end);
        fileSize = inp.tellg();
        inp.close();
;    }


    std::ifstream inp(filePath);

    // To pass the data fron non-UI thread to UI thread, we must use QCoreApplication::postEvent()
    auto postHistUpdateEvent  = [this](const std::list<std::pair<std::string, size_t>> &top, double percent) {
        QMap<QString, size_t> data;
        for(const auto &ref : top)
        {
            data.insert(ref.first.c_str(), ref.second);
        }
        auto event = new HistUpdateEvent{std::move(data), percent};
        QCoreApplication::postEvent(this, event);
    };

    auto callback = [this, &postHistUpdateEvent, &inp, &fileSize](const std::list<std::pair<std::string, size_t>> &top) -> bool {
            if(QThread::isInterruptionRequested())
            {
                qDebug() << "Worker thread has just interrupted";
                return false;
            }

            double percent = 1.0 * inp.tellg() / fileSize;
            postHistUpdateEvent(top, percent);
            // Let's make examining input file slower to observe the progress in QML window
            QThread::currentThread()->msleep(100);
            return true;
        };

    if(inp.good())
    {
        auto top = CountWords<15>(inp, callback);
        postHistUpdateEvent(top, 1.0);
    }
}


bool HistThreadManager::event(QEvent *event)
{
    Q_ASSERT(event);
    if(event->type() == QEvent::User)
    {
        Q_ASSERT(model);
        auto* histUpdateEvent = dynamic_cast<HistUpdateEvent*>(event);
        Q_ASSERT(histUpdateEvent);
        model->updateList(histUpdateEvent->data);
        setPercent(histUpdateEvent->percent);
        return true;
    }
    return false;
}
