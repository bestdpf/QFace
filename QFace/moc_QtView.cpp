/****************************************************************************
** Meta object code from reading C++ file 'QtView.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QtView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    8,    7,    7, 0x05,
      36,    8,    7,    7, 0x05,
      58,    8,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,    7,    7,    7, 0x09,
      90,    7,    7,    7, 0x09,
      99,    8,    7,    7, 0x09,
     117,    8,    7,    7, 0x09,
     135,    8,    7,    7, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_QtView[] = {
    "QtView\0\0angle\0xRotationChanged(int)\0"
    "yRotationChanged(int)\0zRotationChanged(int)\0"
    "OnTimer()\0OnIdle()\0setXRotation(int)\0"
    "setYRotation(int)\0setZRotation(int)\0"
};

void QtView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtView *_t = static_cast<QtView *>(_o);
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->OnTimer(); break;
        case 4: _t->OnIdle(); break;
        case 5: _t->setXRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setYRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setZRotation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtView::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_QtView,
      qt_meta_data_QtView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtView))
        return static_cast<void*>(const_cast< QtView*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int QtView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QtView::xRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtView::yRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtView::zRotationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
