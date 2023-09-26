# Clock

## 项目名称

Clock

## 项目实现功能

钟表的实现

## 项目文件组成

### 头文件

* `clock.h`
抗锯齿图形处理函数、主体函数的头文件

### 源文件

* `clock_graphics.cpp`
抗锯齿图形处理函数的实现

* `clock_main.cpp`
主体函数的实现

## 项目技术细节

### 线段有符号距离场的计算

```cpp
double calculate_line_SDF(int x, int y, int x1, int y1, int x2, int y2, int d)
{
    /* Preprocessing operations */
    int dx = x2 - x1, dy = y2 - y1, px = x - x1, py = y - y1, qx = x - x2, qy = y - y2;

    /* Calculate the length of the segment */
    double length = sqrt(dx * dx + dy * dy);

    /* Calculate the projection length from a point to the extension of the segment */
    double projection = (px * dx + py * dy) / length;

    /* Calculate the signed distance field of a straight line */
    if (projection < 0) { // Return the distance from the point to the starting point if the projection is before the endpoints
        return sqrt(px * px + py * py) - d;
    }
    else if (projection > length) { // Return the distance from the point to the ending point if the projection is after the endpoints
        return sqrt(qx * qx + qy * qy) - d;
    }
    else { // Return the perpendicular distance from a point to a line segment
        return fabs(px * dy - py * dx) / length - d;
    }
}
```

### SDF直线的绘制

```cpp
void line_SDF(int x1, int y1, int x2, int y2, int d, COLORREF color)
{
    /* Determine traversal boundaries */
    int minX = min(x1, x2) - d;
    int maxX = max(x1, x2) + d;
    int minY = min(y1, y2) - d;
    int maxY = max(y1, y2) + d;

    /* Draw a line using SDF algorithm */
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            /* Calculate the signed distance field of a straight line */
            double distance = calculate_line_SDF(i, j, x1, y1, x2, y2, d) + 1;
            if (distance < 2) {
                /* Alpha Blending */
                double alpha = 0.5 * distance;
                if (alpha < 0)
                    alpha = 0;
                if (alpha > 1)
                    alpha = 1;

                /* Put pixel */
                COLORREF target_color = getpixel(i, j);
                putpixel(i, j, RGB(GetRValue(color) * (1 - alpha) + GetRValue(target_color) * alpha, GetGValue(color) * (1 - alpha) + GetGValue(target_color) * alpha, GetBValue(color) * (1 - alpha) + GetBValue(target_color) * alpha));
            }
        }
    }
}
```

### SDF圆形的绘制

```cpp
void circle_SDF(int x, int y, int r, int d, COLORREF color)
{
    /* Determine traversal boundaries */
    int minX = x - r - d;
    int maxX = x + r + d;
    int minY = y - r - d;
    int maxY = y + r + d;

    /* Draw a circle using SDF algorithm */
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            /* Calculate the signed distance field of a circle */
            double distance = fabs(sqrt((i - x) * (i - x) + (j - y) * (j - y)) - r) - d + 1;
            if (distance < 2) {
                /* Alpha Blending */
                double alpha = 0.5 * distance;
                if (alpha < 0)
                    alpha = 0;
                if (alpha > 1)
                    alpha = 1;

                /* Put pixel */
                COLORREF target_color = getpixel(i, j);
                putpixel(i, j, RGB(GetRValue(color) * (1 - alpha) + GetRValue(target_color) * alpha, GetGValue(color) * (1 - alpha) + GetGValue(target_color) * alpha, GetBValue(color) * (1 - alpha) + GetBValue(target_color) * alpha));
            }
        }
    }
}
```

### 渐变色的绘制

渐变色的绘制方法：

* 线性插值渐变（Linear Interpolation Gradient）：使用线性插值来计算渐变过程中的颜色，适用于各种简单的颜色变化效果。

* 径向渐变（Radial Gradient）：从一个中心点向外辐射，通常以一个颜色为中心，逐渐过渡到另一个颜色，适合创建类似太阳光晕的效果。

* 角度渐变（Angular Gradient）：基于角度的渐变，可以在某个角度上开始和结束，适用于创建环形渐变等效果。

* 锥形渐变（Conical Gradient）：类似于一个锥形，颜色按照角度进行渐变，适用于创建光线照射的效果。

* 分段渐变（Gradient Stops）：在渐变过程中定义多个颜色点，实现更复杂的颜色变化，适用于需要丰富颜色变化的场景。

* 纹理映射（Texture Mapping）：将图像或纹理应用到对象上，用于创建复杂的材质效果，适用于模拟表面纹理。

* 渐变遮罩（Gradient Masks）：在图像或对象的部分区域应用渐变，实现局部的颜色变化，用于创建焦点或视觉效果。

* 噪声渐变（Perlin Noise Gradient）：使用噪声函数生成颜色渐变，创造出有机、纹理丰富的效果，适合营造自然风格。

* 二次曲线渐变（Quadratic Gradient）：基于二次曲线方程的渐变，可创建流线型或弧形的颜色变化，适用于独特的渐变形状。

本程序使用线性插值渐变方法进行渐变色的绘制。

```cpp
for (int step = 0; step < consoleHeight; step++) {
    double t = double(step) / consoleHeight;
    int r = GetRValue(start) + int((GetRValue(end) - GetRValue(start)) * t);
    int g = GetGValue(start) + int((GetGValue(end) - GetGValue(start)) * t);
    int b = GetBValue(start) + int((GetBValue(end) - GetBValue(start)) * t);
    setlinecolor(RGB(r, g, b));
    line(0, step, consoleWidth - 1, step);
}
```

### 双缓冲区绘制方法

```cpp
IMAGE* backBuffer = new(nothrow) IMAGE(consoleWidth, consoleHeight);
if (backBuffer == NULL)
    return -1;
getimage(backBuffer, -consoleWidth / 2, -consoleHeight / 2, consoleWidth, consoleHeight);
SetWorkingImage(backBuffer);
setorigin(consoleWidth / 2, consoleHeight / 2);
...
setorigin(0, 0);
SetWorkingImage(NULL);
putimage(-consoleWidth / 2, -consoleHeight / 2, backBuffer);
delete backBuffer;
```

## 集成开发环境

* Microsoft Visual Studio

## 编译运行环境

* 本项目适用于x86和x64架构

## 库依赖

* `EasyX`

  * ```cpp
    #include <graphics.h>
    ```

## 相关资料

* [EasyX Documentation](https://docs.easyx.cn/)

## 文档更新日期

2023年9月27日