/****************************************************************************
** Meta object code from reading C++ file 'openfile.h'
**
** Created: Tue Jan 22 14:31:30 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "openfile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'openfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OpenFileClass[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      37,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   14,   14,   14, 0x08,
      71,   14,   14,   14, 0x08,
      92,   89,   14,   14, 0x08,
     110,   14,   14,   14, 0x08,
     121,   14,   14,   14, 0x08,
     141,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OpenFileClass[] = {
    "OpenFileClass\0\0siSetNewText(QString)\0"
    "activatedOpenFile()\0slSetNewTex()\0"
    "setCodec(QString)\0in\0maskTextEdit(int)\0"
    "openFile()\0setDefaultSetting()\0exec()\0"
};

void OpenFileClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OpenFileClass *_t = static_cast<OpenFileClass *>(_o);
        switch (_id) {
        case 0: _t->siSetNewText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->activatedOpenFile(); break;
        case 2: _t->slSetNewTex(); break;
        case 3: _t->setCodec((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->maskTextEdit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->openFile(); break;
        case 6: _t->setDefaultSetting(); break;
        case 7: _t->exec(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData OpenFileClass::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OpenFileClass::staticMetaObject = {
    { &OpenFile::staticMetaObject, qt_meta_stringdata_OpenFileClass,
      qt_meta_data_OpenFileClass, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OpenFileClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OpenFileClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OpenFileClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OpenFileClass))
        return static_cast<void*>(const_cast< OpenFileClass*>(this));
    if (!strcmp(_clname, "OpenFile/RigimeFile/EasyWork/Plagin/1.0.0"))
        return static_cast< OpenFile*>(const_cast< OpenFileClass*>(this));
    return OpenFile::qt_metacast(_clname);
}

int OpenFileClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OpenFile::qt_metacall(_c, _id, _a);
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
void OpenFileClass::siSetNewText(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OpenFileClass::activatedOpenFile()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
