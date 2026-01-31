#pragma once
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QCoreApplication>
#include <QMetaObject>
#include <QThread>
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QLineEdit>

#include "SplayTree.h"
#include "Account.h"
#include "AccountDAL.h"

class DemoWindow : public QWidget {
    Q_OBJECT
private slots:
    void restartTree();
    void closeWindow();


public:
    DemoWindow(AccountDAL* dal, QWidget* parent = nullptr);
    ~DemoWindow() {}

    void displayTree(SplayTree<Account>::NodeType*);
    void triggerSplay(int id);

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    AccountDAL& DAL;
    SplayTree<Account> demoTree;
    QLineEdit* splayInput;

    void updateTreeDisplay();
    void displayNode(SplayTree<Account>::NodeType* node, int x, int y, int offset);
    
    //void updateNodePosition(QGraphicsTextItem* nodeItem, int level, int position);

};

