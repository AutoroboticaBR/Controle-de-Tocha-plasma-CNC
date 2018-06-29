#include <16f877a.h>
#use delay(clock=1000000)
#fuses hs
#FUSES PUT   
#include <lcd.c>
#FUSES WDT

#define N 4

unsigned long leitura=0;
long fitrado;
int valores[N];

int i=0;
long soma=0;

int histerese=5;
int definida;
int lida=0;
Int Vmin=25;
int temp=0;
int menu=0;
int retardo=0;
int t_retardo=0;
long f_retardo=0;



void main(){
   
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_32);    
   lcd_init();
   setup_wdt(WDT_2304MS);
   set_tris_c(0b11111111);
   set_tris_b(0b11111001);
   port_b_pullups(true);
   set_tris_a(0b11110001);
   printf(lcd_putc,"\fRaul ");
   printf(lcd_putc,"\nControle THC");
   delay_ms(300);
   definida=read_eeprom(0);
   histerese=read_eeprom(1);
   retardo=read_eeprom(2);
   
   while(true){
   restart_wdt();
   set_adc_channel(0);   
   temp=read_adc();
  
   temp=temp*1;//0.5
   leitura=(leitura+temp)/2;
   lida=(lida+leitura)/2;
   


    if((input(pin_b3)==0)&&(menu==4)){
   menu=0;
   delay_ms(1500);
   }
   
   if((input(pin_b3)==0)&&(menu==3)){
   menu=4;
   delay_ms(1500);
   }
    if((input(pin_b3)==0)&&(menu==2)){
   menu=3;
   delay_ms(1500);
   }
      
   if((input(pin_b3)==0)&&(menu==1)){
   menu=2;
   delay_ms(1500);
   }
   
     if((input(pin_b3)==0)&&(menu==0)){
   menu=1;
   delay_ms(1500);
   }
   
   switch (menu){
      case 1:
      printf(lcd_putc,"\fAjuste de tensao");
      printf(lcd_putc,"\nVoltagem:%u",definida);
      restart_wdt();
      if((input(pin_b4)==0)&&(definida<256)){
      definida=definida+1;
       }
       
       if((input(pin_b5)==0)&&(definida>1)){
       definida=definida-1;
       }
       write_eeprom(0,definida);
       delay_ms(1000);    
       break;
      
       case 2:
      printf(lcd_putc,"\fAjuste histerese");
      printf(lcd_putc,"\nVolts:%u",histerese);
       restart_wdt();
       if((input(pin_b4)==0)&&(histerese<50)){
       histerese=histerese+1;
       }
       
       if((input(pin_b5)==0)&&(histerese>1)){
       histerese=histerese-1;
       }
       break;
       
       case 3:
      printf(lcd_putc,"\fTeste de saida");
      printf(lcd_putc,"\nVolts:%u",histerese);
     
       
       while(input(pin_b5)==0){
       output_high(pin_a2);
       output_low(pin_a1);
       printf(lcd_putc,"\nDesce");
       
       }
       while(input(pin_b4)==0){
       output_high(pin_a1);
       output_low(pin_a2);
       printf(lcd_putc,"\nSobe ");
       
       }
       
      restart_wdt();          
       write_eeprom(1,histerese);
       delay_ms(1000);    
      break;
      
      case 4:
      f_retardo=retardo*10;
      printf(lcd_putc,"\fTempo de retardo");
      printf(lcd_putc,"\nMsegundos:%u",retardo);
      if((input(pin_b4)==0)&&(retardo<250)){
       retardo=retardo+20;
       }
       
       if((input(pin_b5)==0)&&(retardo>20)){
       retardo=retardo-20;
       }
      restart_wdt();          
      write_eeprom(2,retardo);
      delay_ms(1000);
      break;
      
     default:   
     printf(lcd_putc,"\f(V) Definida:%u\n(V) Atual :%u",definida,lida);
     menu=0;
     break;
  }
   
    if(lida>Vmin){
    t_retardo= t_retardo+58;
    if(t_retardo>retardo){
    t_retardo=retardo;
      if((lida+histerese)<definida){
      output_high(pin_a2);
      } else output_low(pin_a2);
      
        if((lida+histerese)>definida){
      output_high(pin_a1);
      } else output_low(pin_a1);
    }
    }
    else {
    t_retardo=0;
    output_low(pin_a2);
    output_low(pin_a1);
    }
    
   delay_ms(200);
    
   }
   
}


