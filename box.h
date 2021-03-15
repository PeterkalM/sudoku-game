#ifndef NUMBERLABEL_H
#define NUMBERLABEL_H


#include <QLabel>
#include <QWidget>
#include <Qt>

enum BoxState {
    COMPUTER,
    USER,
    ERROR
};

class Box : public QLabel
{
    Q_OBJECT
public:
    explicit Box(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~Box();

    void highlight(bool boolean);
    inline BoxState getBoxState() { return boxState; }
    void resetBox();
    void assignValue(QString value);
    void wrongBox();

signals:
    void box_clicked(Box *object);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    BoxState boxState;
};

#endif // NUMBERLABEL_H
