#ifndef CAT_H
#define CAT_H
#include <QThread>
#include <QDebug>

class Cat : public QThread {
    public:
        Cat();
        void run();
        QString name;
};
#endif // CAT_H
