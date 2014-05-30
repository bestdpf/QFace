#include<QtGui>
#include<QtOpenGL>
#include<QSettings>
#include"QtView.h"
#include<GL/glu.h>
#include<XFaceApp/Task.h>
#include<XFaceApp/XMLUtils.h>
#include<cstdio>
#include<boost/thread.hpp>
using XFaceApp::Task;
using XFaceApp::TaskDictionary;
using XFaceApp::XMLUtils;

using namespace boost;
using namespace net;

QtView::QtView(QWidget* parent):QGLWidget(parent){
    m_pApp=0;
    m_pCamera=0;
    m_init=false;
    xRot=0;
    yRot=0;
    zRot=0;
    m_settings= new QSettings(QString("QFace.ini"),QSettings::IniFormat);
    QVariant dummy;
    dummy=m_settings->value("Network/Port",50011);
    m_listeningPort=dummy.toString().toUInt();
    dummy=m_settings->value("MPEG-4/Initial-FDP",QString("alice.fdp"));
    m_initialFdp = dummy.toString().toStdString();
    dummy=m_settings->value("MPEG-4/Initial-FAP",QString("../Faps/joy.fap"));
    m_initialFap = dummy.toString().toStdString();
    m_initialFdpPath = "../Faces/alice/";
    m_timer = new QTimer(this);
    m_timer20 = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(OnTimer()));
    connect(m_timer20,SIGNAL(timeout()),this,SLOT(OnIdle()));
    qRegisterMetaType<std::string>();
    connect(this,SIGNAL(recvData(std::string)),this,SLOT(processRecvData(std::string)));
    //seems useless of idle signal
    //connect(m_timer,0,this,SLOT(OnIdle()));
    m_timer->start(10);
    m_timer20->start(20);
    m_server= new TCPServerSocket(m_listeningPort);
    //thread_group tg;
    boost::thread* th1 = new boost::thread(bind(&QtView::listenServer,this));
    th1->detach();
    //tg.add_thread(th1);
    //tg.join_all();
}
QtView::~QtView(){
    delete m_pCamera;
    delete m_pApp;
    delete m_timer;
    delete m_timer20;
    delete m_server;
}

void QtView::OnTimer(){
  if(m_pApp)m_pApp->processTask();
}

void QtView::OnIdle(){
  if(!m_pApp)return;
  //is it right? i don't know????
  makeCurrent();
  m_pApp->onActOldString();
  updateGL();
  //m_pApp->processTask();
}

void QtView::listenServer()
{
  char buff[4097];
  string str;
  while(true){
    TCPSocket *sock=m_server->accept();
    memset(buff,0,sizeof(buff));
    while(sock->recv(buff,4096)>0){
        //printf("get:\n%s\n",buff);
	str=string(buff);
	emit(recvData(str));
	/*
	bool ret=m_pApp->onActString(str);
	if(ret)m_pApp->onResumePlayback();
	else printf("open string failed\n");
	//m_pApp->onResumePlayback();
	*/
    }
    delete sock;
  }
}

void QtView::processRecvData(string str)
{
  printf("process Recv Data\n");
  if(m_pApp->onActString(str))m_pApp->onResumePlayback();
  else printf("open string failed return\n");
  updateGL();
}


void QtView::initGL(){
    QColor qtPurple = QColor::fromCmykF(0.5, 0.5 , 0.0, 0.0);
    qglClearColor(qtPurple.dark());
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    swapBuffers();
    printf("initGL succ\n");
}

void QtView::paintGL(){
    //printf("before paintGL\n");
    makeCurrent();
    if(!m_init){
      initGL();
      m_init = true;
      LoadFace();
    }
    else{
      Render();
    }
    //printf("paintGL succ\n");
}

void QtView::LoadFace()
{
    printf("begin to load face\n");
	if(m_pApp)delete m_pApp;
	m_pApp = new XFaceApp::QtFace(this);
    printf("call qtface\n");
	if (!m_pApp->init())
	{
        printf("mapp init error\n");
		delete m_pApp;
		m_pApp = 0;
		return;
	}
    printf("init mpapp\n");
	// and now we can init our face
	loadFDP(m_initialFdp, m_initialFdpPath);
    printf("has load fdp\n");
	// load the FAP file
	loadFAP(m_initialFap);
    printf("load face\n");
}

void QtView::loadFAP(const std::string& filename)
{
	if(!m_pApp)
		return;

	Task faptask("LOAD_FAP");
	faptask.pushParameter(filename);
	m_pApp->newTask(faptask);
	printf("load fap low in face view\n");
	updateGL();
}

void QtView::loadFDP(const std::string& filename, const std::string& path)
{
	printf("face view load fdp\n");
	if(!m_pApp){
        printf("fv m_papp is null\n");
		return;
    }
	Task fdptask("LOAD_FDP");
	fdptask.pushParameter(filename);
	fdptask.pushParameter(path);
	m_pApp->newTask(fdptask);
    printf("new task fv load fdp\n");
	// we have to process the task immediately! (crash otherwise)
	m_pApp->processTask();
    printf("fv load fdp before cammera\n");
	// update the camera
	if(m_pCamera)
	{
		m_pCamera->setAxisAngle(m_pApp->getFace()->getFDP()->getGlobalAxisAngle());
		m_pCamera->setTranslation(m_pApp->getFace()->getFDP()->getGlobalTranslation());
	}
    printf("before updateGL\n");
	updateGL();
}

void QtView::Render()
{
	if(!m_pApp)
		return;

	if (!m_pCamera)
	{
		int w, h;
		w=size().width();
		h=size().height();
		// Setup our viewport. 
		glViewport( 0, 0, w, h);

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
	    
		float ratio = (float)w / (float)h;
		gluPerspective( 30.0, ratio, 10.0, 1000.0 );
		glMatrixMode( GL_MODELVIEW );

		m_pCamera = new XFaceApp::ModelCamera;
		m_pCamera->setScreenSize(w, h);
		m_pCamera->setDistance(-700);
		m_pCamera->setMode(XFaceApp::ModelCamera::ZOOM);
	}

	//m_pCamera->apply();
	
	//dpf version rotate
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -700.0);
    glRotatef(xRot /1.0, 1.0, 0.0, 0.0);
    glRotatef(yRot /1.0 , 0.0, 1.0, 0.0);
    glRotatef(zRot /1.0, 0.0, 0.0, 1.0);
	//m_pCamera->setAxisAngle(AxisAngle(,0));
	Task rendertask("RENDER_FRAME");
	m_pApp->newTask(rendertask);
}

void QtView::test(){
    m_pApp->onResumePlayback();
}

void QtView::LoadIdentity(){
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -700.0);
    glRotatef(0 /1.0, 1.0, 0.0, 0.0);
    glRotatef(0/1.0 , 0.0, 1.0, 0.0);
    glRotatef(0 /1.0, 0.0, 0.0, 1.0);
    lastPos=QPoint(0,0);
    xRot=0;
    yRot=0;
    zRot=0;
    Render();
}

void QtView::OnPaint()
{
  //pass
}

QSize QtView::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

QSize QtView::sizeHint() const
 {
     return QSize(640, 480);
 }
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}
 

 //! [5]
void QtView::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}
//! [5]

void QtView::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void QtView::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void QtView::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 0.08* dy);
        setYRotation(yRot + 0.08 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 0.08 * dy);
        setZRotation(zRot + 0.08 * dx);
    }
    lastPos = event->pos();
}
