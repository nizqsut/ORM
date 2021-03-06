#include <QString>
#include <QtTest>
#include "ormwhere.cpp"

class Test_ORMWhereTest : public QObject
{
    Q_OBJECT
    
public:
    Test_ORMWhereTest();
    
private Q_SLOTS:
    void test_constructor();
    void test_operatorAND();
    void test_operatorOR();
    void test_operatorEquals();
};

Test_ORMWhereTest::Test_ORMWhereTest()
{

}

void Test_ORMWhereTest::test_constructor()
{
    ORMWhere *a = new ORMWhere("field1", ORMWhere::Equals, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 = '1')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::NotEquals, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 <> '1')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::LessThan, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 < '1')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::LessOrEquals, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 <= '1')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::GreaterThan, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 > '1')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::GreaterOrEquals, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 >= '1')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::IsNull, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 IS NULL)"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::StartsWith, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 LIKE '1%')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::EndsWith, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 LIKE '%1')"));
    delete a;
    a = new ORMWhere("field1", ORMWhere::Contains, "1");
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 LIKE '%1%')"));
    delete a;
    QList<QVariant> list;
    list << QVariant(1) << QVariant(2) << QVariant(3);
    a = new ORMWhere("field1", list);
    QCOMPARE(a->getWhereString(), QString("WHERE (field1 IN ('1', '2', '3'))"));
    delete a;
}

void Test_ORMWhereTest::test_operatorAND()
{
    ORMWhere a("field1", ORMWhere::LessThan, 1);
    ORMWhere b("field2", ORMWhere::GreaterThan, 2);
    QCOMPARE((a && b).getWhereString(), QString("WHERE ((field1 < '1') AND (field2 > '2'))"));
}

void Test_ORMWhereTest::test_operatorOR()
{
    ORMWhere a("field1", ORMWhere::LessThan, 1);
    ORMWhere b("field2", ORMWhere::GreaterThan, 2);
    QCOMPARE((a || b).getWhereString(), QString("WHERE ((field1 < '1') OR (field2 > '2'))"));
}

void Test_ORMWhereTest::test_operatorEquals()
{
    ORMWhere a;
    QCOMPARE(a.getWhereString().isEmpty(), true);
    ORMWhere b("field2", ORMWhere::GreaterOrEquals, 2);
    a = b;
    QCOMPARE(a.getWhereString(), QString("WHERE (field2 >= '2')"));
}

QTEST_APPLESS_MAIN(Test_ORMWhereTest)

#include "tst_test_ormwheretest.moc"
