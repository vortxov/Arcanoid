#include "StrongBrick.h"

StrongBrick::StrongBrick() {
    hitPoints_ = 3;
}

void StrongBrick::hit() {
    Block::hit();
    // �������������� ������ ��� �����
}

bool StrongBrick::shouldBallBounce() const {
    return true;
}