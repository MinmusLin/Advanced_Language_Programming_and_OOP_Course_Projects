/****************************************************************
 * Project Name:  Gluttonous_Snake
 * File Name:     gluttonous_snake_snake.cpp
 * File Function: Snake类的实现
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/9/30
 ****************************************************************/

#include "gluttonous_snake.h"

using namespace std;

/*
 * Function Name:    deleteSnake
 * Function:         Delete snake
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Snake::deleteSnake(void)
{
    while (head != nullptr) {
        SnakeSegment* temp = head;
        head = head->nextSegment;
        delete temp;
    }
    tail = nullptr;
}

/*
 * Function Name:    addSegment
 * Function:         Add a snake segment
 * Input Parameters: Direction direction
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Snake::addSegment(Direction direction)
{
    /* Calculate the new X and Y coordinates for the new segment based on the given direction */
    int newX = tail->coordinate.X;
    int newY = tail->coordinate.Y;
    switch (direction) {
        case Up:
            newY++;
            break;
        case Down:
            newY--;
            break;
        case Left:
            newX++;
            break;
        case Right:
            newX--;
            break;
        default:
            exit(-1);
    }

    /* Create a new SnakeSegment and set its properties */
    SnakeSegment* newSegment = new SnakeSegment;
    newSegment->coordinate.X = newX;
    newSegment->coordinate.Y = newY;
    newSegment->direction = direction;
    newSegment->nextSegment = nullptr;

    /* Update the previous tail's nextSegment pointer to point to the new segment */
    tail->nextSegment = newSegment;

    /* Update the tail pointer to the new segment */
    tail = newSegment;

    /* Update the game map to indicate the presence of the new segment */
    map[tail->coordinate.Y][tail->coordinate.X] = SnakeBody;
    print_grid_status(tail->coordinate.Y, tail->coordinate.X, SnakeBody, snakeCategory, this->getSnakeDirection());

    /* Update data */
    length++;
}

/*
 * Function Name:    deleteSegment
 * Function:         Delete the last element of a linked list
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Snake::deleteSegment(void)
{
    /* Check if it is minimum length */
    if (length <= 1)
        return;

    /* Update snake tail grid state */
    map[tail->coordinate.Y][tail->coordinate.X] = GridBlank;
    print_grid_status(tail->coordinate.Y, tail->coordinate.X, GridBlank, snakeCategory, this->getSnakeDirection());

    /* Delete the last element of a linked list */
    SnakeSegment* current = head;
    SnakeSegment* previous = nullptr;
    while (current->nextSegment != nullptr) {
        previous = current;
        current = current->nextSegment;
    }
    delete current;
    current = nullptr;
    if (previous != nullptr) {
        previous->nextSegment = nullptr;
        tail = previous;
    }

    /* Update length */
    length--;
}

/*
 * Function Name:    findEmptySpace
 * Function:         Find continuous empty space
 * Input Parameters: COORD& coord
 *                   Direction& direction
 *                   bool is_multiplayer
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Snake::findEmptySpace(COORD& coord, Direction& direction, bool is_multiplayer)
{
    /* Find continuous empty space horizontally */
    if (!is_multiplayer || (is_multiplayer && snakeCategory == SnakeB))
        for (int i = 1; i < gridRow - 1; i++)
            for (int j = 1; j < gridCol - snakeInitialLength; j++) {
                bool isEmptySpace = true;
                for (int k = 0; k < snakeInitialLength; k++)
                    if (map[i][j + k] != GridBlank) {
                        isEmptySpace = false;
                        break;
                    }
                if (isEmptySpace) {
                    coord.Y = i;
                    coord.X = j + snakeInitialLength - 1;
                    direction = Right;
                    return true;
                }
            }

    /* Find continuous empty space vertically */
    if (!is_multiplayer || (is_multiplayer && snakeCategory == SnakeA))
        for (int i = 1; i < gridRow - snakeInitialLength; i++)
            for (int j = 1; j < gridCol - 1; j++) {
                bool isEmptySpace = true;
                for (int k = 0; k < snakeInitialLength; k++)
                    if (map[i + k][j] != GridBlank) {
                        isEmptySpace = false;
                        break;
                    }
                if (isEmptySpace) {
                    coord.Y = i + snakeInitialLength - 1;
                    coord.X = j;
                    direction = Down;
                    return true;
                }
            }
    return false;
}

/*
 * Function Name:    findClosestCoordinate
 * Function:         Find closest target coordinate
 * Input Parameters: void
 * Return Value:     point
 * Notes:            Class external implementation of member functions
 */
Point Snake::findClosestCoordinate(void)
{
    int headRow = head->coordinate.Y, headCol = head->coordinate.X;
    for (int distance = 1; distance <= max(gridRow, gridCol) - 3; distance++)
        for (int r = max((headRow - distance), 1); r <= min((headRow + distance), (gridRow - 2)); r++)
            for (int c = max((headCol - distance), 1); c <= min((headCol + distance), (gridCol - 2)); c++)
                if ((r == headRow - distance || r == headRow + distance || c == headCol - distance || c == headCol + distance) && (map[r][c] == GoodFood || map[r][c] == GreatFood))
                    return { r, c };
    return { INVALID_ROW, INVALID_COLUMN };
}

/*
 * Function Name:    findNextStep
 * Function:         Use BFS to find next step
 * Input Parameters: int map[][gridCol]
 *                   int startRow
 *                   int startCol
 *                   int targetRow
 *                   int targetCol
 * Return Value:     next point
 * Notes:            Class external implementation of member functions
 */
Point Snake::findNextStep(int map[][gridCol], int startRow, int startCol, int targetRow, int targetCol)
{
    /* Define movement directions: up, down, left, right */
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    /* Create a boolean matrix to track visited cells */
    bool visited[gridRow][gridCol] = { false };

    /* Create a matrix to store the parent of each cell in the path */
    Point parent[gridRow][gridCol];

    /* Mark the starting cell as visited */
    visited[startRow][startCol] = true;
    parent[startRow][startCol] = { INVALID_ROW, INVALID_COLUMN };

    /* Initialize a queue for BFS traversal */
    Point queue[gridRow * gridCol];
    int front = 0, rear = 1;
    queue[0] = { startRow, startCol };

    /* Perform BFS to find the path to the target */
    while (front < rear) {
        /* Get the current cell from the queue */
        Point current = queue[front++];

        /* Check if we have reached the target cell */
        if (current.row == targetRow && current.col == targetCol) {
            /* Reconstruct the path from the target to the start */
            Point path[gridRow * gridCol], temp = { targetRow, targetCol };
            int pathLength = 0;

            /* Traverse the path in reverse order and store it */
            while (temp.row != startRow || temp.col != startCol) {
                path[pathLength++] = temp;
                temp = parent[temp.row][temp.col];
            }

            /* Return the next step in the path */
            return { path[pathLength - 1].row, path[pathLength - 1].col };
        }

        /* Explore adjacent cells in all four directions */
        for (int dir = 0; dir < 4; dir++) {
            /* Save new row and new column */
            int newRow = current.row + dx[dir], newCol = current.col + dy[dir];

            /* Check if the new cell is within bounds, is open, and hasn't been visited */
            if (newRow >= 0 && newRow < gridRow && newCol >= 0 && newCol < gridCol && map[newRow][newCol] == 0 && !visited[newRow][newCol]) {
                /* Mark the new cell as visited and set its parent */
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = current;

                /* Add the new cell to the queue for further exploration */
                queue[rear++] = { newRow, newCol };
            }
        }
    }

    /* If no path is found, return an invalid point */
    return { INVALID_ROW, INVALID_COLUMN };
}

/*
 * Function Name:    ~Snake
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
Snake::~Snake()
{
    if (head != nullptr)
        deleteSnake();
}

/*
 * Function Name:    generateSnake
 * Function:         Generate the initial snake
 * Input Parameters: bool is_multiplayer
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Snake::generateSnake(bool is_multiplayer)
{
    /* Find space to generate the initial snake */
    COORD start;
    Direction direction;
    if (!findEmptySpace(start, direction, is_multiplayer))
        return false;

    /* Generate the snake head */
    head = new SnakeSegment;
    head->coordinate.X = start.X;
    head->coordinate.Y = start.Y;
    head->direction = direction;
    head->nextSegment = nullptr;
    tail = head;
    map[head->coordinate.Y][head->coordinate.X] = SnakeHead;
    print_grid_status(head->coordinate.Y, head->coordinate.X, SnakeHead, snakeCategory, this->getSnakeDirection());

    /* Increase the length of the snake */
    for (int i = 1; i < snakeInitialLength; i++)
        addSegment(tail->direction);
    return true;
}

/*
 * Function Name:    refreshSnake
 * Function:         Refresh snake
 * Input Parameters: void
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Snake::refreshSnake(void)
{
    deleteSnake();
    length = 1;
    death++;
    score += deathScore;
}

/*
 * Function Name:    changeGridCondition
 * Function:         Change grid condition
 * Input Parameters: GridCondition gridCondition
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Snake::changeGridCondition(GridCondition gridCondition)
{
    SnakeSegment* currentSegment = head;
    while (currentSegment != nullptr) {
        COORD coordinate = currentSegment->coordinate;
        map[coordinate.Y][coordinate.X] = gridCondition;
        print_grid_status(coordinate.Y, coordinate.X, gridCondition);
        currentSegment = currentSegment->nextSegment;
    }
}

/*
 * Function Name:    correct
 * Function:         Correct length and score
 * Input Parameters: int len
 * Return Value:     void
 * Notes:            Class external implementation of member functions
 */
void Snake::correct(int len)
{
    length = len;
}

/*
 * Function Name:    changeDirection
 * Function:         Change snake direction
 * Input Parameters: Direction direction
 * Return Value:     true / false
 * Notes:            Class external implementation of member functions
 */
bool Snake::changeDirection(Direction direction)
{
    /* Update snake head state and snake tail state */
    Direction tailDirection = tail->direction;
    map[head->coordinate.Y][head->coordinate.X] = SnakeBody;
    print_grid_status(head->coordinate.Y, head->coordinate.X, SnakeBody, snakeCategory, this->getSnakeDirection());
    map[tail->coordinate.Y][tail->coordinate.X] = GridBlank;
    print_grid_status(tail->coordinate.Y, tail->coordinate.X, GridBlank, snakeCategory, this->getSnakeDirection());

    /* Calculate new snake head coordinate */
    COORD prevHeadCoord = head->coordinate;
    head->direction = direction;
    switch (direction) {
        case Up:
            head->coordinate.Y--;
            break;
        case Down:
            head->coordinate.Y++;
            break;
        case Left:
            head->coordinate.X--;
            break;
        case Right:
            head->coordinate.X++;
            break;
    }

    /* Traverse the linked list */
    SnakeSegment* currentSegment = head->nextSegment, * previousSegment = head;
    while (currentSegment != nullptr) {
        COORD prevCoord = currentSegment->coordinate;
        Direction prevDirection = currentSegment->direction;
        currentSegment->coordinate = prevHeadCoord;
        currentSegment->direction = prevDirection;
        prevHeadCoord = prevCoord;
        currentSegment = currentSegment->nextSegment;
    }
    GridCondition nextCondition = map[head->coordinate.Y][head->coordinate.X];
    currentSegment = head->nextSegment;
    Direction tempDirection = previousSegment->direction;
    while (currentSegment != nullptr) {
        Direction currentDirection = currentSegment->direction;
        currentSegment->direction = tempDirection;
        tempDirection = currentDirection;
        previousSegment = currentSegment;
        currentSegment = currentSegment->nextSegment;
    }

    /* Update new snake head state */
    map[head->coordinate.Y][head->coordinate.X] = SnakeHead;
    print_grid_status(head->coordinate.Y, head->coordinate.X, SnakeHead, snakeCategory, this->getSnakeDirection());

    /* Update snake head grid state */
    switch (nextCondition) {
        case GridBlank:
            break;
        case GridWall:
        case SnakeHead:
        case SnakeBody:
            return false;
        case GoodFood:
            addSegment(tailDirection);
            score += goodScore;
            (*pGoodFood)--;
            break;
        case BadFood:
            score += badScore;
            (*pBadFood)--;
            break;
        case GridObstacle:
            deleteSegment();
            deleteSegment();
            score += obstacleScore;
            (*pObstacle)--;
            break;
        case GreatFood:
            score += greatScore;
            (*pGreatFood)--;
            break;
        case BoomFood: {
            int len = length / 2;
            for (int i = 0; i < len; i++)
                deleteSegment();
            score += boomScore;
            (*pBoomFood)--;
            break;
        }
        default:
            exit(-1);
    }

    /* Check if the length of the snake is 1 */
    if (length <= 1)
        return false;
    return true;
}

/*
 * Function Name:    getLength
 * Function:         Get length
 * Input Parameters: void
 * Return Value:     length
 * Notes:            Class external implementation of member functions
 */
int Snake::getLength(void)
{
    return length;
}

/*
 * Function Name:    getDeath
 * Function:         Get death count
 * Input Parameters: void
 * Return Value:     death count
 * Notes:            Class external implementation of member functions
 */
int Snake::getDeath(void)
{
    return death;
}

/*
 * Function Name:    getSnakeDirection
 * Function:         Get snake head direction
 * Input Parameters: void
 * Return Value:     direction
 * Notes:            Class external implementation of member functions
 */
Direction Snake::getSnakeDirection(void)
{
    return head->direction;
}

/*
 * Function Name:    BFS
 * Function:         Breadth-First Search
 * Input Parameters: void
 * Return Value:     direction
 * Notes:            Class external implementation of member functions
 */
Direction Snake::BFS(void)
{
    /* Find closest target coordinate */
    Direction currentDirection = head->direction;
    Point target = findClosestCoordinate();
    if (target.row == INVALID_ROW && target.col == INVALID_COLUMN)
        return currentDirection;

    /* Convert an array of GridCondition types into an array of integers */
    int mat[gridRow][gridCol];
    for (int i = 0; i < gridRow; i++)
        for (int j = 0; j < gridCol; j++)
            mat[i][j] = (map[i][j] == GridWall || map[i][j] == SnakeHead || map[i][j] == SnakeBody);
    mat[target.row][target.col] = 0;
    mat[head->coordinate.Y][head->coordinate.X] = 0;

    /* Use BFS to find next step */
    Point next = findNextStep(mat, head->coordinate.Y, head->coordinate.X, target.row, target.col);

    /* If the path is not found return current direction */
    if (next.row == INVALID_ROW && next.col == INVALID_COLUMN)
        return currentDirection;

    /* Return the direction of the next move */
    if (next.row < head->coordinate.Y && currentDirection != Down)
        return Up;
    else if (next.row > head->coordinate.Y && currentDirection != Up)
        return Down;
    else if (next.col < head->coordinate.X && currentDirection != Right)
        return Left;
    else if (next.col > head->coordinate.X && currentDirection != Left)
        return Right;
    else
        return currentDirection;
}