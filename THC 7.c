#include <16f877a.h>
#use delay(clock=1000000,RESTART_WDT)
#fuses hs
#FUSES PUT   
#include <lcd.c>
#FUSES WDT

#define n 8

unsigned long leitura=0;
long int fitrado;
int valores[n];

int i=0;
long int soma=0;

int histerese=5;
int definida;
int lida=0;
Int Vmin=25;
int temp=0;
int menu=0;
int retardo=0;
int t_retardo=0;
long int f_retardo=0;
long int c_retardo=0;



void main(){
   
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_32);    
   lcd_init();
   setup_wdt(WDT_288MS);
   set_tris_c(0b11111111);
   set_tris_b(0b11111001);
   port_b_pullups(true);
   set_tris_a(0b11110001);
   printf(lcd_putc,"\fAutorobotica ");
   printf(lcd_putc,"\nControle THC");
   delay_ms(3000);
   delay_ms(3000);
   definida=read_eeprom(0);
   histerese=read_eeprom(1);
   retardo=read_eeprom(2);
   f_retardo=make16(0,retardo);
   delay_us(30);
   
   while(true){
   restart_wdt();
   set_adc_channel(0);   
   temp=read_adc();
  
   temp=temp*1;//0.5
   leitura=temp;
   for(i=(n-1); i>0; i--) {
      valores[i]=valores[i-1];
      }
      soma=0;
   valores[0]=leitura;

      for(i=0;i<n;i++){
      soma+=valores[i];
      }
lida =soma/n;


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
        delay_ms(1000);  
       }
       
       if((input(pin_b5)==0)&&(histerese>1)){
       histerese=histerese-1;
       delay_ms(1000); 
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
      printf(lcd_putc,"\fTempo de retardo");
      printf(lcd_putc,"\nMsegundos:%lu",f_retardo);
      if((input(pin_b4)==0)&&(retardo<255)){
       retardo=retardo+20;
       delay_ms(1000);
       }      
       if((input(pin_b5)==0)&&(retardo>10)){
       retardo=retardo-20;
       delay_ms(1000);
       }
     f_retardo=make16(0,retardo);
     f_retardo=f_retardo*10;
      restart_wdt();          
      write_eeprom(2,retardo);
      delay_ms(1000);
      break;
      
     default:   
     printf(lcd_putc,"\f(V) Definida:%u\n(V) Atual :%u",definida,lida);
     menu=0;
     break;
  }
   
    if((lida > Vmin)&&(t_retardo==0)){
    while (f_retardo!=0){
    t_retardo= 1;
    f_retardo=f_retardo-1;
    delay_ms(15);
    restart_wdt();
    }
    }
    
    if((lida>Vmin)&&(t_retardo==1)){ 
    
      if((lida+histerese)<definida){
      output_high(pin_a2);
      } else output_low(pin_a2);
      
        if((lida-histerese)>definida){
      output_high(pin_a1);
      } else output_low(pin_a1);    
   }
    else {
    f_retardo=make16(0,retardo);
    f_retardo=f_retardo*10;
    t_retardo=0;
    output_low(pin_a2);
    output_low(pin_a1);
    }
    
   delay_ms(200);
    
   }
   
}


