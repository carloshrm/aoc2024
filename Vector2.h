struct Vector2
{
    int x;
    int y;
};

Vector2 operator+(const Vector2 &left, const Vector2 &right);

bool operator==(const Vector2 &left, const Vector2 &right);

const Vector2 UP = {0, -1};
const Vector2 DOWN = {0, 1};
const Vector2 LEFT = {-1, 0};
const Vector2 RIGHT = {1, 0};
const Vector2 directions[]{UP, DOWN, LEFT, RIGHT};