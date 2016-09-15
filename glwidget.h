#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QBasicTimer>
#include <QGLShaderProgram>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintEvent(QPaintEvent *e);
    void initShaders();

private:
    QBasicTimer timer;
    QGLShaderProgram program;
    QMatrix4x4 m_projection;
};

#endif // GLWIDGET_H
