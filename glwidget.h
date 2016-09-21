#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QBasicTimer>
#include <QGLShaderProgram>
#include <QString>

typedef struct{
    float *point_data;
    int n_of_curves;
    int *offset_curves;
    int x_interval = 6;
    int y_interval = 6;
    QString x_name;
    QString y_name;
    QString z_name;
    QString title;
    float xmin;
    float ymin;
    float xmax;
    float ymax;
}plotinfo;

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = 0);
    GLWidget(QWidget *parent, int n, int *offset, float *data_buffer,
             QString x_name = "", QString y_name = "", QString z_name = "", QString title = "");

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void initShaders();
    void drawCoordinate(QPainter *painter);
    void rescaleData();

private:
    QBasicTimer timer;
    QGLShaderProgram program;
    QMatrix4x4 m_projection;
    plotinfo plot_data;
};

#endif // GLWIDGET_H
