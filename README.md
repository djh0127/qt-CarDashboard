# qt-CarDashboard
基于Qt开发的车载中控UI项目，适合嵌入式车载HMI方向学习。

## 技术栈
- C++
- Qt（Widgets / QPainter）
- SQLite3 数据库
- 多线程

## 项目简介
模拟车载中控仪表盘界面，实现仪表数据动态刷新、本地数据存储，分离UI渲染与数据业务线程，避免界面卡顿。

## 功能
1. 自定义表盘控件绘制，车速、转速动态展示
2. 油量、电量状态显示
3. 车辆告警提示弹窗
4. SQLite存储车辆运行记录
5. 多线程异步更新数据，UI不阻塞

## 编译环境
- Windows
- Qt Creator
- qmake

## 编译步骤
```bash
qmake
make
