#include <16f877a.h>
#use delay(clock=1600000)
#fuses hs
#FUSES PUT   
#include <lcd.c>
#FUSES WDT

int histerese=5;
int definida;
int lida=0;
Int Vmin=25;
int temp=0;
int menu=0;



void main(){
   
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_32);   
   setup_comparator(NC_NC_NC_NC);
   setup_vref(true);
   lcd_init();
   setup_wdt(WDT_2304MS);
   set_tris_c(0b11111111);
   set_tris_b(0b01111111);
   port_b_pullups(true);
  // set_tris_a(0b11111111);
   printf(lcd_putc,"\fRaul THC");
   delay_ms(3000);
   definida=read_eeprom(0);
   histerese=read_eeprom(1);
   
   while(true){
   restart_wdt();
   set_adc_channel(0);   
   temp=read_adc();
   temp=temp*0.5;
   lida=(lida+temp)/2;
   delay_ms(300);  
   
    if((input(pin_b3)==0)&&(menu==2)){
   menu=0;
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
       write_eeprom(1,histerese);
       delay_ms(1000);    
      break;
      
      default:   
     printf(lcd_putc,"\f(V) Definida :%u\n(V) Atual :%u",definida,lida);
     menu=0;
     break;
  }
   
    if(lida>Vmin){
      if((lida+histerese)<definida){
      output_high(pin_a2);
      } else output_low(pin_a2);
      
        if((lida+histerese)>definida){
      output_high(pin_a1);
      } else output_low(pin_a1);
    }else {
    output_low(pin_a2);
    output_low(pin_a1);
    }
    
   delay_ms(800);
 
  
  
   }
   
}


