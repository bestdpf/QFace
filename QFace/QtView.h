#ifndef _QT_VIEW_H
#define _QT_VIEW_H

#include<QGLWidget>
#include<QTimer>
#include<QSettings>
#include<XFaceApp/ModelCamera.h>
#include"QtFace.h"
#include<Socket.h>
class QtView: public QGLWidget{
        Q_OBJECT
    private:
	std::string m_initialFap, m_initialFdp, m_initialFdpPath;
	XFaceApp::QtFace* m_pApp;
	bool m_init;
	XFaceApp::ModelCamera* m_pCamera;
	QTimer* m_timer;
	QTimer* m_timer20;
	QSettings* m_settings;
	unsigned long m_listeningPort;
	net::TCPServerSocket *m_server;
	int xRot,yRot,zRot;
	QPoint lastPos;
    public:
        QtView(QWidget* parent=0);
        ~QtView();
     QSize minimumSizeHint() const;
     QSize sizeHint() const;
    protected:
        void initGL();
        void paintGL();
	void LoadFace();
	void Render();
	void listenServer();
    void OnPaint();
    void mouseMoveEvent(QMouseEvent *event);
    protected slots:
	void OnTimer();
	void OnIdle();
	void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void processRecvData(std::string str);
    
signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void recvData(std::string str);
    public:
	void test();
	void LoadIdentity();
	void loadFDP(const std::string& filename, const std::string& path);
	void loadFAP(const std::string& filename);
	void setInitialFap(const std::string& filename) {m_initialFap = filename;}
	void setInitialFdp(const std::string& filename, const std::string path) {m_initialFdp = filename; m_initialFdpPath = path;}
};
Q_DECLARE_METATYPE(std::string)
#endif
