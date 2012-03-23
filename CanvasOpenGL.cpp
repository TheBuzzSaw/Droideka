#include "CanvasOpenGL.hpp"
#include <QtOpenGL>

CanvasOpenGL::CanvasOpenGL(QWidget *inParent)
    : QGLWidget(QGLFormat(QGL::AlphaChannel
                          | QGL::Rgba
                          | QGL::DepthBuffer
                          | QGL::DoubleBuffer
                          | QGL::DeprecatedFunctions
                          ), inParent)
{
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onPulse()));
    timer->start(25);
    mSelectedCard = 0;
    mCardModel = 0;
    mTableModel = 0;
    mTableActor = 0;
    mTableTexture = 0;
    mMouseMode = None;
}

CanvasOpenGL::~CanvasOpenGL()
{
    destroyAll();

    delete mTableActor;
    delete mTableModel;
    delete mCardModel;

    deleteTexture(mTableTexture);
}

void CanvasOpenGL::onPulse()
{
    //mCamera.changeRotation(1.0f);
    //mCamera.changeAngle(-0.5f);
    mCamera.update();

    mHeadActor.updateMatrices(mat4f(), mCamera.matrix());
    updateGL();

    switch (mMouseMode)
    {
    case PanCamera:
    {
        if (mWillUpdatePanning)
        {
            vec3f delta = mMouse3D;

            delta[0] -= mAnchor3D[0];
            delta[1] -= mAnchor3D[1];
            delta[2] = 0.0f;

            delta[0] = -delta[0];
            delta[1] = -delta[1];

            mCamera.changePosition(delta);

            mWillUpdatePanning = false;
        }

        break;
    }

    case MoveCard:
    {
        vec4f delta = mMouse3D;

        delta[0] -= mAnchor3D[0];
        delta[1] -= mAnchor3D[1];

        float x = mOriginalPosition[0];
        float y = mOriginalPosition[1];

        x += delta[0];
        y += delta[1];

        mSelectedCard->position(x, y);

        break;
    }

    case None:
    {
        const float Extremity = 0.2f;
        vec3f hoverColor;
        hoverColor[0] = Extremity;
        hoverColor[1] = Extremity;
        hoverColor[2] = Extremity;

        vec3f black;

        CardActor* hoverCandidate = 0;
        for (int i = 0; i < mCardActors.size(); ++i)
        {
            CardActor* ca = mCardActors[i];

            if (ca->contains(mMouse3D[0], mMouse3D[1]))
            {
                if (!hoverCandidate || ca->z() > hoverCandidate->z())
                    hoverCandidate = ca;
            }
        }

        if (mSelectedCard)
            mSelectedCard->setHighlight(black);

        mSelectedCard = 0;

        if (hoverCandidate)
        {
            mSelectedCard = hoverCandidate;
            mSelectedCard->setHighlight(hoverColor);
        }
    }

    default:
        break;
    }
}

void CanvasOpenGL::initializeGL()
{
    mTableTexture = bindTexture(QImage("wood.jpg"), GL_TEXTURE_2D);

    mCardModel = new CardModel;
    mTableModel = new TableModel(mTableTexture);
    mTableActor = new TableActor(*mTableModel);

    mHeadActor.addChildNode(*mTableActor);
    mTableActor->addToChain(mHeadActor);

    GLuint frontTexture = loadCardTextureByName(QString("localuprising.gif"));
    GLuint backTexture = loadCardTextureByName(QString("liberation.gif"));

    for (int i = 0; i < 12; ++i)
    {
        CardActor* cardActor = new CardActor(*mCardModel, frontTexture,
            backTexture);

        float x = float(i) * (mCardModel->width() + 0.5f);
        cardActor->position(x, 0.0f);

        mHeadActor.addChildNode(*cardActor);
        cardActor->addToChain(mHeadActor);
        mCardActors.append(cardActor);
    }

    mCamera.setDistance(20.0f);
    mCamera.setAngle(-45.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glClearColor(0.1f, 0.1f, 0.6f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
    glColor3f(0.0f, 0.0f, 0.0f);
}

void CanvasOpenGL::resizeGL(int inWidth, int inHeight)
{
    glViewport(0, 0, inWidth, inHeight);
    glGetIntegerv(GL_VIEWPORT, mViewport);

    float ratio = float(inWidth) / float(inHeight);

    mProjectionMatrix.loadIdentity();
    mProjectionMatrix.perspective(30.0f, ratio, 1.0f, 1000.0f, true);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(mProjectionMatrix);
    glMatrixMode(GL_MODELVIEW);
}

void CanvasOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mHeadActor.drawChain();

    GLfloat depthSample;
    glReadPixels(mSampleX, mSampleY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT,
        &depthSample);
    unproject(mSampleX, mSampleY, depthSample,
        mat4f(mProjectionMatrix, mCamera.matrix()), mMouse3D);
}

void CanvasOpenGL::mousePressEvent(QMouseEvent* inEvent)
{
    switch (inEvent->button())
    {
    case Qt::LeftButton:
        if (mMouseMode == None)
        {
            mAnchor3D = mMouse3D;

            if (mSelectedCard)
            {
                mMouseMode = MoveCard;
                mOriginalPosition = mSelectedCard->position();
            }
            else
            {
                mAnchorX = inEvent->x();
                mAnchorY = inEvent->y();
                mMouseMode = PanCamera;
                mWillUpdatePanning = false;
            }
        }
        break;

    case Qt::MiddleButton:
    {
        qDebug() << mMouse3D[0] << mMouse3D[1] << mMouse3D[2];

        break;
    }

    case Qt::RightButton:
        if (mMouseMode == None)
        {
            if (mSelectedCard)
            {
                mSelectedCard->flip180();
            }
            else
            {
                mAnchorX = inEvent->x();
                mAnchorY = inEvent->y();
                mAnchor3D = mMouse3D;
                mMouseMode = RotateCamera;
            }
        }
        else if (mMouseMode == MoveCard)
        {
            mSelectedCard->rotate90();
        }

        break;

    default:
        break;
    }
}

void CanvasOpenGL::mouseReleaseEvent(QMouseEvent* inEvent)
{
    (void)inEvent;

    switch (inEvent->button())
    {
    case Qt::LeftButton:
        if (mMouseMode == PanCamera || mMouseMode == MoveCard)
            mMouseMode = None;
        break;

    case Qt::MiddleButton:
        break;

    case Qt::RightButton:
        if (mMouseMode == RotateCamera)
            mMouseMode = None;
        break;

    default:
        break;
    }
}

void CanvasOpenGL::mouseMoveEvent(QMouseEvent* inEvent)
{
    mSampleX = inEvent->x();
    mSampleY = height() - inEvent->y();

    switch (mMouseMode)
    {
    case PanCamera:
    {
        mWillUpdatePanning = true;
        break;
    }

    case RotateCamera:
    {
        const float Step = 0.5f;
        float deltaX = float(inEvent->x() - mAnchorX) * Step;
        float deltaY = float(inEvent->y() - mAnchorY) * Step;

        mAnchorX = inEvent->x();
        mAnchorY = inEvent->y();

        mCamera.changeAngle(deltaY);
        mCamera.changeRotation(deltaX);

        break;
    }

    default:
        break;
    }
}

void CanvasOpenGL::wheelEvent(QWheelEvent* inEvent)
{
    const float change = 3.0f;
    mCamera.changeDistance(inEvent->delta() > 0 ? -change : change);
}

void CanvasOpenGL::keyPressEvent(QKeyEvent* inEvent)
{
    switch (inEvent->key())
    {
    case Qt::Key_F:
    {
        if (mSelectedCard)
        {
            mSelectedCard->flip180();
        }
        break;
    }

    default:
        break;
    }
}

void CanvasOpenGL::destroyAll()
{
    for (int i = 0; i < mTextures.size(); ++i)
        deleteTexture(mTextures[i]);

    mTextures.clear();
    mTexturesByName.clear();

    while (!mCardActors.isEmpty())
        delete mCardActors.takeFirst();
}

void CanvasOpenGL::testFolders()
{
    QDir home = QDir::home();
    bool success = home.mkpath("Droideka/data/huh");
    qDebug() << (success ? "WOOT" : "dawww");
}

GLuint CanvasOpenGL::loadCardTextureByName(const QString& inName)
{
    GLuint outTexture = 0;

    QMap<QString, GLuint>::ConstIterator i = mTexturesByName.find(inName);

    if (i == mTexturesByName.end())
    {
        QImage image(inName);

        if (!image.isNull())
        {
            QImage square(QSize(512, 512), image.format());
            QPainter painter(&square);
            painter.drawImage(QRect(0, 0, 512, 512), image);
            outTexture = bindTexture(square, GL_TEXTURE_2D);
            mTextures.append(outTexture);
            mTexturesByName.insert(inName, outTexture);
        }
    }
    else
    {
        outTexture = i.value();
    }

    return outTexture;
}

void CanvasOpenGL::unproject(GLint inX, GLint inY, GLfloat inDepth,
    const mat4f& inModelViewProjectionMatrix, GLfloat *inResult)
{
    float v[4];

    v[0] = GLfloat(inX - mViewport[0]) * 2.0f / GLfloat(mViewport[2]) - 1.0f;
    v[1] = GLfloat(inY - mViewport[1]) * 2.0f / GLfloat(mViewport[3]) - 1.0f;
    v[2] = 2.0f * inDepth - 1.0f;
    v[3] = 1.0f;

    mat4f m;
    inModelViewProjectionMatrix.copyInverseTo(m);
    m.transform(v, inResult);
}

void CanvasOpenGL::onKeyPress(QKeyEvent* inEvent)
{
    keyPressEvent(inEvent);
}
