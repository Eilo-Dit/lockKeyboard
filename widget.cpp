#include "widget.h"
#include "ui_widget.h"

HHOOK keyboardHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    //qDebug()<<nCode<<" "<<wParam<<Qt::endl;
    if (nCode >= 0)
    {
        return 1; // 禁用按键
    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void DisableKeyboard()
{
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (!keyboardHook)
    {
        qDebug()<< "Failed to set keyboard hook." << Qt::endl;
    }
}

bool EnableKeyboard()
{
    if (UnhookWindowsHookEx(keyboardHook))
    {
        return true;
    }
    return false;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    DisableKeyboard();
}

void Widget::on_pushButton_clicked()
{
    EnableKeyboard();
    QApplication::quit();
}

