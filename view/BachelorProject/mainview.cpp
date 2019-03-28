#include "mainview.h"
#include "model.h"
#include "vertex.h"

#include <math.h>
#include <QDateTime>

/**
 * @brief MainView::MainView
 *
 * Constructor of MainView
 *
 * @param parent
 */
MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    //qDebug << "MainView constructor";

    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

/**
 * @brief MainView::~MainView
 *
 * Destructor of MainView
 * This is the last function called, before exit of the program
 * Use this to clean up your variables, buffers etc.
 *
 */
MainView::~MainView() {
    debugLogger->stopLogging();

    //qDebug << "MainView destructor";
    for(GraphicsObject &obj : objects){
        glDeleteTextures(1, &obj.texturePtr);
    }

    destroyModelBuffers();
}

// --- OpenGL initialization

/**
 * @brief MainView::initializeGL
 *
 * Called upon OpenGL initialization
 * Attaches a debugger and calls other init functions
 */
void MainView::initializeGL() {
    //qDebug << ":: Initializing OpenGL";
    initializeOpenGLFunctions();

    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
             this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        //qDebug << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    //qDebug << ":: Using OpenGL" << qPrintable(glVersion);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glClearColor(0.0, 1.0, 0.0, 1.0);

    createShaderProgram();

    GraphicsObject obj;
    /*GraphicsObject obj = loadObject(":/models/cat.obj", ":/textures/cat_diff.png");
    obj.setLocation(1, 0, -6);
    obj.setRotation(0, 0.1, 0.8);
    obj.setScale(0.4);
    obj.setTranslationMovement(0, -0.001, 0);
    obj.setRotationMovement(0.1, -0.01, 0);
    ////qDebug << obj.rotation << obj.rotationMovement;
    objects.push_back(obj);//= loadMesh(":/models/cat.obj");
    //loadMesh();
    //loadTextures(objects.at(objects.size() - 1), ":/textures/cat_diff.png");

    obj = loadObject(":/models/cat.obj", ":/textures/cat_spec.png");
    obj.setLocation(0, 0, -4);
    obj.setRotation(0, 0, 1);
    obj.setScale(0.2);
    obj.setTranslationMovement(0, 0.001, 0.003);
    obj.setRotationMovement(0, 0.001, 0);
    objects.push_back(obj);//= loadMesh(":/models/cat.obj");*/

    obj = loadObject(":/models/grid.obj", ":/textures/laca.png");
    obj.setLocation(0, 0, -4);
    obj.setRotation(-M_PI * 4 / 8, M_PI / 5, M_PI / 7);
    obj.setScale(1);
    obj.setTranslationMovement(0, 0, 0);
    obj.setRotationMovement(0.0001, 0, 0);
    objects.push_back(obj);//= loadMesh(":/models/cat.obj");

    /*obj = loadObject(":/models/cube.obj", ":/textures/rug_logo.png");
    obj.setLocation(0, -5, -10);
    obj.setRotation(0, 0, 1);
    obj.setScale(1);
    obj.setTranslationMovement(0, 0.0, 0);
    obj.setRotationMovement(0, 0.0, 0);
    objects.push_back(obj);//= loadMesh(":/models/cat.obj");

    //objects.push_back(loadMesh(":/models/cube.obj"));//= loadMesh(":/models/cat.obj");
    //loadMesh();
    loadTextures(objects.at(objects.size() - 1), ":/textures/cat_diff.png");
    objects.at(objects.size() - 1).setLocation(0, 0, -10);*/
    // Initialize transformations
    /*updateProjectionTransform();
    updateViewTransform();
    updateModelTransforms();*/

    timer.start(1000.0 / 60.0);

    yrotation = 0;

    translation.setX(0);
    translation.setY(0);
    translation.setZ(0);
}

void MainView::createShaderProgram()
{
    // Create Normal Shader program
    normalShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_normal.glsl");
    normalShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_normal.glsl");
    normalShaderProgram.link();

    // Create Gouraud Shader program
    gouraudShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_gouraud.glsl");
    gouraudShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_gouraud.glsl");
    gouraudShaderProgram.link();

    // Create Phong Shader program
    phongShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_phong.glsl");
    phongShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_phong.glsl");
    phongShaderProgram.link();

    waterShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vertshader_water.glsl");
    waterShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fragshader_water.glsl");
    waterShaderProgram.link();

    // Get the uniforms for the normal shader.
    uniformModelViewTransformNormal  = normalShaderProgram.uniformLocation("modelViewTransform");
    uniformProjectionTransformNormal = normalShaderProgram.uniformLocation("projectionTransform");
    uniformNormalTransformNormal     = normalShaderProgram.uniformLocation("normalTransform");

    // Get the uniforms for the gouraud shader.
    uniformModelViewTransformGouraud  = gouraudShaderProgram.uniformLocation("modelViewTransform");
    uniformProjectionTransformGouraud = gouraudShaderProgram.uniformLocation("projectionTransform");
    uniformNormalTransformGouraud     = gouraudShaderProgram.uniformLocation("normalTransform");
    uniformMaterialGouraud            = gouraudShaderProgram.uniformLocation("material");
    uniformLightPositionGouraud       = gouraudShaderProgram.uniformLocation("lightPosition");
    uniformLightColourGouraud         = gouraudShaderProgram.uniformLocation("lightColour");
    uniformTextureSamplerGouraud      = gouraudShaderProgram.uniformLocation("textureSampler");

    // Get the uniforms for the phong shader.
    uniformModelTransformPhong  = phongShaderProgram.uniformLocation("modelViewTransform");
    uniformViewTransformPhong = phongShaderProgram.uniformLocation("viewTransform");
    uniformProjectionTransformPhong = phongShaderProgram.uniformLocation("projectionTransform");
    uniformNormalTransformPhong     = phongShaderProgram.uniformLocation("normalTransform");
    uniformMaterialPhong            = phongShaderProgram.uniformLocation("material");
    uniformLightPositionPhong       = phongShaderProgram.uniformLocation("lightPosition");
    uniformLightColourPhong         = phongShaderProgram.uniformLocation("lightColour");
    uniformTextureSamplerPhong      = phongShaderProgram.uniformLocation("textureSampler");

    uniformModelTransformWater  = waterShaderProgram.uniformLocation("modelTransform");
    uniformViewTransformWater = waterShaderProgram.uniformLocation("viewTransform");
    uniformProjectionTransformWater = waterShaderProgram.uniformLocation("projectionTransform");
    uniformNormalTransformWater     = waterShaderProgram.uniformLocation("normalTransform");
    uniformMaterialWater            = waterShaderProgram.uniformLocation("material");
    uniformLightPositionWater       = waterShaderProgram.uniformLocation("lightPosition");
    uniformLightColourWater         = waterShaderProgram.uniformLocation("lightColour");
    uniformTextureSamplerWater      = waterShaderProgram.uniformLocation("textureSampler");
}

GraphicsObject MainView::loadObject(QString meshfile, QString texturefile){
    GraphicsObject obj;
    loadMesh(obj, meshfile);
    loadTextures(obj, texturefile);
    return obj;
}

void MainView::loadMesh(GraphicsObject &obj, QString filename)
{
    Model model(filename);
    model.unitize();
    QVector<float> meshData = model.getVNTInterleaved();

    obj.meshSize = model.getVertices().size();

    // Generate VAO
    glGenVertexArrays(1, &obj.vao);
    glBindVertexArray(obj.vao);

    // Generate VBO
    glGenBuffers(1, &obj.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);

    // Write the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), meshData.data(), GL_STATIC_DRAW);

    // Set vertex coordinates to location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Set vertex normals to location 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set vertex texture coordinates to location 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MainView::loadTextures(GraphicsObject &obj, QString textureName)
{
    glGenTextures(1, &obj.texturePtr);
    loadTexture(textureName, obj.texturePtr);
}

void MainView::loadTexture(QString file, GLuint texturePtr)
{
    // Set texture parameters.
    glBindTexture(GL_TEXTURE_2D, texturePtr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Push image data to texture.
    QImage image(file);
    QVector<quint8> imageData = imageToBytes(image);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
}

void MainView::drawObject(GraphicsObject &obj){
    //qDebug << "In drawObject0" << obj.getTranslation() << obj.getRotation();
    obj.updateModelTransforms(scale);

    //qDebug << "In drawObject" << obj.getTranslation() << obj.getRotation();

    switch (currentShader) {
    case NORMAL:
        updateNormalUniforms(obj);
        break;
    case GOURAUD:
        updateGouraudUniforms(obj);
        break;
    case PHONG:
        updatePhongUniforms(obj);
        break;
    case WATER:
        updateWaterUniforms(obj);
        break;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, obj.texturePtr);

    glBindVertexArray(obj.vao);
    glDrawArrays(GL_TRIANGLES, 0, obj.meshSize);
    //qDebug << "In drawObject2" << obj.getTranslation() << obj.getRotation();
}

// --- OpenGL drawing

/**
 * @brief MainView::paintGL
 *
 * Actual function used for drawing to the screen
 *
 */
void MainView::paintGL() {
    // Clear the screen before rendering
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto obj : objects){
        //qDebug << "In paintGl" << obj.getTranslation() << obj.getRotation();
    }
    /*yrotation += 0.01;

    QVector3D step(0.0001, 0, 0);
    QMatrix4x4 rotationMatrix;
    rotationMatrix.rotate(yrotation, 0, 0);
    step = rotationMatrix * step;

    translation += step;*/



    // Choose the selected shader.
    QOpenGLShaderProgram *shaderProgram;

    //updateModelTransforms();
    //update();

    switch (currentShader) {
    case NORMAL:
        shaderProgram = &normalShaderProgram;
        shaderProgram->bind();
        break;
    case GOURAUD:
        shaderProgram = &gouraudShaderProgram;
        shaderProgram->bind();
        break;
    case PHONG:
        shaderProgram = &phongShaderProgram;
        shaderProgram->bind();
        break;
    case WATER:
        shaderProgram = &waterShaderProgram;
        shaderProgram->bind();
        break;
    }
    // Set the texture and draw the mesh.
    for(GraphicsObject& obj : objects){
        drawObject(obj);
        //qDebug << "###---In paintGl2" << obj.getTranslation() << obj.getRotation();
    }

    shaderProgram->release();
}

/**
 * @brief MainView::resizeGL
 *
 * Called upon resizing of the screen
 *
 * @param newWidth
 * @param newHeight
 */
void MainView::resizeGL(int newWidth, int newHeight)
{
    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
    updateProjectionTransform();
}

void MainView::updateNormalUniforms(GraphicsObject &obj)
{
    glUniformMatrix4fv(uniformProjectionTransformNormal, 1, GL_FALSE, projectionTransform.data());
    glUniformMatrix4fv(uniformModelViewTransformNormal, 1, GL_FALSE, obj.meshTransform.data());
    glUniformMatrix3fv(uniformNormalTransformNormal, 1, GL_FALSE, obj.meshNormalTransform.data());
}

void MainView::updateGouraudUniforms(GraphicsObject &obj)
{
    glUniformMatrix4fv(uniformProjectionTransformGouraud, 1, GL_FALSE, projectionTransform.data());
    glUniformMatrix4fv(uniformModelViewTransformGouraud, 1, GL_FALSE, obj.meshTransform.data());
    glUniformMatrix3fv(uniformNormalTransformGouraud, 1, GL_FALSE, obj.meshNormalTransform.data());

    glUniform4fv(uniformMaterialGouraud, 1, &material[0]);
    glUniform3fv(uniformLightPositionGouraud, 1, &lightPosition[0]);
    glUniform3fv(uniformLightColourGouraud, 1, &lightColour[0]);

    glUniform1i(uniformTextureSamplerGouraud, 0); // Redundant now, but useful when you have multiple textures.
}

void MainView::updatePhongUniforms(GraphicsObject &obj)
{
    glUniformMatrix4fv(uniformProjectionTransformPhong, 1, GL_FALSE, projectionTransform.data());
    glUniformMatrix4fv(uniformModelTransformPhong, 1, GL_FALSE, obj.meshTransform.data());
    glUniformMatrix4fv(uniformViewTransformPhong, 1, GL_FALSE, viewTransform.data());
    glUniformMatrix3fv(uniformNormalTransformPhong, 1, GL_FALSE, obj.meshNormalTransform.data());

    glUniform4fv(uniformMaterialPhong, 1, &material[0]);
    glUniform3fv(uniformLightPositionPhong, 1, &lightPosition[0]);
    glUniform3f(uniformLightColourPhong, lightColour.x(), lightColour.y(), lightColour.z());

    glUniform1i(uniformTextureSamplerPhong, 0);
}

void MainView::updateWaterUniforms(GraphicsObject &obj)
{
    glUniformMatrix4fv(uniformProjectionTransformWater, 1, GL_FALSE, projectionTransform.data());
    glUniformMatrix4fv(uniformModelTransformWater, 1, GL_FALSE, obj.meshTransform.data());
    glUniformMatrix4fv(uniformViewTransformWater, 1, GL_FALSE, viewTransform.data());
    glUniformMatrix3fv(uniformNormalTransformWater, 1, GL_FALSE, obj.meshNormalTransform.data());

    //glUniform4fv(uniformMaterialPhong, 1, &material[0]);
    //glUniform3fv(uniformLightPositionPhong, 1, &lightPosition[0]);
    //glUniform3f(uniformLightColourPhong, lightColour.x(), lightColour.y(), lightColour.z());

    //glUniform1i(uniformTextureSamplerPhong, 0);
}

void MainView::updateProjectionTransform()
{
    float aspect_ratio = static_cast<float>(width()) / static_cast<float>(height());
    projectionTransform.setToIdentity();
    projectionTransform.perspective(60, aspect_ratio, 0.2, 20);
}

void MainView::updateModelTransforms()
{
    //qDebug << "Begin" << endl;
    //qDebug << "In mainview::updateModelTransform" << obj.getTranslation() << obj.getRotation();
    for(auto obj: objects){
        obj.updateModelTransforms(scale);
        /*//qDebug << "It is looping!" << endl;
        obj.meshTransform.setToIdentity();
        obj.meshTransform.translate(0 + obj.translation[0], 0 + obj.translation[1], -4 + obj.translation[2]);
        //obj.meshTransform.scale(scale);
        QVector3D newRotation = obj.rotation;
        //newRotation[1] += yrotation;
        obj.meshTransform.rotate(QQuaternion::fromEulerAngles(newRotation));
        obj.meshNormalTransform = obj.meshTransform.normalMatrix();*/
    }
}

void MainView::updateViewTransform()
{
    viewTransform.setToIdentity();
    QVector3D up(0, 1, 0);
    //viewTransform.lookAt(rotation, objects.at(0).translation, up);
    //viewTransform.translate(translation[0], translation[1], translation[2]);
    //viewTransform.scale(scale);
    //newRotation[1] += yrotation;
    qDebug() << translation;
    viewTransform.translate(translation);
    viewTransform.rotate(QQuaternion::fromEulerAngles(rotation));
    //viewNormalTransform = viewTransform.normalMatrix();

}
// --- OpenGL cleanup helpers

void MainView::destroyModelBuffers()
{
    glDeleteBuffers(1, &obj.vbo);
    glDeleteVertexArrays(1, &obj.vao);
}

// --- Public interface

void MainView::setRotation(int rotateX, int rotateY, int rotateZ)
{
    rotation = { static_cast<float>(rotateX), static_cast<float>(rotateY), static_cast<float>(rotateZ) };
    //updateModelTransforms();
    updateViewTransform();
}

void MainView::translate(double x, double y, double z){
    translation[0] += x;
    translation[1] += y;
    translation[2] += z;
}

void MainView::setScale(int newScale)
{
    scale = static_cast<float>(newScale) / 100.f;
    updateModelTransforms();
}

void MainView::setShadingMode(ShadingMode shading)
{
    //qDebug << "Changed shading to" << shading;
    currentShader = shading;
}

// --- Private helpers

/**
 * @brief MainView::onMessageLogged
 *
 * OpenGL logging function, do not change
 *
 * @param Message
 */
void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}

