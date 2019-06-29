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
- **SPI_DMA**
    - SPI定时连续收发（DMA+TIM方式）
    - SPI单次收发（发送手动调用函数发送，接收使用中断方式）
- **SPWM_output**
    - 单极性SPWM脉宽调制输出
    - 双极性SPWM脉宽调制输出

