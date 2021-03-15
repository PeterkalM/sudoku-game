#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <vector>
#include <box.h>

enum GameState {
    STOPPED,
    STARTED
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_startButton_clicked();
    void on_resetButton_clicked();
    void on_checkButton_clicked();
    void on_clearButton_clicked();
    void on_solutionButton_clicked();

    void box_clicked(Box *object);

private:
    Ui::MainWindow *ui;

    Box *selectedBox;
    GameState gameState;
    std::vector<std::vector<Box*>> listOfBoxes;

    QString sudoku;
    QString sudokuSolution;
};

#endif // MAINWINDOW_H
