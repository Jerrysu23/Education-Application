#include "textbox2danimationwidget.h"
#include <QPainter>
#include <QDebug>

textBox2DAnimationWidget::textBox2DAnimationWidget(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 200.0f)),
    timer(this),
    image(":/app_title.png")
{
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 40.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);

    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    connect(&timer, &QTimer::timeout, this, &textBox2DAnimationWidget::updateWorld);
    timer.start(50);


}

void textBox2DAnimationWidget::paintEvent(QPaintEvent *) {
    // Create a painter
    QPainter painter(this);
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    painter.drawImage(position.x, position.y, image);
    painter.end();
   }

void textBox2DAnimationWidget::updateWorld() {
    world.Step(1.0/60.0, 6, 2);
    update();
}

