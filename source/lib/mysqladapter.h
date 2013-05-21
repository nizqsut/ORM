#ifndef MYSQLADAPTER_H
#define MYSQLADAPTER_H

#include <QVariant>
#include <QSqlRecord>
#include <QStringList>
#include <QSqlField>
#include "ormabstractadapter.h"

class MySqlAdapter : public ORMAbstractAdapter
{
public:
    MySqlAdapter();
    bool createDatabase(const QString &name);
    bool createTable(const QString &tableName, const QHash<QString, QString> &info);
    bool createTableRelations(const QString &parent, Relation rel, const QString &child);
    bool dropTable(const QString &tableName);
    bool dropDatabase(const QString &name);
    int addRecord(const QString &tableName, const QHash<QString, QVariant> &info);
    bool updateRecord(const QString &tableName, const qlonglong id, const QHash<QString, QVariant> &info);
    QList<QSqlRecord> find(const QString &tableName, const QString &params);
    virtual QSqlRecord first(const QString &tableName);
    virtual QSqlRecord last(const QString &tableName);
    virtual bool remove(const QString &tableName, const QString &params);
    virtual int count(const QString &tableName, const QString &arg);
    virtual int countBy(const QString &tableName, const QString &params);
    virtual double calculation(Calculation func, const QString &tableName, const QString &fieldName, const QString &params);
    virtual QHash<QString, QList<QSqlRecord> > includes(const QString &parentModel, const QStringList &childModels, const QString &params);

protected:
    void fillTableTypes();

private:
    void initDB(const QString &name);
};

#endif // MYSQLADAPTER_H
