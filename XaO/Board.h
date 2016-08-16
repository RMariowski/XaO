#pragma once

class Board
{
public:
    enum Field
    {
        FIELD_EMPTY,
        FIELD_CROSS,
        FIELD_CIRCLE,
        FIELD_COUNT
    };

public:
    void clearFields();

    void update();

    void draw();

    void checkWinConditions();

    bool isFieldEmpty(int x, int y) const;

    bool isFieldCross(int x, int y) const;

    bool isFieldCircle(int x, int y) const;

    void setFieldToCross(int x, int y);

    void setFieldToCircle(int x, int y);

private:
    void playerMove(int x, int y);

    void drawLines();

    void drawMarks();

private:
    Field _fields[3][3];
};