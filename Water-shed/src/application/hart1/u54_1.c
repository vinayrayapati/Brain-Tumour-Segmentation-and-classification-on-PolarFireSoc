/*******************************************************************************
 * Copyright 2019-2022 Microchip FPGA Embedded Systems Solutions.
 *
 * SPDX-License-Identifier: MIT
 *
 * Application code running on U54_1
 *
 * PolarFire SoC MSS GPIO interrupt example project
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mpfs_hal/mss_hal.h"
#include <math.h>
//#include "drivers/mss/mss_gpio/mss_gpio.h"
#include "drivers/mss/mss_mmuart/mss_uart.h"

#include "data.h"
/******************************************************************************
 * Instruction message. These message will be displayed on the UART terminal
   when the program starts.
 *****************************************************************************/

uint8_t w=128,h=128;

uint8_t g_message2[] =
"\r\n\r\n\r\n **** PolarFire SoC Water-shed Segmentation ****\r\n\r\n\r\n\
This program is running on u54_1.\r\n\r\n";

#define RX_BUFF_SIZE    64U

uint8_t g_rx_buff[RX_BUFF_SIZE] = {0};
volatile uint8_t g_rx_size = 0U;

/* Main function for the hart1(U54 processor).
 * Application code running on hart1 is placed here.
 * On Icicle kit, apart from the UART menu, you can also use push button
 */

void u54_1(void)
{
    uint32_t dmessage[5]={0};


    /* Clear pending software interrupt in case there was any.
     * Enable only the software interrupt so that the E51 core can bring this
     * core out of WFI by raising a software interrupt In case of external,
     * bootloader not present
     */

    clear_soft_interrupt();
    set_csr(mie, MIP_MSIP);

#if (IMAGE_LOADED_BY_BOOTLOADER == 0)

    /*Put this hart into WFI.*/

    do
    {
        __asm("wfi");
    }while(0 == (read_csr(mip) & MIP_MSIP));

    /* The hart is out of WFI, clear the SW interrupt. Hear onwards Application
     * can enable and use any interrupts as required */
    clear_soft_interrupt();
#endif

    PLIC_init();
    __enable_irq();

    /* Reset the peripherals turn on the clocks */

    (void)mss_config_clk_rst(MSS_PERIPH_MMUART1, (uint8_t) MPFS_HAL_FIRST_HART, PERIPHERAL_ON);
    (void)mss_config_clk_rst(MSS_PERIPH_MMUART2, (uint8_t) MPFS_HAL_FIRST_HART, PERIPHERAL_ON);
    (void)mss_config_clk_rst(MSS_PERIPH_MMUART3, (uint8_t) MPFS_HAL_FIRST_HART, PERIPHERAL_ON);
    (void)mss_config_clk_rst(MSS_PERIPH_CFM, (uint8_t) MPFS_HAL_FIRST_HART, PERIPHERAL_ON);

   /* mmuart0 initialization */


   /* mmuart1 initialization */

    MSS_UART_init( &g_mss_uart1_lo,
            MSS_UART_115200_BAUD,
            MSS_UART_DATA_8_BITS | MSS_UART_NO_PARITY | MSS_UART_ONE_STOP_BIT);

    MSS_UART_polled_tx_string(&g_mss_uart1_lo,
                       g_message2 );


    uint8_t message[]= "\r\n----Finish of water-shed segmentation----\r\n";





    // Start of the water-shed algorithm

    padding(data);

    //padding
    MSS_UART_polled_tx_string(&g_mss_uart1_lo, message);
}
//padding and Thresholding
void padding(uint8_t data[w][h])
{
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\r\nThe start of padding....\r\n");
    uint8_t zeroFramedAry[132][132];
    /*for(int i=0;i<(128+(2*2));i++){
              for(int j=0;j<(128+(2*2));j++){
                zeroFramedAry[i][j]=0;
              }
            }*/
    //print_data(zeroFramedAry,132,132);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r zeroFramedAry initialisation done....\r\n");
    uint8_t threshold=150;
    for(uint8_t r=0;r<128;r++){
      for(uint8_t c=0;c<128;c++){
          if(data[r][c]<threshold){
          zeroFramedAry[r+2][c+2]=0;
        }else{
            zeroFramedAry[r+2][c+2]=1;
        }
      }
      }
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r loADING IMAGE done....\r\n");
    for(uint8_t k=0;k<132;k++)
    {
     for(uint8_t l=0;l<2;l++)
      {
       zeroFramedAry[k][l]=0;
       zeroFramedAry[k][132-1-l]=0;
       }
    }
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r padding row frame done....\r\n");
    for(uint8_t j=0;j<132;j++){
        for(uint8_t m=0;m<2;m++){
          zeroFramedAry[m][j]=0;
          zeroFramedAry[132-1-m][j]= 0;
        }
    }
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r padding column frame done....\r\n");
    //print_data(zeroFramedAry,132,132);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r Printing done...\n\r");
    morphology(zeroFramedAry,data);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is Input data\n\r");
    print_data_128(data,128,128);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is Thresholded image...\n\r");
    print_data_132(zeroFramedAry,132,132);
}


// Morphology
void morphology(uint8_t zeroFramedAry[132][132],uint8_t data[128][128])
{
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\r\nThe start of morphology....\r\n");
    static uint8_t tempFramedAry[132][132];
    static uint8_t morphFramedAry[132][132];
   uint8_t kernel[3][3]={0, 1, 0, 1, 1, 1, 0, 1, 0};


  //  MSS_UART_polled_tx_string(&g_mss_uart1_lo,"Flag Check start....\r\n");
    for(uint8_t i = 0; i<128; i++)
    {
              for(uint8_t j =0; j<128; j++)
              {
                if(zeroFramedAry[i+2][j+2]==kernel[1][1])
                {
                    if(i==0&&j==0)
                    {
                        //MSS_UART_polled_tx_string(&g_mss_uart1_lo,"Flag Check 1....\r\n");
                    }
                    if(i==127&&j==127)
                    {
                       // MSS_UART_polled_tx_string(&g_mss_uart1_lo,"Flag Check 3....\r\n");
                    }
                    uint8_t flag = 1; // Will use this as a boolean flag for whether it passes or not
                    uint8_t rowStart = (i+2-1);
                    uint8_t rowEnd = (rowStart+3);
                    uint8_t colStart = (j+2-1);
                    uint8_t colEnd = (colStart + 3);
                    uint8_t seRow;
                    uint8_t seCol;
                   for(uint8_t m =0; m< (rowEnd-rowStart); m++)
                   {
                      for(uint8_t n = 0; n< (colEnd-colStart); n++)
                      {
                        seRow =  (3-(rowEnd-m-rowStart));
                        seCol =  (3-(colEnd-n-colStart));
                        if(kernel[seRow][seCol]==1)
                        {
                            if(zeroFramedAry[m+rowStart][n+colStart]!=kernel[seRow][seCol])
                            {
                                //if(j==127)
                                  //  {
                                   // MSS_UART_polled_tx_string(&g_mss_uart1_lo,"Flag Check 2....\r\n");
                                   // }
                                flag=0;
                            }
                        }
                      }
                   }
                   tempFramedAry[i+2][j+2] = flag;
                }
              }
    }
  //  MSS_UART_polled_tx_string(&g_mss_uart1_lo,"Flag check Done....\r\n");

    for(uint8_t i = 2; i<(130); i++){
              for(uint8_t j =2; j<(130); j++){

                if(tempFramedAry[i][j]==kernel[1][1]){

                    uint8_t rowStart = (i-1);
                    uint8_t rowEnd = (rowStart+3);
                    uint8_t colStart = (j-1);
                    uint8_t colEnd = (colStart + 3);

                    uint8_t seRow;
                    uint8_t seCol;

                   for(uint8_t i = rowStart; i< rowEnd; i++){
                      for(uint8_t j = colStart; j< colEnd; j++){

                        seRow =  (3-(rowEnd-i));
                        seCol =  (3-(colEnd-j));

                        if(kernel[seRow][seCol]==1){
                            morphFramedAry[i][j] = kernel[seRow][seCol];
                        }

                      }

                   }

                }

              }
    }
    //print_data(morphFramedAry,132,132);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r Morphology Done....\r\n");
    dilation(morphFramedAry,kernel,data);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is morphFramedAry image...\n\r");
    print_data_132(morphFramedAry,132,132);
}

// Dilation
void dilation(uint8_t morphFramedAry[132][132],uint8_t kernel[3][3],uint8_t data[128][128])
{
   static uint8_t dilation[132][132];
   static uint8_t boundary[132][132];

for(uint8_t i = 2; i<(130); i++){
       for(uint8_t j =2; j<(130); j++){

         if(morphFramedAry[i][j]==kernel[1][1]){

             uint8_t rowStart = (i-1);
             uint8_t rowEnd = (rowStart+3);
             uint8_t colStart = (j-1);
             uint8_t colEnd = (colStart + 3);

             uint8_t seRow;
             uint8_t seCol;

            for(uint8_t i = rowStart; i< rowEnd; i++){
               for(uint8_t j = colStart; j< colEnd; j++){

                 seRow =  (3-(rowEnd-i));
                 seCol =  (3-(colEnd-j));

                 if(kernel[seRow][seCol]==1){
                     dilation[i][j] = kernel[seRow][seCol];
                 }

               }

            }

         }

       }
}
for(uint8_t k=0;k<132;k++)
    {
     for(uint8_t l=0;l<132;l++)
      {
       boundary[k][l]= morphFramedAry[k][l]-dilation[k][l];
       }
    }
//print_data(dilation,132,132);
MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r dilation Done....\r\n");

output(morphFramedAry,boundary,data);
MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is dilated image...\n\r");
print_data_132(dilation,132,132);
MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is Subtracted image...\n\r");
print_data_132(boundary,132,132);
//distance_transform(morphFramedAry,dilation);
}
//Distance Transform
/*
void distance_transform(uint8_t morphFramedAry[132][132],uint8_t dilation[132][132])
{

    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"distance transform start...\r\n");
    static double b[132][132];

    static uint8_t c[132][132],d[132][132];
    float x,y,z;
    float temp;
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"dt check 1...\r\n");
    for(uint8_t i=0;i<132;i++)
    {
        for(uint8_t j=0;j<132;j++)
        {
            b[i][j]=255;
            d[i][j]=1;
        }
    }

    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"dt check 2...\r\n");

    for(uint8_t i=0;i<132;i++)
    {
        for(uint8_t j=0;j<132;j++)
        {

        if(morphFramedAry[i][j]==1)
        {
            d[i][j]=0;
        }

        }

    }
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"dt check 3...\r\n");
    temp=0;
    for(uint8_t i=0; i<132; i++ ){
                for(uint8_t j=0; j<132; j++){

                    if(d[i][j]==0)
                    {
                        for(uint8_t k=0; k<132; k++ ){
                            for(uint8_t l=0; l<132; l++){

                                if(d[k][l]==1)
                                {
                                x=(k-i)*(k-i);
                                y=(l-j)*(l-j);
                                temp = sqrt(x+y);
                                if(temp< b[i][j])
                                {
                                    b[i][j]=temp;
                            }
                        }
                    }
                }

            }
        }

    }

    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"dt check 4...\r\n");

    for(uint8_t i=0; i<132; i++ ){
            for(uint8_t j=0; j<132; j++){
                    if(b[i][j]==255)
                    {
                        b[i][j]=0;
                    }
                }

                }

    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"dt check 5...\r\n");
    float max=b[0][0];
    for(uint8_t i=0;i<132;i++)
    {
     for(uint8_t j=0;j<132;j++)
     {
        if(b[i][j]>max){
            max=b[i][j];
        }
     }
    }
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"dt check 6...\r\n");
    print_data_double(b,132,132);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"dt check 7...\r\n");
    uint32_t mes[10]={0};
    sprintf(mes,"%f\r\n",(uint64_t) max);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo, mes);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"distance transform Done....\r\n");
}*/
//Output
void output(uint8_t morphFramedAry[132][132],uint8_t boundary[132][132],uint8_t data[128][128])
{
    static uint8_t rgb[128][128][3];
//    static uint8_t output[128][128];
    for(uint8_t i=0;i<128;i++)
    {
     for(uint8_t j=0;j<128;j++)
     {
      rgb[i][j][0]=data[i][j];
       rgb[i][j][1]=data[i][j];
        rgb[i][j][2]=data[i][j];

     }

    }
    //uint8_t count=0;
    for(uint8_t i=0;i<128;i++)
    {
     for(uint8_t j=0;j<128;j++)
     {
        if(morphFramedAry[i+2][j+2]==1){
            rgb[i][j][0]=255;
            //count++;
        }
     }
    }
    for(uint8_t i=0;i<128;i++)
    {
     for(uint8_t j=0;j<128;j++)
     {
        if(boundary[i+2][j+2]==1){
            rgb[i][j][1]=255;
            //count++;
        }
     }
    }
    /*
    uint8_t cnt_mes[10]={0};
    sprintf(cnt_mes,"\n\r***** The Count is: %d *****\n\r",count);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,cnt_mes);
    verify(rgb,data);*/
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is output image....\n\r");
    print_data_3d(rgb,128,128,3);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r Output generation Done....\n\r");
}
/*
void verify(uint8_t rgb[128][128][3],uint8_t data[128][128])
{
    static uint8_t verify[128][128];
    for(uint8_t i=0;i<128;i++)
    {
     for(uint8_t j=0;j<128;j++)
     {
        verify[i][j]= rgb[i][j][0]-data[i][j];
        }
     }
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is Verification image....\n\r");
    print_data_128(verify,128,128);
    MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r This is Verification Done....\n\r");
}*/
void print_data_128(uint8_t data[128][128],uint8_t width,uint8_t height)
{
    uint32_t mes1[10]={0};
    MSS_UART_polled_tx_string(&g_mss_uart1_lo, "\n\r The result image is:\n\r");
    for(uint8_t i=0;i<width;i++)
    {MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r");
        for(uint8_t j=0;j<height;j++)
        {
            sprintf(mes1,"%d ",data[i][j]);
            MSS_UART_polled_tx_string(&g_mss_uart1_lo,mes1);
        }
    }
}
void print_data_132(uint8_t data[132][132],uint8_t width,uint8_t height)
{
    uint32_t mes1[10]={0};
    MSS_UART_polled_tx_string(&g_mss_uart1_lo, "\n\r The result image is:\n\r");
    for(uint8_t i=0;i<width;i++)
    {MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r");
        for(uint8_t j=0;j<height;j++)
        {
            sprintf(mes1,"%d ",data[i][j]);
            MSS_UART_polled_tx_string(&g_mss_uart1_lo,mes1);
        }
    }
}
void print_data_3d(uint8_t data[128][128][3],uint8_t width,uint8_t height,uint8_t channel)
{
    uint32_t mes1[10]={0};
    MSS_UART_polled_tx_string(&g_mss_uart1_lo, "\n\rThe result image is:\n\r");
    for(uint8_t k=0;k<channel;k++)
    {MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r");
        for(uint8_t i=0;i<width;i++)
        {MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\n\r");
            for(uint8_t j=0;j<height;j++)
             {  //if(j==10)
                //{
                  //  MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\r\n");
               // }
                sprintf(mes1,"%d ",data[i][j][k]);
                MSS_UART_polled_tx_string(&g_mss_uart1_lo,mes1);
            }
        }
    }
}
void print_data_double(double data[132][132],uint8_t width,uint8_t height)
{
    uint32_t mes1[10]={0};
    MSS_UART_polled_tx_string(&g_mss_uart1_lo, "\n\rThe result image is:\r\n");
    for(uint8_t i=0;i<width;i++)
    {MSS_UART_polled_tx_string(&g_mss_uart1_lo,"\r\n");
        for(uint8_t j=0;j<height;j++)
        {
            sprintf(mes1,"%ld,",data[i][j]);
            MSS_UART_polled_tx_string(&g_mss_uart1_lo,(uint64_t) mes1);
        }
    }
}
