/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[14];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "slot_aboutMenu"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "slot_reglesMenu"
QT_MOC_LITERAL(4, 43, 12), // "slot_newGame"
QT_MOC_LITERAL(5, 56, 20), // "slot_meilleursNormal"
QT_MOC_LITERAL(6, 77, 1), // "n"
QT_MOC_LITERAL(7, 79, 23), // "slot_meilleursDifficile"
QT_MOC_LITERAL(8, 103, 21), // "slot_meilleursExtreme"
QT_MOC_LITERAL(9, 125, 18), // "slot_nombreVoiture"
QT_MOC_LITERAL(10, 144, 24), // "slot_vitesseEntrainement"
QT_MOC_LITERAL(11, 169, 9), // "slot_skin"
QT_MOC_LITERAL(12, 179, 12), // "slot_couleur"
QT_MOC_LITERAL(13, 192, 18) // "slot_commandesMenu"

    },
    "MainWindow\0slot_aboutMenu\0\0slot_reglesMenu\0"
    "slot_newGame\0slot_meilleursNormal\0n\0"
    "slot_meilleursDifficile\0slot_meilleursExtreme\0"
    "slot_nombreVoiture\0slot_vitesseEntrainement\0"
    "slot_skin\0slot_couleur\0slot_commandesMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    1,   87,    2, 0x0a /* Public */,
       5,    0,   90,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   91,    2, 0x0a /* Public */,
       7,    0,   94,    2, 0x2a /* Public | MethodCloned */,
       8,    1,   95,    2, 0x0a /* Public */,
       8,    0,   98,    2, 0x2a /* Public | MethodCloned */,
       9,    0,   99,    2, 0x0a /* Public */,
      10,    0,  100,    2, 0x0a /* Public */,
      11,    0,  101,    2, 0x0a /* Public */,
      12,    0,  102,    2, 0x0a /* Public */,
      13,    0,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_aboutMenu(); break;
        case 1: _t->slot_reglesMenu(); break;
        case 2: _t->slot_newGame(); break;
        case 3: _t->slot_meilleursNormal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_meilleursNormal(); break;
        case 5: _t->slot_meilleursDifficile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slot_meilleursDifficile(); break;
        case 7: _t->slot_meilleursExtreme((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_meilleursExtreme(); break;
        case 9: _t->slot_nombreVoiture(); break;
        case 10: _t->slot_vitesseEntrainement(); break;
        case 11: _t->slot_skin(); break;
        case 12: _t->slot_couleur(); break;
        case 13: _t->slot_commandesMenu(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
