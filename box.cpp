#include "box.h"
#include <QLabel>
#include <QRegularExpression>

Box::Box(QWidget* parent, Qt::WindowFlags f) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setFont(QFont("Cantarell", 20, QFont::Bold, false));
    resetBox();
}

Box::~Box() {}

void Box::mousePressEvent(QMouseEvent* event) {
    emit box_clicked(this);
}

void Box::highlight(bool boolean)
{
    if (boolean) {
        setStyleSheet(styleSheet().replace(QRegularExpression("background-color.*?;"), "background-color: rgba(65, 65, 65, 0.2);"));
    } else {
        setStyleSheet(styleSheet().replace(QRegularExpression("background-color.*?;"), "background-color: rgba(65, 65, 65, 0);"));
    }
}

void Box::resetBox()
{
    setText("");
    boxState = BoxState::USER;
    setStyleSheet(styleSheet().replace(QRegularExpression(" color.*?;"), " color: rgb(65, 93, 148);"));
}

void Box::assignValue(QString value)
{
    setText(value);
    boxState = BoxState::COMPUTER;
    setStyleSheet(styleSheet().replace(QRegularExpression(" color.*?;"), " color: black;"));
}

void Box::wrongBox()
{
    boxState = BoxState::ERROR;
    setStyleSheet(styleSheet().replace(QRegularExpression(" color.*?;"), " color: red;"));
}
