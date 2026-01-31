#include "DemoWindow.h"

DemoWindow::DemoWindow(AccountDAL* dal, QWidget* parent)
    : QWidget(parent), scene(new QGraphicsScene(this)), view(new QGraphicsView(scene, this)), DAL(*dal) {

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);

    view->setScene(scene);
    view->show();

    
    // Input Field
    QLineEdit* inputField = new QLineEdit(this);
    inputField->setPlaceholderText("Enter Customer ID");
    layout->addWidget(inputField);

    // Buttons
    QPushButton* triggerButton = new QPushButton("Trigger Splay", this);
    QPushButton* restartButton = new QPushButton("Restart Tree", this);
    QPushButton* closeButton = new QPushButton("Close Window", this);

    layout->addWidget(triggerButton);
    layout->addWidget(restartButton);
    layout->addWidget(closeButton);

    connect(triggerButton, &QPushButton::clicked, [this, inputField]() {
        bool ok;
        int id = inputField->text().toInt(&ok);
        if (ok) {
            triggerSplay(id);
        }
        else {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid numeric Customer ID.");
        }
        });

    connect(restartButton, &QPushButton::clicked, this, &DemoWindow::restartTree);
    connect(closeButton, &QPushButton::clicked, this, &DemoWindow::closeWindow);

    scene->setSceneRect(-1000, -1000, 2000, 2000);
    setLayout(layout);
    setWindowTitle("Splay Tree Demo");
    resize(1800, 700);

    demoTree = DAL.getDemoAccounts();
    qDebug() << "Loaded demo accounts:" << demoTree.nodeCount();

    demoTree.setOnRotationCallback([this](SplayTree<Account>::NodeType* root) {
        QMetaObject::invokeMethod(this, [this, root]() {
            displayTree(root);
            }, Qt::QueuedConnection);

        QThread::msleep(1000);
        QCoreApplication::processEvents();
        });

    displayTree(demoTree.getRoot());
}

void DemoWindow::displayTree(SplayTree<Account>::NodeType* root) {
    scene->clear();
    qDebug() << "Displaying tree with" << demoTree.nodeCount() << "accounts";
    displayNode(root, 0, 0, 150);
    scene->update();
    view->viewport()->update();
}

void DemoWindow::displayNode(SplayTree<Account>::NodeType* node, int x, int y, int offset) {
    if (!node) return;

    QString text = QString::number(node->data.getCustomerID());
    QGraphicsTextItem* item = scene->addText(text);
    item->setPos(x, y);

    if (node->left) {
        scene->addLine(x + 10, y + 10, x - offset + 10, y + 50);
        displayNode(node->left, x - offset, y + 60, offset /1.2);
    }

    if (node->right) {
        scene->addLine(x + 10, y + 10, x + offset + 10, y + 50);
        displayNode(node->right, x + offset, y + 60, offset / 1.2);
    }
}

void DemoWindow::triggerSplay(int id) {
    Account targetAccount(id);
    auto foundNode = demoTree.search(targetAccount);
    if (foundNode) {
        updateTreeDisplay();
    }
}

void DemoWindow::updateTreeDisplay() {
    displayTree(demoTree.getRoot());
}

//  New slot: Restart the tree completely
void DemoWindow::restartTree() {
    demoTree = DAL.getDemoAccounts();
    qDebug() << "Tree restarted with" << demoTree.nodeCount() << "accounts.";
    displayTree(demoTree.getRoot());
}

//  New slot: Close the window
void DemoWindow::closeWindow() {
    this->close();
}
