#ifndef _QFACE_H
#define _QFACE_H
#include<cstdio>
#include<QtCore/QCoreApplication>
#include<QtGui/QMainWindow>
#include<QtGui/QPushButton>
#include<QLayout>
#include<QtGui>
#include"QtView.h"
namespace QFace{
class QWindow: public QMainWindow{
    Q_OBJECT
public:
    QWindow(QWidget* parent):QMainWindow(parent){
        resize(sizeHint());
        m_button_start=new QPushButton("start",this);
	m_button_id=new QPushButton("identity",this);
	//m_button_start->resize(QSize(100,50));
	//m_button_id->resize(QSize(100,50));
        m_viewer=new QtView(this);
        m_viewer->resize(m_viewer->sizeHint());
        connect(m_button_start,SIGNAL(released()),this,SLOT(HandleStart()));
	connect(m_button_id,SIGNAL(released()),this,SLOT(HandleIdentity()));
        m_layout=new QHBoxLayout;
        m_layout->addWidget(m_viewer);
	QGroupBox *qb=new QGroupBox(this);
	QHBoxLayout *b_layout=new QHBoxLayout(this);
	b_layout->addWidget(m_button_id);
	b_layout->addWidget(m_button_start);
	qb->setLayout(b_layout);
	qb->resize(QSize(200,70));
	 //qb->addButton(m_button_id);
	//qb->addButton(m_button_start);
	m_layout->addWidget(qb);
        //m_layout->addWidget(m_button_start);
	//m_layout->addWidget(m_button_id);
        m_viewer->lower();
        setLayout(m_layout);
        setCentralWidget(m_viewer);
        //m_viewer->show();
        setWindowTitle("QFace");
    }
     QSize minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize sizeHint() const
 {
     return QSize(800, 600);
 }

private slots:
    void HandleStart(){
        printf("handle start button");
        m_viewer->test();
    };
    void HandleIdentity(){
	m_viewer->LoadIdentity();
    }
private:
    QPushButton* m_button_start,*m_button_id;
    QtView* m_viewer;
    QLayout *m_layout;
};
}//end of namespace QFace
#endif
