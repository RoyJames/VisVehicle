#include "glwidget.h"
#include <QGLWidget>
//#include <QOpenGLFunctions>
//#include <QGLFunctions>
//#include <QtOpenGL/QtOpenGL>
//#include <GL/glu.h>
//#include <GL/gl.h>
#include <locale.h>
#include <QColor>
#include <QBrush>


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    this->setAutoFillBackground(false);
    this->setAutoBufferSwap(false);
}

GLWidget::GLWidget(QWidget *parent, int n, int *offset, float *data_buffer,
                   QString x_name, QString y_name, QString z_name,
                   QString title) : QGLWidget(parent)
{
    this->setAutoFillBackground(false);
    this->setAutoBufferSwap(false);

    plot_data.n_of_curves = n;
    plot_data.offset_curves = new int[n];
    int tot = 0;
    for (int i = 0; i < n; i++)
    {
        plot_data.offset_curves[i] = offset[i];
        tot += offset[i];
    }
    tot *= 3;

    plot_data.point_data = new float[tot];
    for (int i = 0; i < tot; i++)
    {
        plot_data.point_data[i] = data_buffer[i];
    }

    plot_data.x_name = x_name;
    plot_data.y_name = y_name;
    plot_data.z_name = z_name;
    plot_data.title = title;
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    glFrontFace( GL_CW );

    // Enable back face culling
    //glEnable(GL_CULL_FACE);

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
    QPainter painter;
    painter.begin(this);
    painter.beginNativePainting();
    makeCurrent();
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();

    // Generate points data
    /*float point[300];
    for (int i = 0; i < 100; i++)
    {
        point[i*3] = (GLfloat)i / 100.0f - 0.5f;
        point[i*3 + 1] = point[i*3] * point[i*3];
        point[i*3 + 2] = 0;
    }
    */
    int vertexLocation = program.attributeLocation("a_position");
    program.enableAttributeArray(vertexLocation);
    //glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, point);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, this->plot_data.point_data);

    //qDebug() << "in excution:" << this->plot_data.offset_curves[0];

    GLfloat green[] = {0.0,1.0,0.0,1.0};
    program.setUniformValueArray("color", green, 1, 4);
    glDrawArrays(GL_LINE_STRIP, 0, this->plot_data.offset_curves[0]);

    program.disableAttributeArray(vertexLocation);
    program.release();
    glPopAttrib();

    painter.endNativePainting();

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));;
    painter.drawEllipse(60,30,10,30);
    painter.drawRect(20,20,10,10);

    painter.setPen(Qt::white);
    painter.drawText(60,60,tr("Test String!"));

    painter.end();
    swapBuffers();
    update();
}


