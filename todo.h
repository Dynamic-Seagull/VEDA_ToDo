#ifndef TODO_H
#define TODO_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QCheckBox>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QCheckBox>
#include <QStringConverter>
#include <QMessageBox>

class todo : public QWidget
{
    Q_OBJECT
private:
    QString name;
    QVector<QString> m_list;
    QVector<qint32> c_list;

public:
    todo(QWidget *parent = nullptr);
    ~todo();
    bool check(QString name) const;
    void load(QString name);
    void save(QString name);
    QVector<QString>& getList();
    void insert(QString input);
    void del(int idx);
    void modify(int idx, QString input);
    void listClear();

public slots:
    void setName(QString s);

};

#endif // TODO_H
