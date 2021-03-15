#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTextStream>
#include <box.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    listOfBoxes = std::vector<std::vector<Box*>>(9);
    for (unsigned long i = 0; i<9; ++i) {
        listOfBoxes.push_back(std::vector<Box*>(9));
        for (int j = 0; j<9; ++j) {
            listOfBoxes[i].push_back(nullptr);
        }
    }

    gameState = GameState::STOPPED;
    selectedBox = nullptr;
    setFixedSize(600, 600);
    ui->setupUi(this);
    foreach (Box *box, findChildren<Box *>()) {
        if (box->objectName().startsWith("n_")) {
            QStringList split = box->objectName().split("_");
            listOfBoxes[split.at(1).toULong()-1][split.at(2).toULong()-1] = box;
            connect(box, SIGNAL(box_clicked(Box*)), this, SLOT(box_clicked(Box*)));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    on_clearButton_clicked();
    gameState = GameState::STARTED;

    QFile data(":/sudoku.txt");
    if (!data.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Sudoku", "Program couldn't file input file!", QMessageBox::Ok);
        return;
    }

    QTextStream in(&data);
    int i = 0;
    int random = (rand() % 100 + 1) * 3;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (i == random) {
            sudoku = line;
            sudokuSolution = in.readLine();
        }
        i++;
    }
    data.close();

    int count = 0;
    for (unsigned long i = 0; i<9; ++i) {
        for (unsigned long j = 0; j<9; ++j) {
            QChar c = sudoku.at(count);
            if (c != '.')
                listOfBoxes[i][j]->assignValue(c);
            count++;
        }
    }
}

void MainWindow::on_resetButton_clicked()
{
    if (gameState != GameState::STARTED) return;
    if (selectedBox != nullptr) {
        selectedBox->highlight(false);
        selectedBox = nullptr;
    }
    for (unsigned long i = 0; i<9; ++i) {
        for (unsigned long j = 0; j<9; ++j) {
            if (listOfBoxes[i][j]->getBoxState() != BoxState::COMPUTER)
                listOfBoxes[i][j]->setText("");
        }
    }
}

void MainWindow::on_checkButton_clicked()
{
    if (gameState != GameState::STARTED) return;
    if (selectedBox != nullptr) {
        selectedBox->highlight(false);
        selectedBox = nullptr;
    }
    int count = 0;
    bool finished = true;
    for (unsigned long i = 0; i<9; ++i) {
        for (unsigned long j = 0; j<9; ++j) {
            QChar c = sudokuSolution.at(count);
            Box *box = listOfBoxes[i][j];
            if (c != box->text()) {
                box->wrongBox();
                finished = false;
            } else {
                box->assignValue(c);
            }
            count++;
        }
    }
    if (finished) {
        gameState = GameState::STOPPED;
        QMessageBox::information(this, "Sudoku", "Congratulations! You finished the game!", QMessageBox::Ok);
    }
}

void MainWindow::on_clearButton_clicked()
{
    gameState = GameState::STOPPED;
    if (selectedBox != nullptr) {
        selectedBox->highlight(false);
        selectedBox = nullptr;
    }
    for (unsigned long i = 0; i<9; ++i)
        for (unsigned long j = 0; j<9; ++j)
            listOfBoxes[i][j]->resetBox();
}

void MainWindow::on_solutionButton_clicked()
{
    if (gameState != GameState::STARTED) return;
    on_clearButton_clicked();
    int count = 0;
    for (unsigned long i = 0; i<9; ++i) {
        for (unsigned long j = 0; j<9; ++j) {
            listOfBoxes[i][j]->assignValue(sudokuSolution.at(count));
            count++;
        }
    }
}

void MainWindow::box_clicked(Box *object)
{
    if (gameState != GameState::STARTED || object->getBoxState() == BoxState::COMPUTER) return;
    if (selectedBox == object) {
        selectedBox->highlight(false);
        selectedBox = nullptr;
    } else {
        if (selectedBox != nullptr)
            selectedBox->highlight(false);
        selectedBox = object;
        selectedBox->highlight(true);
    }

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (selectedBox == nullptr) return;

    if (selectedBox->getBoxState() == BoxState::ERROR)
        selectedBox->resetBox();

    if (event->key() == Qt::Key_1) {
        selectedBox->setText("1");
    } else if (event->key() == Qt::Key_2) {
        selectedBox->setText("2");
    } else if (event->key() == Qt::Key_3) {
        selectedBox->setText("3");
    } else if (event->key() == Qt::Key_4) {
        selectedBox->setText("4");
    } else if (event->key() == Qt::Key_5) {
        selectedBox->setText("5");
    } else if (event->key() == Qt::Key_6) {
        selectedBox->setText("6");
    } else if (event->key() == Qt::Key_7) {
        selectedBox->setText("7");
    } else if (event->key() == Qt::Key_8) {
        selectedBox->setText("8");
    } else if (event->key() == Qt::Key_9) {
        selectedBox->setText("9");
    } else if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
        selectedBox->setText("");
    }
}
