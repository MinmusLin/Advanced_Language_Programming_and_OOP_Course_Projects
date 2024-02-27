# Simulated LED Screen

## 项目名称

Simulated_LED_Screen

## 项目实现功能

模拟LED显示屏

1. 从GB2312对应的简体中文汉字库中读取16*16点阵信息

1. 从GB2312对应的繁体中文汉字库中读取16*16点阵信息

1. 模拟LED显示屏（简体中文）

1. 模拟LED显示屏（繁体中文）

1. 模拟LED显示屏（当前日期和时间）

## 项目文件组成

### 头文件

* `cmd_console_tools.h`
伪图形界面函数工具集的头文件

* `lib_hdc_tools.h`
图形界面绘制函数工具集的头文件

### 源文件

* `cmd_console_tools.cpp`
伪图形界面函数工具集的实现

* `LED_main.cpp`
菜单函数的实现

* `LED_retrieve_bitinfo.cpp`
读取点阵信息函数的实现

* `LED_simulated_screen.cpp`
模拟LED显示屏函数的实现

* `lib_hdc_tools.cpp`
图形界面绘制函数工具集的实现

### 资源文件

* `lib_hdc_tools.lib`
图形界面绘制函数工具集的静态链接库

* `/HZK`
存放GB2312对应的中文汉字库

  * `HZK16.dat`
  GB2312对应的简体中文汉字库

  * `HZK16F.dat`
  GB2312对应的繁体中文汉字库

## 项目技术细节

### 一个双字节编码的字符是否为GB2312编码的确认

```cpp
inline bool is_GB2312(char highByte, char lowByte)
{
    BYTE hb = BYTE(highByte), lb = BYTE(lowByte);
    return (hb >= 0xA1 && hb <= 0xFE && lb >= 0xA1 && lb <= 0xFE);
}
```

### GB2312编码区位码的计算

```
区码 = highByte + 96
位码 = lowByte + 96
```

### GB2312编码内部码的计算

```
高字节内部码 = highByte & 0xFF
低字节内部码 = lowByte & 0xFF
```

### GB2312编码偏移值的计算

```cpp
inline int calculate_offset(char highByte, char lowByte)
{
    return 32 * (94 * (highByte - 1) + lowByte - 1);
}
```

### 显示特效的实现

#### 揭开（自顶部）

```cpp
for (int i = 0; i < row * 16; i++) {
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    Sleep(DELAY_TIME);
}
```

#### 揭开（自底部）

```cpp
for (int i = row * 16 - 1; i >= 0; i--) {
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    Sleep(DELAY_TIME);
}
```

#### 揭开（自左侧）

```cpp
for (int j = 0; j < col * 16; j++) {
    for (int i = 0; i < row * 16; i++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    Sleep(DELAY_TIME);
}
```

#### 揭开（自右侧）

```cpp
for (int j = col * 16 - 1; j >= 0; j--) {
    for (int i = 0; i < row * 16; i++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    Sleep(DELAY_TIME);
}
```

#### 推入（自顶部）

```cpp
for (int k = 0; k < row * 16; k++) {
    for (int i = 0; i < k + 1; i++)
        for (int j = 0; j < col * 16; j++)
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i - k + row * 16 - 1][j] ? RGB(R, G, B) : RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 推入（自底部）

```cpp
for (int k = 0; k < row * 16; k++) {
    for (int i = row * 16 - 1; i >= row * 16 - 1 - k; i--)
        for (int j = 0; j < col * 16; j++)
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i + k - row * 16 + 1][j] ? RGB(R, G, B) : RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 推入（自左侧）

```cpp
for (int k = 0; k < col * 16; k++) {
    for (int i = 0; i < row * 16; i++)
        for (int j = 0; j < k + 1; j++)
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i][j - k + col * 16 - 1] ? RGB(R, G, B) : RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 推入（自右侧）

```cpp
for (int k = 0; k < col * 16; k++) {
    for (int i = 0; i < row * 16; i++)
        for (int j = col * 16 - 1; j >= col * 16 - 1 - k; j--)
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, bitmaps[i][j + k - col * 16 + 1] ? RGB(R, G, B) : RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 擦除（自顶部）

```cpp
for (int i = 0; i < row * 16; i++)
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
for (int i = 0; i < row * 16; i++) {
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 擦除（自底部）

```cpp
for (int i = 0; i < row * 16; i++)
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
for (int i = row * 16 - 1; i >= 0; i--) {
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 擦除（自左侧）

```cpp
for (int i = 0; i < row * 16; i++)
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
for (int j = 0; j < col * 16; j++) {
    for (int i = 0; i < row * 16; i++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 擦除（自右侧）

```cpp
for (int i = 0; i < row * 16; i++)
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
for (int j = col * 16 - 1; j >= 0; j--) {
    for (int i = 0; i < row * 16; i++)
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(12, 12, 12));
    Sleep(DELAY_TIME);
}
```

#### 分割（中央向上下展开）

```cpp
for (int i = row * 8; i >= 0; i--) {
    for (int j = 0; j < col * 16; j++) {
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
        if (bitmaps[row * 16 - i - 1][j])
            hdc_point(j * diameter + diameter / 2, (row * 16 - i - 1) * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    }
    Sleep(DELAY_TIME);
}
```

#### 分割（中央向左右展开）

```cpp
for (int j = col * 8; j >= 0; j--) {
    for (int i = 0; i < row * 16; i++) {
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
        if (bitmaps[i][col * 16 - j - 1])
            hdc_point((col * 16 - j - 1) * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    }
    Sleep(DELAY_TIME);
}
```

#### 分割（上下向中央收缩）

```cpp
for (int i = 0; i < row * 8; i++) {
    for (int j = 0; j < col * 16; j++) {
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
        if (bitmaps[row * 16 - i - 1][j])
            hdc_point(j * diameter + diameter / 2, (row * 16 - i - 1) * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    }
    Sleep(DELAY_TIME);
}
```

#### 分割（左右向中央收缩）

```cpp
for (int j = 0; j < col * 8; j++) {
    for (int i = 0; i < row * 16; i++) {
        if (bitmaps[i][j])
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
        if (bitmaps[i][col * 16 - j - 1])
            hdc_point((col * 16 - j - 1) * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    }
    Sleep(DELAY_TIME);
}
```

#### 随机线条（垂直）

```cpp
int* elements = new(nothrow) int[col * 16];
if (elements == NULL)
    exit(-1);
for (int i = 0; i < col * 16; i++)
    elements[i] = i;
shuffle(elements, col * 16);
for (int j = 0; j < col * 16; j++) {
    for (int i = 0; i < row * 16; i++)
        if (bitmaps[i][elements[j]])
            hdc_point(elements[j] * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    Sleep(DELAY_TIME);
}
delete[] elements;
```

#### 随机线条（水平）

```cpp
int* elements = new(nothrow) int[row * 16];
if (elements == NULL)
    exit(-1);
for (int i = 0; i < row * 16; i++)
    elements[i] = i;
shuffle(elements, row * 16);
for (int i = 0; i < row * 16; i++) {
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[elements[i]][j])
            hdc_point(j * diameter + diameter / 2, elements[i] * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
    Sleep(DELAY_TIME);
}
delete[] elements;
```

#### 溶解

```cpp
int* allPoints = new(nothrow) int[row * col * 256];
if (allPoints == NULL)
    exit(-1);
for (int i = 0; i < row * col * 256; i++)
    allPoints[i] = i;
shuffle(allPoints, row * col * 256);
for (int count = 0; count < row * col * 256; count++) {
    int i = allPoints[count] / (col * 16);
    int j = allPoints[count] % (col * 16);
    if (bitmaps[i][j])
        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
}
delete[] allPoints;
```

#### 随机每点颜色

```cpp
int* allPoints = new(nothrow) int[row * col * 256];
if (allPoints == NULL)
    exit(-1);
for (int i = 0; i < row * col * 256; i++)
    allPoints[i] = i;
shuffle(allPoints, row * col * 256);
for (int count = 0; count < row * col * 256; count++) {
    int i = allPoints[count] / (col * 16);
    int j = allPoints[count] % (col * 16);
    if (bitmaps[i][j])
        hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(rand() % 256, rand() % 256, rand() % 256));
}
delete[] allPoints;
```

#### 随机每字颜色

```cpp
int** allCharacters = new(nothrow) int* [row * col] {0};
if (allCharacters == NULL)
    exit(-1);
for (int i = 0; i < row * col; i++) {
    allCharacters[i] = new(nothrow) int[3] {rand() % 256, rand() % 256, rand() % 256};
    if (allCharacters[i] == NULL)
        exit(-1);
}
for (int i = 0; i < row * 16; i++)
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j]) {
            int index = (i / 16) * col + (j / 16);
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(allCharacters[index][0], allCharacters[index][1], allCharacters[index][2]));
        }
for (int i = 0; i < row * col; i++)
    delete[] allCharacters[i];
delete[] allCharacters;
```

#### 闪烁

```cpp
for (int i = 0; i < row * 16; i++)
    for (int j = 0; j < col * 16; j++)
        if (bitmaps[i][j]) {
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
            Sleep(1);
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(255 - R, 255 - G, 255 - B));
            Sleep(1);
            hdc_point(j * diameter + diameter / 2, i * diameter + diameter / 2 + 16, diameter, RGB(R, G, B));
            Sleep(1);
        }
```

### 当前日期和时间的获取

```cpp
struct tm* tt;
time_t current_time = time(0);
tt = localtime(&current_time);
```

## 集成开发环境

* Microsoft Visual Studio 2022

## 编译运行环境

* 本项目仅适用于x86架构

* Windows控制台主机的旧版控制台运行（取消选项“快速编辑模式”和“插入模式”）

## 相关资料

* GB2312编码：GB2312编码是第一个汉字编码国家标准，由中国国家标准总局1980年发布，1981年5月1日开始使用。GB2312编码共收录汉字6763个，其中一级汉字3755个，二级汉字3008个。同时，GB2312编码收录了包括拉丁字母、希腊字母、日文平假名及片假名字母、俄语西里尔字母在内的682个全角字符。自2017年3月23日起，该标准转化为推荐性标准：GB/T2312-1980，不再强制执行。

  * 分区表示：GB2312编码对所收录字符进行了分区处理，共94个区，每区含有94个位，共8836个码位。这种表示方式也称为区位码。

    * 01-09区收录除汉字外的682个字符。

    * 10-15区为空白区，无收录字符。

    * 16-55区收录3755个一级汉字，按拼音排序。

    * 56-87区收录3008个二级汉字，按部首/笔画排序。

    * 88-94区为空白区，无收录字符。

  * 编码规则：GB2312规定对收录的每个字符采用两个字节表示，第一个字节为“高字节”，对应94个区；第二个字节为“低字节”，对应94个位。区位码范围为0101-9494。区号和位号分别加上0xA0就是GB2312编码。

  * 编码范围：A1A1-FEFE，其中汉字的编码范围为B0A1-F7FE，第一字节编码范围为0xB0-0xF7（对应区号16-87），第二字节编码范围为0xA1-0xFE（对应位号01-94）。

* BIG5编码：台湾地区繁体中文标准字符集，采用双字节编码，共收录13053个中文字，1984年实施。

* GBK编码：1995年12月发布的汉字编码国家标准，是对GB2312编码的扩充，对汉字采用双字节编码。GBK字符集共收录21003个汉字，包含国家标准GB13000-1中的全部中日韩汉字，和BIG5编码中的所有汉字。

* GB18030编码：2000年3月17日发布的汉字编码国家标准，是对GBK编码的扩充，覆盖中文、日文、朝鲜语和中国少数民族文字，其中收录27484个汉字。GB18030字符集采用单字节、双字节和四字节三种方式对字符编码。兼容GBK和GB2312字符集。2005年11月8日，发布了修订版本：GB18030-2005，共收录汉字七万余个。2022年7月19日，发布了第二次修订版本：GB18030-2022，收录汉字总数八万余个。

* Unicode编码：国际标准字符集，它将世界各种语言的每个字符定义一个唯一的编码，以满足跨语言、跨平台的文本信息转换。Unicode采用四个字节为每个字符编码。

* UTF-8和UTF-16编码：Unicode编码的转换格式，可变长编码，相对于Unicode更节省空间。UTF-16的字节序有大尾序（big-endian）和小尾序（little-endian）之别。

## 文档更新日期

2024年2月27日