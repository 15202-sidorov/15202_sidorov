/****************************************************************************
** Meta object code from reading C++ file 'feild_widget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "feild_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'feild_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FeildWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      24,   12,   12,   12, 0x0a,
      36,   12,   12,   12, 0x0a,
      47,   12,   12,   12, 0x0a,
      71,   55,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FeildWidget[] = {
    "FeildWidget\0\0StepOnce()\0StartPlay()\0"
    "StopPlay()\0Clear()\0length_,height_\0"
    "changeSize(int,int)\0"
};

void FeildWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FeildWidget *_t = static_cast<FeildWidget *>(_o);
        switch (_id) {
        case 0: _t->StepOnce(); break;
        case 1: _t->StartPlay(); break;
        case 2: _t->StopPlay(); break;
        case 3: _t->Clear(); break;
        case 4: _t->changeSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FeildWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FeildWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FeildWidget,
      qt_meta_data_FeildWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FeildWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FeildWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FeildWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FeildWidget))
        return static_cast<void*>(const_cast< FeildWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FeildWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
