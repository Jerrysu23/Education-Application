#ifndef PHYSICSSCENEWIDGET_H
#define PHYSICSSCENEWIDGET_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>

class PhysicsSceneWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhysicsSceneWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

public slots:
    void updateWorld();
    void runPhysics_slot();

private:
    void setupPhysicsWorld();
    void startPhysics();
    int scaleFactorToPixels = 50; // See first comment in constructor (.cpp) for more information on what this is
    b2World world;
    b2Body* coin1;
    b2Body* coin2;
    b2Body* coin3;
    b2Body* coin4;
    b2Body* coin5;
    b2Body* coin6;
    b2Body* coin7;
    b2Body* coin8;
    b2Body* coin9;
    b2Body* coin10;
    QTimer timer;
    QImage baseImage;
    std::vector<float> yOffsets;
    std::vector<float> imageScales;
};

#endif // PHYSICSSCENEWIDGET_H
