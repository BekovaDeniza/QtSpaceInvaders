#include "spaceinvaders.h"
#include "button.h"
#include <QTimer>

//Инициализация сцены
CSpaceInvaders::CSpaceInvaders(QSize oScreenSize, QWidget *pParent)
    : QGraphicsView(pParent), m_oScreenSize(oScreenSize)
{
    QGraphicsScene* pScene = new QGraphicsScene();
    setScene(pScene);

    pScene->setSceneRect(0, 0, m_oScreenSize.width(), m_oScreenSize.height());

    setBackgroundBrush(QBrush(QImage(":/Resources/SpaceInvadersBg.jpg")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCursor(Qt::PointingHandCursor);
    setStyleSheet("border-style:none");
}

//Меню игры
void CSpaceInvaders::Menu()
{
    scene()->clear();
//    Добавляем кнопку для начала игры
    Button *retryButton = new Button(QString("Играть"));
    int xRetryPos = this->width()/2 - retryButton->boundingRect().width()/2;
    int yRetryPos = 275;
    retryButton->setPos(xRetryPos, yRetryPos);
    connect(retryButton, &Button::clicked, this, &CSpaceInvaders::Run);
    scene()->addItem(retryButton);
//    добавляем кнопку для выхода
    Button *exitButton = new Button(QString("Выход"));
    int xExitPos = this->width()/2 - exitButton->boundingRect().width()/2;
    int yExitPos = 350;
    exitButton->setPos(xExitPos, yExitPos);
    connect(exitButton, &Button::clicked, this, &CSpaceInvaders::onGameOver);
    scene()->addItem(exitButton);
}

//Запуск игры
void CSpaceInvaders::Run()
{
    scene()->clear();//очищаем сцену
//    setCursor(Qt::BlankCursor);

    m_pCannon = new CCannon();//создаем и добавляем на сцену игрока
    m_pCannon->setPos(m_oScreenSize.width() / 2, m_oScreenSize.height() - gCannonSize.height());
    m_pCannon->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCannon->setFocus();
    scene()->addItem(m_pCannon);

    connect(m_pCannon, &CCannon::sigIncreaseScore, this, &CSpaceInvaders::onIncreaseScore);
    connect(m_pCannon, &CCannon::sigDecreaseScore, this, &CSpaceInvaders::onDecreaseScore);

    m_pPoints = new CPoints();//создание и добавление баллов
    scene()->addItem(m_pPoints);

    pTimer = new QTimer(this);
    connect(pTimer, &QTimer::timeout, this, &CSpaceInvaders::onCreateEnemy);
    pTimer->start(2000);
}

//Чек поинт для проверки состояния очков жизни
void CSpaceInvaders::CheckPoints()
{
    if ((m_pPoints->GetHealth() <= 0))//если жизней не осталось, запускаем по новой
    {
        pTimer->stop();
        Menu();
    }
}

//Обработка кнопок
void CSpaceInvaders::keyPressEvent(QKeyEvent *pEvent)
{
    if (m_pCannon == nullptr)
        return;

    switch (pEvent->key())
    {
        case Qt::Key_Left://движение в лево
            if (m_pCannon->pos().x() > 0)
                m_pCannon->setPos(m_pCannon->x() - 20, m_pCannon->y());
            break;

        case Qt::Key_Right://движение в право
            if ((m_pCannon->pos().x() + gCannonSize.width()) < m_oScreenSize.width())
                m_pCannon->setPos(m_pCannon->x() + 20, m_pCannon->y());
            break;

        case Qt::Key_Space://выстрел
        {
            m_pCannon->Shoot();
            break;

        }
        case Qt::Key_Escape://выход из игры
        {
            onGameOver();
        }
        case Qt::Key_B://обмен баллов на жизнь
        {
            onDecreaseScore();
        }
    }
}

//добавление врага
void CSpaceInvaders::onCreateEnemy()
{
    int nPos = rand() % m_oScreenSize.width();
    int nColor = rand() % 3;

    CAlien *pAlien = new CAlien(static_cast<EColor>(nColor));
    pAlien->setPos(nPos, 0);

    scene()->addItem(pAlien);

    connect(pAlien, &CAlien::sigGameOver, this, &CSpaceInvaders::Menu);
    connect(pAlien, &CAlien::sigDecreaseHealth, this, &CSpaceInvaders::onDecreaseHealth);
}

//добавление баллов
void CSpaceInvaders::onIncreaseScore()
{
    m_pPoints->IncreaseScore();
    CheckPoints();
}

//обмен баллов на жизнь
void CSpaceInvaders::onDecreaseScore()
{
    m_pPoints->DecreaseScore();
    CheckPoints();
}

//отнимание жизни
void CSpaceInvaders::onDecreaseHealth()
{
    m_pPoints->DecreaseHealth();
    CheckPoints();
}

//выход из игры
void CSpaceInvaders::onGameOver()
{
    close();
}

