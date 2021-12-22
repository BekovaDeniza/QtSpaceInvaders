#ifndef CCANNON_H
#define CCANNON_H

#include "settings.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QKeyEvent>

enum class EColor
{
    Red, Pink, Blue
};

class CBullet;

class CCannon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CCannon(QGraphicsItem* pParent = nullptr);

    void Shoot();
signals:
    void sigIncreaseScore();
    void sigDecreaseScore();
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class CAlien : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CAlien(EColor eColor, QGraphicsItem* pParent = nullptr);

    EColor GetColor() const;
    void SetColor(EColor eColor);

signals:
    void sigDecreaseHealth();
    void sigGameOver();

public slots:
    void onMove();

private:
    EColor m_eColor;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class CBullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    CBullet(QGraphicsItem* pParent = nullptr);

signals:
    void sigIncreaseScore();
    void sigDecreaseScore();

public slots:
    void onMove();
private:
    EColor m_eColor;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

class CPoints : public QGraphicsTextItem
{
public:
    CPoints(QGraphicsItem *pParent = nullptr);

    void IncreaseScore();
    void DecreaseScore();
    void DecreaseHealth();

    int GetHealth() const;
    int GetScore() const;

private:
    int m_nHealth = gMaxHealth;
    int m_nScore  = 0;
};

#endif // CCANNON_H
