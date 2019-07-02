# STM32_lib

### NOTICE

- This function library is only appropriate for **STM32F103RCT6**.
- Please contact me at 953799126lxc@gmail.com if there’s any mistakes.
- This library will be continue to be updated.

### CONTENT

- **ADC_input**
    - 定时器触发ADC稳定频率（2.5kHz或5kHz）连续采样，扫描模式/非扫描模式，DMA
    - ADC单次采样
- **PID_control**
    - 增量式PID闭环反馈
- **PWM_input_capture**
    - PWM输入捕获模式
    - 计算两路方波相位差
- **sp_math**
    - 数学函数库
    - 峰峰值
    - 视在功率/有功功率/有效值
- **SPI_DMA**
    - SPI定时连续收发（DMA+TIM方式）
    - SPI单次收发（发送手动调用函数发送，接收使用中断方式）
- **SPWM_output**
    - 单极性SPWM脉宽调制输出（磨平衡/非磨平衡）
    - 双极性SPWM脉宽调制输出z
- **DSP_lib**
    - ST官方DSP函数库
        - 基4FFT
        - IIR滤波器
        - PID
- **infrared_remote**
    - 红外遥控
    - 自定义按键功能

- **GUI_lib**
    - 界面显示函数
    - 波形视窗 WaveWindow
        - 一窗多种线型
        - 不同粗细
        - 参考线（横向、纵向、中轴线）
    - 信息视窗 MsgWindow
        - 数字型信息
        - 字符型信息
        - 左对齐 / 居中对齐
    - 菜单
        - 自动布局 / 手动布局
        - 