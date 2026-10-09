# 03_soft_pwm：软件 PWM 呼吸灯

Blue Pill (STM32F103C8T6) 板载 LED (PC13，低电平点亮) 实现 1Hz 正弦呼吸灯。
PC13 无定时器通道（Datasheet 引脚定义表确认），PWM 由软件模拟。

## 时序链（8MHz HSI）

| 层级 | 参数 | 计算 |
|---|---|---|
| SysTick 中断节拍 | 100 µs | RVR = 100µs × 8MHz − 1 = 799 |
| PWM 周期 | 10 ms (100Hz) | 100 拍 × 100µs，高于视觉暂留阈值，无频闪 |
| 呼吸周期 | 1 s (1Hz) | 100 个 PWM 周期 × 10ms |

## 架构

- ISR (SysTick_Handler)：清 COUNTFLAG → PWM 计数 0~99 → 与占空比比较写 BSRR
  → 周期走完置 g_PWM_Circle_Flag。ISR 内无乘除、无浮点。
- 主循环：查 g_PWM_Circle_Flag → 亮度表索引 +1 (0~99 回绕) → 取表值赋 g_Duty_Cycle → 清标志。
  ISR 置标志、主循环消费的 volatile 共享模式。
- 亮度表 const unsigned char g_Brightness_Table[100]，预生成存 Flash，运行时零计算：
  brightness[i] = round(50 × (1 − cos(2πi/100)))
  生成脚本 tools/gen_table.py。选正弦的原因：变化率在峰值处为零，
  最亮/最暗处有视觉停顿，消除线性扫描在回绕点的跳变感。

## 占空比定义

占空比 = 一个 PWM 周期内 LED 点亮时间 / 周期 × 100%。
本实现中 = (g_PWM_cnt &lt; g_Duty_Cycle 的拍数) / 100。

## 极性约定

LED_ON  = BSRR 高 16 位 (bit29) → PC13 输出低 → 点亮（低电平点亮）
LED_OFF = BSRR 低 16 位 (bit13) → PC13 输出高 → 熄灭

## 实测

理论呼吸周期 1.000s；秒表掐 10 个完整来回 ÷ 10 = 1.0s/来回，与理论一致。
