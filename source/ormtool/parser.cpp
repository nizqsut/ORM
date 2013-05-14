#include "parser.h"
#include <QDebug>

Parser::Parser()
{
    m_modelNamePattern.setPattern("(ORMObject<\\w+>)");
}

void Parser::process(QStringList files)
{
    QString currentPath;
    foreach (currentPath, files)
    {
        QFile file(currentPath);
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        while(!stream.atEnd())
            m_currentFile += removeTrash(stream.readLine());
        m_currentFile = simplified(m_currentFile);
        QRegularExpressionMatchIterator i = m_modelNamePattern.globalMatch(m_currentFile);
        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();
            m_modelsRef.append(match.capturedRef());
        }
    }
}

QString Parser::getCurrentFile()
{
    return m_currentFile;
}

QString Parser::removeTrash(QString str)
{
    str.remove(QRegularExpression("\".*[^\\\\]\""));
    if(str.indexOf("//") < str.indexOf("*/")) //  abc//def
        str.remove(str.indexOf("//"), str.indexOf("*/") - str.indexOf("//"));
    str.remove(QRegularExpression("//.*"));
    return str;
}

QString &Parser::simplified(QString &str)
{
    str = str.simplified();
    str.remove(QRegularExpression("/\\*.*\\*/"));
    return str;
}