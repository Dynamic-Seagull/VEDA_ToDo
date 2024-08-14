#include "TodoWindow.h"
#include "./ui_mainwindow.h"

TodoWindow::TodoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), first(false)
{
    //ui->setupUi(this);

    // 기본 틀
    qint32 w = 350;
    qint32 h = 500;
    resize(w, h);
    setMinimumSize(w, h);
    setMaximumSize(w, h);

    system("chcp 65001");
    this->setStyleSheet("QLabel { font-family: Arial; font-size: 11pt; }");
    // 날짜 가져오기
    QDate today = QDate::currentDate();
    QString dateString = today.toString("yyyy-MM-dd");
    // 날짜 표시 QLabel 생성
    QLabel* dateLabel = new QLabel(this);
    dateLabel->setText(dateString);
    dateLabel->setAlignment(Qt::AlignCenter);
    // 날짜 라벨 위치 설정
    dateLabel->setGeometry(10, h - 30, w - 20, 20);
    dateLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    dateLabel->show();

    TodoWindow::mkDir();
    User = new todo;

    // 메모 생성
    QPushButton* createBttn = new QPushButton(this);
    createBttn->setIcon(QIcon(":/resource/add.png"));
    createBttn->setGeometry(300, 450, 50, 50);
    createBttn->setIconSize(QSize(50, 50));
    connect(createBttn, &QPushButton::clicked, this, &TodoWindow::createMemo);

    // 뒤로 가기
    QPushButton* prev = new QPushButton(this);
    prev->setIcon(QIcon(":/resource/undo.png"));
    prev->setGeometry(0, 0, 30, 30);
    prev->setIconSize(QSize(30, 30));
    connect(prev, &QPushButton::clicked, this, &TodoWindow::init);

    // 움짤
    mainTitle = new QLabel(this);
    QMovie* movie = new QMovie(":/resource/img.gif");
    movie->setScaledSize(QSize(180, 90));
    mainTitle->setMovie(movie);
    mainTitle->setGeometry(85, 10, 200, 90);
    movie->start();

    // 초기화
    init();
    this->setStyleSheet("background-color: #90CBFB");
}

TodoWindow::~TodoWindow()
{
    delete ui;
}

void TodoWindow::init()
{
    bool check = 0;
    int flag = 0;

    while (1)
    {
        if (!flag)
            inputName = QInputDialog::getText(this, "Wait", "메모 이름을 입력해주세요: ", QLineEdit::Normal, NULL, &check);
        if (flag)
            inputName = QInputDialog::getText(this, "Wait", "다시 입력해주세요: ", QLineEdit::Normal, NULL, &check);

        if (!check)
        {
            close();
            break;
        }
        else if (inputName.length() > 0)
        {
            first = true;
            this->setWindowTitle(inputName + "'s memo");

            // 작성한 파일이 있었는지 확인
            if (!(User->check(inputName)))
            {
                User->load(inputName);
                QVector<QString> lines = User->getList();

                for (auto& x: lines)
                {
                    QChar temp = x[0];
                    qint32 check = temp.digitValue();
                    QString input = x.mid(1);

                    mkMemo(input ,check);
                }
            }
            else
            {
                QMessageBox::information(this, "알림", "새 파일을 생성합니다.", QMessageBox::Yes);
                // 벡터 지우고 초기화 한 내용 출력
                todo_clear();
            }

            break;
        }
        else
            flag = 1;
    }
}

void TodoWindow::createMemo()
{
    // InputDialog
    bool check = false;
    QString input = QInputDialog::getText(this, "Wait", "내용을 입력해주세요: ", QLineEdit::Normal, NULL, &check);
    // 확인 누르면
    if (check)
    {
        // 값 제대로 입력 했으면
        if (input.size() > 0)
        {
            mkMemo(input, 1);

            // 데이터 저장
            User->insert(QString::number(1) + input);
        }
        else
            QMessageBox::warning(this, "알림", "값을 입력해주세요.", QMessageBox::Yes);
    }
}

void TodoWindow::mkDir()
{
    // 폴더 없으면 생성 (사용자 정보 저장용)
    QDir userInfoDir("./../../userInfo");
    if (!userInfoDir.exists())
    {
        if (userInfoDir.mkpath("."))  // 디렉토리 생성
        {
            qDebug() << "Directory created successfully";
        }
        else
        {
            qDebug() << "Failed to create directory";
        }
    }
}

void TodoWindow::mkMemo(QString line, int check)
{
    QPushButton* cBttn;
    QLabel* newText;

    if (!check)
    {
        cBttn = new QPushButton(QIcon(":/resource/true.png"), "");
        newText = new QLabel("<s>" + line + "</s>");
    }
    else
    {
        cBttn = new QPushButton(QIcon(":/resource/false.png"), "");
        newText = new QLabel(line);
    }

    // HBox
    layout = new QHBoxLayout();
    QPushButton* rBttn = new QPushButton(QIcon(":/resource/edit.png"), "");
    QPushButton* dBttn = new QPushButton(QIcon(":/resource/delete.png"), "");

    cBttn->setObjectName(QString::number(naming));
    rBttn->setObjectName(QString::number(naming));
    dBttn->setObjectName(QString::number(naming));

    // design
    newText->setAlignment(Qt::AlignCenter);
    qint32 size = 25;
    cBttn->setFixedSize(QSize(size, size));
    rBttn->setFixedSize(QSize(size, size));
    dBttn->setFixedSize(QSize(size, size));
    cBttn->setIconSize(QSize(size, size));
    rBttn->setIconSize(QSize(size, size));
    dBttn->setIconSize(QSize(size, size));
    newText->setStyleSheet("QLabel { background-color: #013368; color: white}");

    connect(cBttn, &QPushButton::clicked, this, [=](){
        cBttn->setIcon(QIcon(":/resource/true.png"));
        newText->setText("<s>" + newText->text() + "</s>");

        QPushButton* temp = dynamic_cast<QPushButton*>((sender()));
        QString name = temp->objectName();
        for (int i = 0; i < newLines.size(); i++)
        {
            if (newLines[i]->objectName() == name)
            {
                QString original = User->getList()[i];
                original = original.mid(1);
                User->modify(i + 1, QString::number(0) + original);
            }
        }
    });

    connect(rBttn, &QPushButton::clicked, this, [=](){
        QPushButton* temp = dynamic_cast<QPushButton*>((sender()));
        QString name = temp->objectName();
        for (int i = 0; i < newLines.size(); i++)
        {
            QString original = User->getList()[i];
            if (newLines[i]->objectName() == name && original[0] != QString::number(0)) // check 전 이면
            {
                QString input = QInputDialog::getText(this, "Wait", "내용을 입력해주세요: ", QLineEdit::Normal, NULL);
                newText->setText(input);
                User->modify(i + 1, QString::number(1) + input);
            }
        }
    });

    connect(dBttn, &QPushButton::clicked, this, [=](){
        QPushButton* temp = dynamic_cast<QPushButton*>((sender()));
        QString name = temp->objectName();
        for (int i = 0; i < newLines.size(); i++)
        {
            if (newLines[i]->objectName() == name)
            {
                newLines[i]->close();
                newLines.erase(newLines.begin() + i, newLines.begin() + i + 1);
                User->del(i + 1);
            }
        }
        setMargin();
    });

    layout->addWidget(cBttn);
    layout->addWidget(newText);
    layout->addWidget(rBttn);
    layout->addWidget(dBttn);

    // linked Widget
    QWidget* newLine = new QWidget(this);
    newLine->setGeometry(QRect(75, m_margin * newLines.size() + 115, 200, m_margin));
    newLine->setLayout(layout);
    newLine->setObjectName(QString::number(naming++));
    newLines.push_back(newLine);

    newLine->show();
}

void TodoWindow::setMargin()
{
    for (int i = 0; i < newLines.size(); i++)
        newLines[i]->setGeometry(QRect(75, m_margin * i + 115, 200, m_margin));
}

void TodoWindow::todo_clear()
{
    for (auto& x: newLines)
    {
        x->close();
        delete x;
    }

    newLines.clear();
    User->listClear();
}

void TodoWindow::closeEvent(QCloseEvent *event)
{
    if (first)
    {
         User->save(inputName);  // 창을 닫기 전에 데이터 저장
    }
    event->accept();  // 창 닫기 허용
}
