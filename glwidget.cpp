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

#include <assert.h>
#include <math.h>
#include "definitions.h"


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
    plot_data.offset_curves = new int[n + 1];
    plot_data.offset_curves[n] = 0;
    for (int i = 0; i < n; i++)
    {
        plot_data.offset_curves[i] = offset[i];
        plot_data.offset_curves[n] += plot_data.offset_curves[i];
    }    
    plot_data.xmax = -(float)INFINITE;
    plot_data.ymax = -(float)INFINITE;
    plot_data.xmin = (float)INFINITE;
    plot_data.ymin = (float)INFINITE;

    int tot = plot_data.offset_curves[n] * 3;
    plot_data.point_data = new float[tot];
    for (int i = 0; i < tot; i++)
    {
        plot_data.point_data[i] = data_buffer[i];
        // record maximum and minimum of original data while reading
        if ((i % 3) == 0)
        {
            plot_data.xmax = (plot_data.xmax > data_buffer[i]) ? plot_data.xmax : data_buffer[i];
            plot_data.xmin = (plot_data.xmin < data_buffer[i]) ? plot_data.xmin : data_buffer[i];
        }else if ((i % 3) == 1)
        {
            plot_data.ymax = (plot_data.ymax > data_buffer[i]) ? plot_data.ymax : data_buffer[i];
            plot_data.ymin = (plot_data.ymin < data_buffer[i]) ? plot_data.ymin : data_buffer[i];
        }
    }

    plot_data.x_name = x_name;
    plot_data.y_name = y_name;
    plot_data.z_name = z_name;
    plot_data.title = title;

    rescaleData();
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

void GLWidget::drawCoordinate(QPainter *painter)
{
    int w = painter->window().width();
    int h = painter->window().height();
    QFontMetrics metrics = painter->fontMetrics();
    int textHeight = metrics.ascent() + metrics.descent();
    float deltaX = (float)w / plot_data.x_interval;

    // draw bounding box
    painter->drawRect(w * COORD_TOP_X, h * COORD_TOP_Y,
                       w * (COORD_BOTTOM_X - COORD_TOP_X), h * (COORD_BOTTOM_Y - COORD_TOP_Y));

    // draw horizontal ticks
    for (int i = 1; i <= plot_data.x_interval; i++) {
        QString tick = QString("%1").arg(plot_data.xmin + (plot_data.xmax - plot_data.xmin) * i / plot_data.x_interval);
        int stringWidth = metrics.width(tick);
        painter->drawLine(w * COORD_TOP_X + deltaX * i, h * COORD_BOTTOM_Y, w * COORD_TOP_X + deltaX * i, h * COORD_BOTTOM_Y + 4);
        int monthX = deltaX * (i - 1) + ((deltaX - stringWidth) / 2);
        painter->drawText(monthX, h * COORD_BOTTOM_Y + textHeight, tick);
    }


    // draw vertical ticks
}

void GLWidget::rescaleData()
{
    float xrange = plot_data.xmax - plot_data.xmin;
    float yrange = plot_data.ymax - plot_data.ymin;
    //plot_data.ymax += yrange * 0.1;
    //plot_data.ymin -= yrange * 0.1;
    //yrange = plot_data.ymax - plot_data.ymin;
    assert(xrange > 0);
    assert(yrange > 0);
    int n = plot_data.offset_curves[plot_data.n_of_curves];
    for (int i = 0; i < n; i++)
    {
        plot_data.point_data[i * 3] = (plot_data.point_data[i * 3] - plot_data.xmin) / xrange;
        plot_data.point_data[i * 3 + 1] = (plot_data.point_data[i * 3 + 1] - plot_data.ymin) / yrange;
    }
}

void GLWidget::paintGL()
{
    QPainter *painter = new QPainter();
    painter->begin(this);
    painter->beginNativePainting();
    makeCurrent();
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program.bind();
    int vertexLocation = program.attributeLocation("a_position");
    program.enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, this->plot_data.point_data);

    GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
    program.setUniformValueArray("color", green, 1, 4);

    glPushMatrix();
    glTranslatef((COORD_TOP_X - 0.5) * 2, (0.5 - COORD_BOTTOM_Y) * 2, 1);
    glScalef(fabs(COORD_BOTTOM_X - COORD_TOP_X) * 2, fabs(COORD_TOP_Y - COORD_BOTTOM_Y) * 2, 1);
    glDrawArrays(GL_LINE_STRIP, 0, this->plot_data.offset_curves[0]);
    glPopMatrix();

    program.disableAttributeArray(vertexLocation);
    program.release();
    glPopAttrib();

    painter->endNativePainting();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);
    painter->setPen(Qt::white);
    //painter->drawText(60,60,tr("Test String!"));
    drawCoordinate(painter);

    painter->end();
    swapBuffers();
    update();
}


