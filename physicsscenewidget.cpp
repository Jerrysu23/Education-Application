#include "physicsscenewidget.h"
#include <QPainter>
#include <QDebug>
#include <QBrush>

PhysicsSceneWidget::PhysicsSceneWidget(QWidget *parent) : QWidget(parent),
  world(b2Vec2(0.0f, -50.0f)),
  timer(this),
  baseImage(":/Dollar.png")
{
    setupPhysicsWorld();
    startPhysics();
}

void PhysicsSceneWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    b2Vec2 coinPos1 = coin1->GetPosition();
    b2Vec2 coinPos2 = coin2->GetPosition();
    b2Vec2 coinPos3 = coin3->GetPosition();
    b2Vec2 coinPos4 = coin4->GetPosition();
    b2Vec2 coinPos5 = coin5->GetPosition();
    b2Vec2 coinPos6 = coin6->GetPosition();
    b2Vec2 coinPos7 = coin7->GetPosition();
    b2Vec2 coinPos8 = coin8->GetPosition();
    b2Vec2 coinPos9 = coin9->GetPosition();
    b2Vec2 coinPos10 = coin10->GetPosition();

    int coin1DrawPosX = (int)((coinPos1.x * scaleFactorToPixels) - baseImage.size().height());
    int coin1DrawPosY = (int)(531 - (coinPos1.y * scaleFactorToPixels) - baseImage.size().height());

    int coin2DrawPosX = (int)((coinPos2.x * scaleFactorToPixels) - baseImage.size().height());
    int coin2DrawPosY = (int)(531 - (coinPos2.y * scaleFactorToPixels) - baseImage.size().height());

    int coin3DrawPosX = (int)((coinPos3.x * scaleFactorToPixels) - baseImage.size().height());
    int coin3DrawPosY = (int)(531 - (coinPos3.y * scaleFactorToPixels) - baseImage.size().height());

    int coin4DrawPosX = (int)((coinPos4.x * scaleFactorToPixels) - baseImage.size().height());
    int coin4DrawPosY = (int)(531 - (coinPos4.y * scaleFactorToPixels) - baseImage.size().height());

    int coin5DrawPosX = (int)((coinPos5.x * scaleFactorToPixels) - baseImage.size().height());
    int coin5DrawPosY = (int)(531 - (coinPos5.y * scaleFactorToPixels) - baseImage.size().height());

    int coin6DrawPosX = (int)((coinPos6.x * scaleFactorToPixels) - baseImage.size().height());
    int coin6DrawPosY = (int)(531 - (coinPos6.y * scaleFactorToPixels) - baseImage.size().height());

    int coin7DrawPosX = (int)((coinPos7.x * scaleFactorToPixels) - baseImage.size().height());
    int coin7DrawPosY = (int)(531 - (coinPos7.y * scaleFactorToPixels) - baseImage.size().height());

    int coin8DrawPosX = (int)((coinPos8.x * scaleFactorToPixels) - baseImage.size().height());
    int coin8DrawPosY = (int)(531 - (coinPos8.y * scaleFactorToPixels) - baseImage.size().height());

    int coin9DrawPosX = (int)((coinPos9.x * scaleFactorToPixels) - baseImage.size().height());
    int coin9DrawPosY = (int)(531 - (coinPos9.y * scaleFactorToPixels) - baseImage.size().height());

    int coin10DrawPosX = (int)((coinPos10.x * scaleFactorToPixels) - baseImage.size().height());
    int coin10DrawPosY = (int)(531 - (coinPos10.y * scaleFactorToPixels) - baseImage.size().height());

    painter.drawImage(coin1DrawPosX, coin1DrawPosY, baseImage.scaled(baseImage.width() * imageScales[0], baseImage.height() * imageScales[0]));
    painter.drawImage(coin2DrawPosX, coin2DrawPosY, baseImage.scaled(baseImage.width() * imageScales[1], baseImage.height() * imageScales[1]));
    painter.drawImage(coin3DrawPosX, coin3DrawPosY, baseImage.scaled(baseImage.width() * imageScales[2], baseImage.height() * imageScales[2]));
    painter.drawImage(coin4DrawPosX, coin4DrawPosY, baseImage.scaled(baseImage.width() * imageScales[3], baseImage.height() * imageScales[3]));
    painter.drawImage(coin5DrawPosX, coin5DrawPosY, baseImage.scaled(baseImage.width() * imageScales[4], baseImage.height() * imageScales[4]));
    painter.drawImage(coin6DrawPosX, coin6DrawPosY, baseImage.scaled(baseImage.width() * imageScales[5], baseImage.height() * imageScales[5]));
    painter.drawImage(coin7DrawPosX, coin7DrawPosY, baseImage.scaled(baseImage.width() * imageScales[6], baseImage.height() * imageScales[6]));
    painter.drawImage(coin8DrawPosX, coin8DrawPosY, baseImage.scaled(baseImage.width() * imageScales[7], baseImage.height() * imageScales[7]));
    painter.drawImage(coin9DrawPosX, coin9DrawPosY, baseImage.scaled(baseImage.width() * imageScales[8], baseImage.height() * imageScales[8]));
    painter.drawImage(coin10DrawPosX, coin10DrawPosY, baseImage.scaled(baseImage.width() * imageScales[9], baseImage.height() * imageScales[9]));

    painter.end();
}

void PhysicsSceneWidget::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);

    update();
}

void PhysicsSceneWidget::setupPhysicsWorld()
{
    imageScales.resize(10);
    for (int i = 0; i < 10; i++)
    {
        float scaleMax = 2.0f;
        float scale = ((float(rand()) / float((RAND_MAX))) * scaleMax) + 1;
        if (scale > 2)
            scale -= 1;
        imageScales[i] = scale;
    }

    yOffsets.resize(10);
    for (int i = 0; i < 10; i++)
    {
        float offsetMax = 10.0f;
        float offset = ((float(rand()) / float((RAND_MAX))) * offsetMax);
        yOffsets[i] = offset;
    }

    //
    // ---------- Setting up the "ground" for the coins to bounce on ----------
    //

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    //groundBox.SetAsBox(50.0f, 10.0f);
    groundBox.SetAsBox(50.0f, 0.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    //
    // ---------- Setting up the dynamic coin that bounces up and down ----------
    //

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef dynamicCoinDef;
    dynamicCoinDef.type = b2_dynamicBody;

    dynamicCoinDef.position.Set(1.0f, 11.0f + yOffsets[0]);
    coin1 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(2.5f, 11.0f + yOffsets[1]);
    coin2 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(4.0f, 11.0f + yOffsets[2]);
    coin3 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(5.0f, 11.0f + yOffsets[3]);
    coin4 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(6.5f, 11.0f + yOffsets[4]);
    coin5 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(8.0f, 11.0f + yOffsets[5]);
    coin6 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(9.0f, 11.0f + yOffsets[6]);
    coin7 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(10.0f, 11.0f + yOffsets[7]);
    coin8 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(12.0f, 11.0f + yOffsets[8]);
    coin9 = world.CreateBody(&dynamicCoinDef);

    dynamicCoinDef.position.Set(14.0f, 11.0f + yOffsets[9]);
    coin10 = world.CreateBody(&dynamicCoinDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.4f, 0.4f); // Original: 0.2 x 0.2

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // "Set the box density to be non-zero, so it will be dynamic." - instructors comment
    // Not really sure what this does exactly, we should just leave it
    fixtureDef.density = 1.0f;

    // Not sure what friction does in our case, so I just left it here.
    fixtureDef.friction = 0.3f;

    // Restitution is bounciness. '0.5' means it maintains 50% of its previous max height every time it bounces
    // If you set this to 1.0 it would keep bouncing at the same height forever.
    fixtureDef.restitution = 0.8f;

    // Add the shape to the body.
    coin1->CreateFixture(&fixtureDef);
    coin2->CreateFixture(&fixtureDef);
    coin3->CreateFixture(&fixtureDef);
    coin4->CreateFixture(&fixtureDef);
    coin5->CreateFixture(&fixtureDef);
    coin6->CreateFixture(&fixtureDef);
    coin7->CreateFixture(&fixtureDef);
    coin8->CreateFixture(&fixtureDef);
    coin9->CreateFixture(&fixtureDef);
    coin10->CreateFixture(&fixtureDef);
}

void PhysicsSceneWidget::startPhysics()
{
    connect(&timer, &QTimer::timeout, this, &PhysicsSceneWidget::updateWorld);
    timer.start(50);
}

void PhysicsSceneWidget::runPhysics_slot()
{
    setupPhysicsWorld();
}
