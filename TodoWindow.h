#ifndef TODOWINDOW_H
#define TODOWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QWidget>
#include <QVector>
#include <QMovie>
#include <QDir>
#include <QCloseEvent>
#include <QFont>
#include <QDate>

#include "todo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TodoWindow : public QMainWindow
{
    Q_OBJECT

public:
    TodoWindow(QWidget *parent = nullptr);
    ~TodoWindow();
    void init();

    // 추가
    todo* User;
    void mkDir();

private:
    Ui::MainWindow *ui;

    // mem
    QLabel* mainTitle;
    QHBoxLayout* layout;
    qint32 m_margin = 35;
    qint32 naming = 0;
    QString inputName;
    QVector<QWidget*> newLines;
    void closeEvent(QCloseEvent * event);
    bool first; // 첫 로그인 확인

    // func
    void mkMemo(QString line, int check);
    void setMargin();
    void todo_clear();

public slots:
    void createMemo();
};
#endif // TODOWINDOW_H
