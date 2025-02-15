#include <main.h>
#include <string.h>

#define tb1    PIN_D4
#define led    PIN_D5 //LOA
#define cb     PIN_A1



#define LCD_RS_PIN PIN_B6    // RS noi voi B6
#define LCD_RW_PIN PIN_B5
#define LCD_ENABLE_PIN PIN_B4 // chan E noi voi B4

#define LCD_DATA4 PIN_B3    //D4 noi voi B3
#define LCD_DATA5 PIN_B2
#define LCD_DATA6 PIN_B1
#define LCD_DATA7 PIN_B0  

#include <lcd.c>

unsigned char x=11;
char sdt[20]="0399783163"; //  0975122195

unsigned char dataSMS[80],index=0;
/***************************************************************/
#int_RDA
void  RDA_isr(void)//Ngat du lieu khi truyen nhan
{
     unsigned char c; 
     c=getc();//Gan ki tu vua nhan duoc vao bien tam 
     dataSMS[index] =  c; // dua du lieu vao bo dem
     index++;
     if(index>=80)index=1;
}
/***************************************************************/


void xoabodem()
{
    char i;
    for(i=0;i<80;i++)dataSMS[i]=0; 
    index=0;
}



void doctinnhan()  //printf("AT+CMGDA=\"DEL ALL\"\r\n");
{
  if(index >1) // neu trong bo dem co du lieu  //sim >1
        {
        
         
         delay_ms(1000); // cho du lieu gui xong
         
         if(strstr(dataSMS,(unsigned char *)"Bat") != 0)
         {
          lcd_gotoxy(16,1);lcd_putc("<");
          output_high(tb1);delay_ms(2000); //BAT RELAY
           lcd_gotoxy(16,1);lcd_putc(" ");
                    
         }
         
                
         else if(strstr(dataSMS,(unsigned char *)"Tat") != 0)   
        { 
         lcd_gotoxy(16,1);lcd_putc("<");
          output_low(tb1); output_high(led);delay_ms(2000); //TAT RELAY 
           lcd_gotoxy(16,1);lcd_putc(" ");
                
        }
        
         else if(strstr(dataSMS,(unsigned char *)"BIP") != 0)   
        { 
         lcd_gotoxy(16,1);lcd_putc("<");
          output_high(led);delay_ms(2000); // TAT COI 
           lcd_gotoxy(16,1);lcd_putc(" ");
                
        }
    
    lcd_gotoxy(1,2);lcd_putc("                 ");

    xoabodem();//xoa bo dem
    
  }
}

void SIM_INIT()
{
  delay_ms(10000);
  printf("AT\r\n");delay_ms(500);
  printf("ATE0\r\n");delay_ms(500);
  printf("AT+CMGF=1\r\n");delay_ms(500);
  printf("AT+CNMI=2,2,0,0,0\r\n");delay_ms(500); // GUI ND SMS RA 
  printf("AT&W\r\n");delay_ms(500);
  printf("AT+CMGDA=\"DEL ALL\"\r\n");delay_ms(500);
}
void main()
{  delay_ms(2000);


   output_low(tb1);




lcd_init();  // khoi dong LCD




output_low(led);delay_ms(100);
output_high(led);delay_ms(100);

output_low(led);delay_ms(100);
output_high(led);delay_ms(100);


       lcd_gotoxy(1,1);lcd_putc("               ");
       lcd_gotoxy(1,2);lcd_putc("               "); 



           lcd_gotoxy(1,2);lcd_putc("                ");
           lcd_gotoxy(1,1);lcd_putc("  KHOI DONG...      "); 
          delay_ms(15000);
   
         ENABLE_INTERRUPTS(INT_RDA); //cho phep ngat uart
         ENABLE_INTERRUPTS(GLOBAL); //cho phep tat ca cac loai ngat hoat dong   ;
         
           printf("AT+CMGS=\"%s\"\r\n",sdt);delay_ms(200);
           printf("DA KHOI DONG ! ");
           printf("%c",26);
           delay_ms(3000);
           
           
       lcd_gotoxy(1,2);lcd_putc("                ");
       lcd_gotoxy(1,1);lcd_putc("    OK !      "); 
       delay_ms(1000);
       lcd_gotoxy(1,1);lcd_putc("    XIN CHAO   ");
       lcd_gotoxy(1,2);lcd_putc("               "); 

       output_low(led);delay_ms(100);
       output_high(led);delay_ms(100);

   
   //SIM_INIT();
   

  
   xoabodem();//xoa bo dem
   while(TRUE)
   {
      doctinnhan();     
      
      
      if(!input(cb))
          {
          
          output_low(led);  output_high(tb1);
          lcd_gotoxy(1,1);lcd_putc("   SEND SMS..   "); 
          lcd_gotoxy(1,2);lcd_putc("   CANH BAO !!   "); 
             
           printf("AT+CMGS=\"%s\"\r\n",sdt);delay_ms(200);
           printf("CANH BAO CO TROM !! ");
           printf("%c",26);
           delay_ms(3000);
           
           lcd_gotoxy(1,1);lcd_putc("   CO TROM !!     ");
           
     
        }
             
   }

}

