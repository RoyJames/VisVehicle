#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLFunctions>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
protected:
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private:
    QMatrix4x4 m_projection;
};

#endif // GLWIDGET_H
