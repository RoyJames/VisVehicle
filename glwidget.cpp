#include "glwidget.h"
#include <QOpenGLFunctions>
#include <QGLFunctions>
#include <QGLWidget>
#include <QGLWidget>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <GL/gl.h>
#include <locale.h>
#include <QColor>
#include <QBrush>


GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}



void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2f,0.2f,0.2f,1.0f);
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    // Use QBasicTimer because its faster than QTimer
    //timer.start(12, this);
}

void GLWidget::initShaders()
{
    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QGLShader::Vertex, ":/shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QGLShader::Fragment, ":/shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void GLWidget::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    m_projection.setToIdentity();

    // Set perspective projection
    m_projection.perspective(fov, aspect, zNear, zFar);

}

void GLWidget::paintGL()
{
    QPainter painter(this);
    //painter.begin(this);
    painter.beginNativePainting();
    glPushAttrib( GL_ALL_ATTRIB_BITS );

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();
    // Generate points data
    GLfloat point[300];
    for (int i = 0; i < 100; i++)
    {
        point[i*3] = (GLfloat)i / 100.0f - 0.5f;
        point[i*3 + 1] = point[i*3] * point[i*3];
        point[i*3 + 2] = 0;
    }
    int vertexLocation = program.attributeLocation("a_position");
    program.enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, point);

    GLfloat green[] = {0.0,1.0,0.0,1.0};
    program.setUniformValueArray("color", green, 1, 4);
    glDrawArrays(GL_LINE_STRIP, 0, 50);
    GLfloat red[] = {1.0,0.0,0.0,1.0};
    program.setUniformValueArray("color", red, 1, 4);
    glDrawArrays(GL_LINE_STRIP, 49, 51);
    program.disableAttributeArray(vertexLocation);
    program.release();
    glPopAttrib();

    painter.endNativePainting();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setPen(Qt::white);
    painter.drawText(60,30,"TEST STRING! WHAT'S WRONG WITH THE TEXT?");
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));;
    painter.drawEllipse(60,30,10,30);
    painter.drawRect(20,20,160,160);
    painter.end();
}

void GLWidget::paintEvent(QPaintEvent *e)
{
}


