#define KEY0_PORT           PORTD
#define KEY0_DDR            DDRD
#define KEY0_PIN               PIND
#define KEY0                        PD0

#define KEY1_PORT           PORTD
#define KEY1_DDR             DDRD
#define KEY1_PIN                PIND
#define KEY1                        PD1

#define KEY2_PORT           PORTD
#define KEY2_DDR              DDRD
#define KEY2_PIN                    PIND
#define KEY2                   PD2

#define KEY3_PORT           PORTD
#define KEY3_DDR          DDRD
#define KEY3_PIN                    PIND
#define KEY3                   PD3

#define KEY0_STATUS    (BIT_STATUS(KEY0_PIN,KEY0))
#define KEY1_STATUS     (BIT_STATUS(KEY1_PIN,KEY1))
#define KEY2_STATUS    (BIT_STATUS(KEY2_PIN,KEY2))
#define KEY3_STATUS   (BIT_STATUS(KEY3_PIN,KEY3))


#define KEY_SERIES_FLAG     200      //按键连发开始所需时间长度
#define KEY_SERIES_DELAY    5       //按键连发的时间间隔长度

//按键属性
#define KEY_DOWN        0xA0
#define KEY_LONG        0xB0
#define KEY_LIAN        0xC0
#define KEY_UP          0xD0

#define NO_KEY          0x00

#define KEY0_DOWN       0X01
#define KEY1_DOWN       0X02
#define KEY2_DOWN       0X03
#define KEY3_DOWN       0X04

#define KEY0_PRESS      (KEY_DOWN|KEY0_DOWN)
#define KEY1_PRESS      (KEY_DOWN|KEY1_DOWN)
#define KEY2_PRESS      (KEY_DOWN|KEY2_DOWN)
#define KEY3_PRESS      (KEY_DOWN|KEY3_DOWN)

