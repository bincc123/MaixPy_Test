class Board_Info:
    def __init__(self):
        self.pin_num = 48
        self.JTAG_TCK = 0
        self.JTAG_TDI = 1
        self.JTAG_TMS = 2
        self.JTAG_TDO = 3
        self.ISP_RX = 4
        self.ISP_TX = 5
        self.WIFI_TX = 6
        self.WIFI_RX = 7
        self.WIFI_EN = 8
        self.RS485_RX = 9  #TXKJ_K210_AI_Board Define
        self.RS485_TX = 10 #TXKJ_K210_AI_Board Define
        self.LED_B = 11    #TXKJ_K210_AI_Board Define
        self.LED_G = 12    #TXKJ_K210_AI_Board Define
        self.LED_R = 13    #TXKJ_K210_AI_Board Define
        self.Key_2 = 14    #TXKJ_K210_AI_Board Define
        self.Key_1 = 15    #TXKJ_K210_AI_Board Define
        self.BOOT_KEY = 16 #This is special use for BOOT Key
        self.Key_3 = 17    #TXKJ_K210_AI_Board Define
        self.MIC_ARRAY_BCK = 18
        self.MIC_ARRAY_WS = 19
        self.MIC_ARRAY_DATA3 = 20
        self.MIC_ARRAY_DATA2 = 21
        self.MIC_ARRAY_DATA1 = 22
        self.MIC_ARRAY_DATA0 = 23
        self.MIC_ARRAY_DATA_LED = 24 #TXKJ_K210_AI_Board Define
        self.MIC_ARRAY_CLK_LED = 25 #TXKJ_K210_AI_Board Define
        #self.SPI0_CS1 = 25
        self.SPI0_MISO = 26
        self.SPI0_CLK = 27
        self.SPI0_MOSI = 28
        self.SPI0_CS0 = 29
        #self.MIC0_WS = 30
        #self.MIC0_DATA = 31
        #self.MIC0_BCK = 32
        self.I2C1_SCL = 30 #TXKJ_K210_AI_Board Define
        self.I2C1_SDA = 31 #TXKJ_K210_AI_Board Define 
        self.RS485_RE = 32 #TXKJ_K210_AI_Board Define
        self.I2S_WS = 33 #TXKJ_K210_AI_Board Define
        self.I2S_DA = 34 #TXKJ_K210_AI_Board Define
        self.I2S_BCK = 35 #TXKJ_K210_AI_Board Define
        self.LCD_CS = 36
        self.LCD_RST = 37	
        self.LCD_DC = 38
        self.LCD_WR = 39
        self.DVP_SDA = 40
        self.DVP_SCL = 41
        self.DVP_RST = 42
        self.DVP_VSYNC = 43
        self.DVP_PWDN = 44
        self.DVP_HSYNC = 45
        self.DVP_XCLK = 46
        self.DVP_PCLK = 47
        self.pin_name=['JTAG_TCK','JTAG_TDI','JTAG_TMS','JTAG_TDO','ISP_RX','ISP_TX','WIFI_TX ','WIFI_RX ','WIFI_EN ','RS485_RX','RS485_TX','LED_B','LED_G','LED_R','Key_2','Key_1','BOOT_KEY','Key_3','MIC_ARRAY_BCK','MIC_ARRAY_WS ','MIC_ARRAY_DATA3','MIC_ARRAY_DATA2','MIC_ARRAY_DATA1','MIC_ARRAY_DATA0','MIC_ARRAY_DATA_LED','MIC_ARRAY_CLK_LED','SPI0_MISO','SPI0_CLK ','SPI0_MOSI','SPI0_CS0','I2C1_SCL','I2C1_SDA','RS485_RE','I2S_WS','I2S_DA','I2S_BCK','LCD_CS','LCD_RST','LCD_DC','LCD_WR ','DVP_SDA','DVP_SCL','DVP_RST','DVP_VSYNC','DVP_PWDN','DVP_HSYNC','DVP_XCLK','DVP_PCLK']
        self.D = [4, 5, 21, 22, 23, 24, 32, 15, 14, 13, 12, 11, 10, 3]

    def pin_map(self,Pin = None):
        num_len = 10
        str_len = 23
        if Pin == None :
            num_sum_length = num_len
            str_sum_length = str_len
            Pin_str_obj = "Pin"
            Pin_str_obj_length = len(Pin_str_obj)
            Pin_str_obj_front = 3
            Pin_str_obj_rear = num_sum_length - Pin_str_obj_front - Pin_str_obj_front
            fun_str_obj = "Function"
            fun_str_obj_length = len(fun_str_obj)
            fun_str_obj_front = 5
            fun_str_obj_rear = str_sum_length - fun_str_obj_front - fun_str_obj_length
            print("|%s%s%s|%s%s%s|"%(str(Pin_str_obj_front * '-'),Pin_str_obj,str(Pin_str_obj_rear * '-'),str(fun_str_obj_front * '-'),fun_str_obj,str(fun_str_obj_rear*'-')))
            for i in range(0,len(self.pin_name)):
                num = str(i)
                num_length = len(num)
                num_front = 3
                num_rear = num_sum_length - num_front - num_length
                str_length = len(self.pin_name[i])
                str_front = 5
                str_rear = str_sum_length - str_front - str_length
                print("|%s%d%s|%s%s%s|"%(str(num_front * ' '),i,str(num_rear * ' '),str(str_front * ' '),self.pin_name[i],str(str_rear*' ')))
                print("+%s|%s+"%(str(num_sum_length*'-'),str(str_sum_length*'-')))
        elif isinstance(Pin,int) and Pin < 0 or Pin > 47:
            print("Pin num must in range[0,47]")
            return False
        elif isinstance(Pin,int):
            Pin_sum_length = num_len
            string_sum_length = str_len
            pin_str_obj = "Pin"
            pin_str_obj_length = len(pin_str_obj)
            pin_str_obj_front = 3
            pin_str_obj_rear = Pin_sum_length - pin_str_obj_front - pin_str_obj_front
            Fun_str_obj = "Function"
            Fun_str_obj_length = len(Fun_str_obj)
            Fun_str_obj_front = 5
            Fun_str_obj_rear = string_sum_length - Fun_str_obj_front - Fun_str_obj_length
            print("|%s%s%s|%s%s%s|"%(str(pin_str_obj_front * '-'),pin_str_obj,str(pin_str_obj_rear * '-'),str(Fun_str_obj_front * '-'),Fun_str_obj,str(Fun_str_obj_rear*'-')))
            Pin_str = str(Pin)
            Pin_length = len(Pin_str)
            Pin_front = 3
            Pin_rear = Pin_sum_length - Pin_front - Pin_length
            string_length = len(self.pin_name[Pin])
            string_front = 5
            string_rear = string_sum_length - string_front - string_length
            print("|%s%d%s|%s%s%s|"%(str(Pin_front * ' '),Pin,str(Pin_rear * ' '),str(string_front * ' '),self.pin_name[Pin],str(string_rear*' ')))
            print("+%s|%s+"%(str(Pin_sum_length*'-'),str(string_sum_length*'-')))
        else:
            print("Unknow error")
            return False
global board_info
board_info=Board_Info()
