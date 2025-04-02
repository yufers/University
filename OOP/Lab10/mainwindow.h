#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

template <typename T>
class SmartPtr {
    T* ptr;
public:
    explicit SmartPtr(T* p = nullptr) : ptr(p) {}
    ~SmartPtr() { delete ptr; }

    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;

    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    SmartPtr& operator+=(const T& value) {
        if (ptr) {
            *ptr += value;
        }
        return *this;
    }

    T* operator->() const { return ptr; }
    T& operator*() const { return *ptr; }
    explicit operator bool() const { return ptr != nullptr; }
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void increaseCounter1();
    void increaseCounter2();
    void increaseCounter3();
    void increaseCounter4();
    void resetCounters();

private:
    Ui::MainWindow *ui;
    SmartPtr<int> counter1, counter2, counter3, counter4;

};

#endif // MAINWINDOW_H
