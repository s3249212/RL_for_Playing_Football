#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "model.h"
#include "graphicsobject.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QVector3D>
#include <QImage>
#include <QVector>
#include <memory>
#include <QMatrix4x4>
#include <vector>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    QOpenGLDebugLogger *debugLogger;
    QTimer timer; // timer used for animation

    QOpenGLShaderProgram normalShaderProgram,
                         gouraudShaderProgram,
                         phongShaderProgram,
                         waterShaderProgram;

    // Uniforms for the normal shader.
    GLint uniformModelViewTransformNormal;
    GLint uniformProjectionTransformNormal;
    GLint uniformNormalTransformNormal;

    // Uniforms for the gouraud shader.
    GLint uniformModelViewTransformGouraud;
    GLint uniformProjectionTransformGouraud;
    GLint uniformNormalTransformGouraud;

    GLint uniformMaterialGouraud;
    GLint uniformLightPositionGouraud;
    GLint uniformLightColourGouraud;

    GLint uniformTextureSamplerGouraud;

    // Uniforms for the phong shader.
    GLint uniformModelTransformPhong;
    GLint uniformViewTransformPhong;
    GLint uniformProjectionTransformPhong;
    GLint uniformNormalTransformPhong;

    GLint uniformMaterialPhong;
    GLint uniformLightPositionPhong;
    GLint uniformLightColourPhong;

    GLint uniformTextureSamplerPhong;

    // Buffers
    GLuint meshVAO;
    GLuint meshVBO;
    GLuint meshSize;

    // Texture
    GLuint texturePtr;

    // Transforms
    float scale = 1.f;
    QVector3D rotation;
    QMatrix4x4 projectionTransform;
    QMatrix4x4 viewTransform;
    QMatrix3x3 meshNormalTransform;
    QMatrix4x4 meshTransform;

    // Phong model constants.
    QVector4D material = {0.5, 0.5, 1, 5};
    QVector3D lightPosition = {1, 100, 1};
    QVector3D lightColour = {1, 1, 1};

    float yrotation;
    QVector3D translation;

    GraphicsObject obj;
    std::vector<GraphicsObject> objects;

    clock_t time = 0;

    GLuint uniformModelTransformWater;
    GLuint uniformViewTransformWater;
    GLuint uniformProjectionTransformWater;
    GLuint uniformNormalTransformWater;
    GLuint uniformMaterialWater;
    GLuint uniformLightPositionWater;
    GLuint uniformLightColourWater;
    GLuint uniformTextureSamplerWater;

public:
    enum ShadingMode : GLuint
    {
        PHONG = 0, NORMAL, GOURAUD, WATER
    };

    MainView(QWidget *parent = 0);
    ~MainView();

    void drawObject(GraphicsObject &obj);

    // Functions for widget input events
    void setRotation(int rotateX, int rotateY, int rotateZ);
    void translate(double x, double y, double z);
    void setScale(int scale);
    void setShadingMode(ShadingMode shading);

protected:
    void initializeGL();
    void resizeGL(int newWidth, int newHeight);
    void paintGL();

    // Functions for keyboard input events
    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);

    // Function for mouse input events
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

private slots:
    void onMessageLogged( QOpenGLDebugMessage Message );

private:
    void createShaderProgram();

    GraphicsObject loadObject(QString meshfile, QString texturefile);
    void loadMesh(GraphicsObject &obj, QString filename);

    // Loads texture data into the buffer of texturePtr.
    void loadTextures(GraphicsObject &obj, QString textureName);//void loadTextures();
    void loadTexture(QString file, GLuint texturePtr);

    void destroyModelBuffers();

    void updateProjectionTransform();
    void updateViewTransform();
    void updateModelTransforms();

    void updateNormalUniforms(GraphicsObject &obj);
    void updateGouraudUniforms(GraphicsObject &obj);
    void updatePhongUniforms(GraphicsObject &obj);
    void updateWaterUniforms(GraphicsObject &obj);

    // Useful utility method to convert image to bytes.
    QVector<quint8> imageToBytes(QImage image);

    // The current shader to use.
    ShadingMode currentShader = PHONG;
};

#endif // MAINVIEW_H
