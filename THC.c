#include <16f877a.h>
#use delay(clock=1600000)
#fuses hs
#include <lcd.c>


int histerese=1;
long int definida=50,lida;





void main(){
   
    setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_32);   
   setup_comparator(NC_NC_NC_NC);
   setup_vref(true);
   lcd_init();
   
   set_tris_c(0b11111111);
   set_tris_b(0b01111111);
   port_b_pullups(true);
   set_tris_a(0b11111111);
    printf(lcd_putc,"\fRaul THC");
    delay_ms(3000);
   
   while(true){
   set_adc_channel(0);   
    lida=read_adc();
    lida=lida*0.1960;
    delay_ms(300);   
   
   
   while((input(pin_b4)==0)||(input(pin_b5)==0)){
   printf(lcd_putc,"\fAjuste de tensao");
   printf(lcd_putc,"\ndistancia:%lu",definida);
   
    if((input(pin_b4)==0)&&(definida<200)){
    definida=definida+1;
    }
    
    if((input(pin_b5)==0)&&(definida>1)){
    definida=definida-1;
    }
    delay_ms(800);
   }
   if((lida-histerese)>definida){
   output_high(pin_a1);
   }
   else output_low(pin_a1);
   
   if((lida+histerese)<definida){
   output_high(pin_a2);
   }
   else output_low(pin_a2);
   delay_ms(200);
  printf(lcd_putc,"\fDefinida 1:%lu\nLida :%lu",definida,lida);
  
   }
   
}


