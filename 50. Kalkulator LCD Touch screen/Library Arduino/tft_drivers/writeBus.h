//Write 8Bit data into LCD register
//ʹ��8λ������������ģʽ ��Һ����ָ��Ĵ�����������
void LCD_WR_REG(u8 data)
{ 
	LCD_RS_CLR;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;	
}
//Write 8Bit data into LCD DataRegister
//ʹ��8λ������������ģʽ ��Һ�������ݼĴ�����������
void LCD_WR_DATA(u8 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;
}
//Write 16Bit data into LCD GRAM
//ʹ��8λ������������ģʽ ��Һ����GRAM����һ��16λ��ɫ����
void LCD_WR_DATA_16Bit(u16 color)
{
	u8 DH,DL;
	DH=color>>8;
	DL=color;
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET; 
	DATAOUT(DH);//��8λ
	LCD_WR_CLR;
	LCD_WR_SET;	
	DATAOUT(DL);//��8λ	
	LCD_WR_CLR;
	LCD_WR_SET;	 
	LCD_CS_SET;
}

