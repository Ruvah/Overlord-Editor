/********************************************************************************
** Form generated from reading UI file 'OverlordEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OVERLORDEDITOR_H
#define UI_OVERLORDEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OverlordEditorClass
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionSave_Scene;
    QAction *actionSaveProject;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *DockLeft;
    QWidget *dockwidgetcontents;
    QDockWidget *DockRight;
    QWidget *dockWidgetContents_2;
    QTextEdit *textEdit;
    QDockWidget *dockBottom;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *OverlordEditorClass)
    {
        if (OverlordEditorClass->objectName().isEmpty())
            OverlordEditorClass->setObjectName(QStringLiteral("OverlordEditorClass"));
        OverlordEditorClass->resize(1482, 911);
        OverlordEditorClass->setDockNestingEnabled(true);
        OverlordEditorClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        actionNew_Project = new QAction(OverlordEditorClass);
        actionNew_Project->setObjectName(QStringLiteral("actionNew_Project"));
        actionOpen_Project = new QAction(OverlordEditorClass);
        actionOpen_Project->setObjectName(QStringLiteral("actionOpen_Project"));
        actionSave_Scene = new QAction(OverlordEditorClass);
        actionSave_Scene->setObjectName(QStringLiteral("actionSave_Scene"));
        actionSaveProject = new QAction(OverlordEditorClass);
        actionSaveProject->setObjectName(QStringLiteral("actionSaveProject"));
        centralWidget = new QWidget(OverlordEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(false);
        OverlordEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OverlordEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1482, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        OverlordEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OverlordEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OverlordEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OverlordEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OverlordEditorClass->setStatusBar(statusBar);
        DockLeft = new QDockWidget(OverlordEditorClass);
        DockLeft->setObjectName(QStringLiteral("DockLeft"));
        DockLeft->setBaseSize(QSize(400, 0));
        DockLeft->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockwidgetcontents = new QWidget();
        dockwidgetcontents->setObjectName(QStringLiteral("dockwidgetcontents"));
        dockwidgetcontents->setBaseSize(QSize(900, 0));
        DockLeft->setWidget(dockwidgetcontents);
        OverlordEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), DockLeft);
        DockRight = new QDockWidget(OverlordEditorClass);
        DockRight->setObjectName(QStringLiteral("DockRight"));
        DockRight->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        textEdit = new QTextEdit(dockWidgetContents_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(180, 20, 121, 31));
        DockRight->setWidget(dockWidgetContents_2);
        OverlordEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), DockRight);
        dockBottom = new QDockWidget(OverlordEditorClass);
        dockBottom->setObjectName(QStringLiteral("dockBottom"));
        dockBottom->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockBottom->setWidget(dockWidgetContents);
        OverlordEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockBottom);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Scene);
        menuFile->addAction(actionSaveProject);

        retranslateUi(OverlordEditorClass);

        QMetaObject::connectSlotsByName(OverlordEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *OverlordEditorClass)
    {
        OverlordEditorClass->setWindowTitle(QApplication::translate("OverlordEditorClass", "OverlordEditor", nullptr));
        actionNew_Project->setText(QApplication::translate("OverlordEditorClass", "New Project", nullptr));
        actionOpen_Project->setText(QApplication::translate("OverlordEditorClass", "Open Project", nullptr));
        actionSave_Scene->setText(QApplication::translate("OverlordEditorClass", "Save Scene", nullptr));
        actionSaveProject->setText(QApplication::translate("OverlordEditorClass", "Save Project", nullptr));
        menuFile->setTitle(QApplication::translate("OverlordEditorClass", "File", nullptr));
        DockLeft->setWindowTitle(QApplication::translate("OverlordEditorClass", "Hierarchy", nullptr));
        DockRight->setWindowTitle(QApplication::translate("OverlordEditorClass", "Inspector", nullptr));
        dockBottom->setWindowTitle(QApplication::translate("OverlordEditorClass", "File Explorer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OverlordEditorClass: public Ui_OverlordEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OVERLORDEDITOR_H
