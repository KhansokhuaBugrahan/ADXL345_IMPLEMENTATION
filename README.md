# ADXL345_IMPLEMENTATION-via-SPI

Warning: There is no guarantee that each of the information in this repository is correct.                              
I do not take any responsibility for misusage or being referenced in case of bad results.                  
To avoid such issues, please make safety controls and make reliability tests.                      
Hope find you beneficial, have a nice day.    


Board: STM32F407G-DISC1            
IDE: STMCubdeIDE                                  
Reference: ADXL345-Datasheet
https://www.analog.com/media/en/technical-documentation/data-sheets/adxl345.pdf

In the maindebug.c file, you can  read comment lines for having better understanding.                    
You can see some test codes here.                 

main.c file includes simplified codes, you can run it directly. I recommed to follow this file,               
you can take a look at the corresponding line in the maindebug.c file, if you get stuck.                   
 
Also, you can find orientation test file and communication test file to test your communication line             
and adxl345's hardware reliability(if it is damaged, malfunction).          

You can find information about SPI configuration and working principle in adxl345.c file.
                                                              
                                                              
                                                                                    
                                                                            
Before setting up lockout mechanism, I am quite cautious about not triggering the interrupt multiple times.                                        
Click the icon to redirect YouTube and watch the test-1 video.                                           
[![Custom Thumbnail](https://github.com/KhansokhuaBugrahan/ADXL345_IMPLEMENTATION-via-SPI/blob/main/gif.gif)](https://www.youtube.com/watch?v=JeKnpv8_L8A)














After setting up lockout mechanism, I feel comfortable, lockout time 1 second here.                                                      
See that first lapse time between two interrupt is below lockout time(1000ms).                                                                           
Click the icon to redirect YouTube and watch the test-2 video.                                                           
[![Custom Thumbnail](https://github.com/KhansokhuaBugrahan/ADXL345_IMPLEMENTATION-via-SPI/blob/main/gif.gif)](https://www.youtube.com/watch?v=XMO4NOZyLm0)

As you can see in the below, first period is  under the lockout time(1 second)                                                             
but following periods are always higher than lockout time like 1.2 second                                         
![ORANGE LED STATE](https://github.com/KhansokhuaBugrahan/ADXL345_IMPLEMENTATION-via-SPI/blob/main/orangeLED.png "Optional Tooltip")
