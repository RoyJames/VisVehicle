#include "glwidget.h"
#include <QOpenGLFunctions>
#include <QtOpenGL/QtOpenGL>
#include <GL/glu.h>
#include <GL/gl.h>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

void GLWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void GLWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
}

void GLWidget::paintGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);

    GLfloat point[300];
    for (int i = 0; i < 100; i++)
    {
        point[i*3] = (GLfloat)i / 100.0f - 0.5f;
        point[i*3 + 1] = point[i*3] * point[i*3];
        point[i*3 + 2] = 0;
    }

    const GLfloat gColors[] = {
        1.0f,0.0f,0.0f, 1.0f,
    };


    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, point);
    f->glEnableVertexAttribArray(0);    
    //f->glLineWidth(2.0);
    f->glDrawArrays(GL_LINE_STRIP, 0, 100);
}
