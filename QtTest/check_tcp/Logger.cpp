#include "Logger.h"

Logger::Logger(QObject *parent, QString fileName, QPlainTextEdit *editor) : QObject(parent)
{
    m_editor = editor;
    m_showDate = true;
    QString fileDate = fileName.replace(".txt", QString("%1.txt").arg(QDateTime::currentDateTime().toString("_yyMM")));

    if (!fileName.isEmpty()) {
        file = new QFile;
        file->setFileName(fileDate);
        file->open(QIODevice::Append | QIODevice::Text);
    }
}

void Logger::local_write(const QString &value)
{
    QString text = value;
    if (m_showDate)
        text = QDateTime::currentDateTime().toString("\nyyyy-MM-dd hh:mm:ss ") + text;
    QTextStream out(file);
    out.setCodec("UTF-8");
    if (file != nullptr) {
        out << text;
    }
    if (m_editor != nullptr)
        m_editor->appendPlainText(text);
}

void Logger::remote_write(const QString &value, QDateTime time)
{
    QString text = value;
    if (m_showDate)
        text = time.toString("\nyyyy-MM-dd hh:mm:ss ") + text;
    QTextStream out(file);
    out.setCodec("UTF-8");
    if (file != nullptr) {
        out << text;
    }
    if (m_editor != nullptr)
        m_editor->appendPlainText(text);
}

void Logger::setShowDateTime(bool value) {
    m_showDate = value;
}

Logger::~Logger() {
    if (file != nullptr)
        file->close();
}
