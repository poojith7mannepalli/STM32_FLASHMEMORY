/*
 * G473_Flash.c
 *
 *  Created on: Jan 31, 2024
 *      Author: poojith7
 */
#include "G473_Flash.h"

uint32_t UL_page;
uint32_t UL_bank;


/***************************
* Function Name  :BSP_GetBankAndPageNumber(uint32_t UL_address)
*
* Abstract    : This function calculates bank size and page size and it gives which page and under which bank does it come
*
* Requiremnet Traceability :
*
* Function Parameters:
* 					UL_address: This describes the address that you want to change memory
*
* Return Value :  its return a struct
*Function Design:
 * step1 : Firstly it finds the size of bank and page
 * step2 : It checks under which bank and under which page does it come.
***************************/
st_FlashLocation BSP_GetBankAndPageNumber(uint32_t UL_address) {
    st_FlashLocation st_location;

    uint32_t UL_bankSize = 512 * 1024;
    uint32_t UL_pageSize = 2 * 1024;

    st_location.UL_bankNumber = (UL_address >= 0x08000000 && UL_address <= 0x0803FFFF) ? 1 : 2;
    UL_bank = st_location.UL_bankNumber;

    if (st_location.UL_bankNumber == 1) {
    	st_location.UL_pageNumber = (UL_address - 0x08000000) / UL_pageSize;
    } else {
    	st_location.UL_pageNumber = (UL_address - 0x08040000) / UL_pageSize;
    }
    UL_page  = st_location.UL_pageNumber;

    return st_location;
}


/***************************
* Function Name  :BSP_writeFlash(uint32_t UL_address, uint32_t* UL_data, uint32_t UL_size)
*
* Abstract    : This function writes to the memory
*
* Requiremnet Traceability :
*
* Function Parameters:
* 					UL_address: This describes the address that you want to change memory
*					UL_data : The data that to be written in the flash memory
*					UL_size : The size of the data
* Return Value :  It does not return any value.
*Function Design:
 * step1 :It Unlocks the Flash to be written
 * step2 :It flashes the data into the memory
 * step3 :It locks the Flash
***************************/
void BSP_WriteFlash(uint32_t UL_address, uint32_t* UL_data, uint32_t UL_size){
    HAL_FLASH_Unlock();

    for (uint32_t i = 0; i < UL_size; i++) {

        HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, UL_address + i * 4, *(uint64_t*)&UL_data[i]);
    }

    HAL_FLASH_Lock();

}

/***************************
* Function Name  :BSP_ReadInternalFlash(uint32_t UL_address ,uint32_t UL_data[4])
*
* Abstract    : This function reads to the memory
*
* Requiremnet Traceability :
*
* Function Parameters:
* 					UL_address: This describes the address that you want to read
*					UL_data : The data that to be read in the flash memory
* Return Value :  It does not return any value.
*Function Design:
 * step1 :It Unlocks the Flash to be written
 * step2 :It reads the data from the address
 * step3 :It locks the Flash
***************************/
void BSP_ReadInternalFlash(uint32_t UL_address ,uint32_t UL_data[4]) {
    HAL_Init();
    HAL_FLASH_Unlock();
    for (int i = 0; i < 4; i++) {
        UL_data[i] = *(__IO uint32_t*)(UL_address + i * 4);
    }

    HAL_FLASH_Lock();
}


