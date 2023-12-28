#ifndef TEXTBOX2DANIMATIONWIDGET_H
#define TEXTBOX2DANIMATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

class textBox2DAnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit textBox2DAnimationWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void updateWorld();


private:
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
};

#endif // SCENEWIDGET_H
