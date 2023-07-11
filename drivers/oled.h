#ifndef __OPENLOONGSON_OLED_H
#define __OPENLOONGSON_OLED_H

#define  SIZE                                   16
#define  X_WIDTH                                128
#define  Y_WIDTH                                64
#define  Page                                   8

//GPIO
#define  OLED_RST_PIN                           54
#define  OLED_DC_PIN                            55

#define  OLED_DC_H                              rt_pin_write(OLED_DC_PIN, PIN_HIGH)
#define  OLED_DC_L                              rt_pin_write(OLED_DC_PIN, PIN_LOW)
#define  OLED_RST_H                             rt_pin_write(OLED_RST_PIN, PIN_HIGH)
#define  OLED_RST_L                             rt_pin_write(OLED_RST_PIN, PIN_LOW)

// spi复用  
#define LS1C_SPI_1_CS_0_GPIO            (49)        // gpio49/spi1_cs0/CAMHSYNC  
#define LS1C_SPI_1_CS_1_GPIO            (50)        // gpio50/spi1_cs1/CAMDATA0  
#define LS1C_SPI_1_CS_2_GPIO            (51)        // gpio51/spi1_cs2/CAMDATA1  
#define LS1C_SPI_1_CS_3_GPIO            (52)        // gpio52/spi1_cs3/CAMDATA2  
#define LS1C_SPI_1_MISO_GPIO            (47)        // gpio47/spi1_miso/CAMCLKOUT  
#define LS1C_SPI_1_MOSI_GPIO            (48)        // gpio48/spi1_mosi/CAMVSYNC  
#define LS1C_SPI_1_CLK_GPIO             (46)        // gpio46/spi1_clk/CAMPCLKIN  

void OLED_GPIO_Config(void);
void SPI_Config(void);
void OLED_WB(unsigned char TxData);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowChar(rt_uint8_t x, rt_uint8_t y, rt_uint8_t chr);
void OLED_ShowNum(rt_uint8_t x, rt_uint8_t y,rt_uint8_t num);
void OLED_ShowOneNum(rt_uint8_t x, rt_uint8_t y, rt_uint8_t num);
void OLED_ShowCHinese(rt_uint8_t x,rt_uint8_t y,rt_uint8_t no);
void OLED_DLY_ms(unsigned int ms);
void OLED_Fill(unsigned char bmp_dat);
void OLED_Clear(void);
void OLED_Init(void);


#endif

