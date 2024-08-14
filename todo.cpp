#include "todo.h"

todo::todo(QWidget *parent) : QWidget(parent)
{
    m_list.clear();
    c_list.clear();
}

todo::~todo()
{
    m_list.clear();
    c_list.clear();
}

void todo::setName(QString s)
{
    name = s;
}

bool todo::check(QString name) const
{
    QString fileName = "./../../userInfo/" + name + ".txt";
    QFile checkFile(fileName);
    return !checkFile.exists();
}

void todo::load(QString name)
{
    QString fileName = "./../../userInfo/" + name + ".txt";
    QFile loadfile(fileName);
    loadfile.open(QFile::ReadOnly|QFile::Text);

    m_list.clear();

    QTextStream in(&loadfile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        m_list.append(line);
    }

    loadfile.close();

    if (m_list.size() > 0)
    {
        // qDebug() << "리스트 불러오기가 완료 되었습니다.";
        QMessageBox::information(this, "알림", "파일 불러오기에 성공했습니다.", QMessageBox::Yes);
    }
    else
    {
        // qDebug() << "파일이 비어있어 불러오기를 실패하였습니다.";
        QMessageBox::information(this, "알림", "파일이 비어있어 불러오기에 실패하였습니다.", QMessageBox::Yes);
    }

}

void todo::save(QString name)
{
    QString fileName = "./../../userInfo/" + name + ".txt";
    QFile saveFile(fileName);

    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //qDebug() << "파일을 열 수 없습니다.\n";
        QMessageBox::warning(this, "알림", "파일을 열 수 없습니다.", QMessageBox::Ok);
        return;
    }
    QTextStream out(&saveFile);
    out.setEncoding(QStringConverter::Utf8);
    for (auto& x : m_list)
    {
        out << x << "\n";
    }
    //qDebug() << "저장 완료";
    QMessageBox::information(this, "알림", "저장이 완료되었습니다.", QMessageBox::Yes);
    saveFile.close();
}

QVector<QString>& todo::getList()
{
    return m_list;
}

void todo::insert(QString input)
{
    m_list.append(input);
}

void todo::del(int idx)
{
    if (m_list.size() < idx)
        qDebug()<< "Error : 범위를 벗어났습니다.";
    else
    {
        m_list.removeAt(idx-1);
        //qDebug() << QString::number(idx) << "번 째 할 일 목록 삭제가 완료되었습니다.";
    }
}

void todo::modify(int idx, QString input)
{
    if (m_list.size() < idx)
        qDebug()<< "Error : 범위를 벗어났습니다.";
    else
    {
        m_list[idx - 1] = input;
        //qDebug() << "수정 완료";
    }
}

void todo::listClear()
{
    m_list.clear();
}
