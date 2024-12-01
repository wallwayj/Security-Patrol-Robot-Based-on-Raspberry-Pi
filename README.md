# Security-Patrol-Robot-Based-on-Raspberry-Pi
项目简介：本项目致力于开发一款以树莓派为核心的安保巡逻机器人，深度融合ROS框架，实现了模块化编程与精准路径规划。该机器人不仅具备人脸录入与陌生人智能识别功能，还通过PID控制的二维云台，实现对目标的精确追踪。同时利用环境传感器高效采集环境数据，一旦监测到任何异常状况，将迅速启动邮件及语音报警系统。此外机器人内置的无线串口模块，能够实时向下位机传输数据，实现全面的远程监控与管理。


​基于树莓派的安保巡逻机器人--项目介绍：https://blog.csdn.net/wallwayj/article/details/144156870?spm=1001.2014.3001.5502


代码源说明：本项目一共有三部分代码
Partial code for Raspberry Pi：为树莓派端的部分代码，打开文件夹，执行python newproject.py即可运行代码，其他ros路径规划等代码源相关库太多不方便上传，大家可以直接参考各大开源码进行自行配置；
STM32 end complete code (using UCOSIII)：此部分代码为安保室对机器人监控与接收端，使用了UCOSIII实时操作系统，直接编译烧入即可使用，需注意相关引脚的正确性；
WeChat Mini Program Complete Code Rpi5：此部分为微信小程序完整代码，与onenet进行数据交互，需要注意api，key等需要依据自己的信息进行适配。

