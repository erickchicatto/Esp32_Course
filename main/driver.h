#ifndef DRIVER_H_
#define DRIVER_H_

#include <stdbool.h>
#include <stdint.h>

#include "spi.h"

/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
*******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif


/**Number of outputs available in the L9733 chip*/
#define L9733_OUTPUT_NUM        (8)
/**Keyword used in the command register*/
#define L9733_CMD_KEYWORD       (0b1010 << 12)
/**Nibble used to set the writing mode to output in the command register*/
#define L9733_CMD_WM_OUTPUT     (0b1100 << 8)
/**Nibble used to set the writing mode to diagnostic in the command register*/
#define L9733_CMD_WM_DIAG       (0b0011 << 8)
/**Nibble used to set the writing mode to protection in the command register*/
#define L9733_CMD_WM_PROTECT    (0b1010 << 8)


/**Command registers */
/** OUT1 bit in command register */
#define L9733_OUT1_BIT (1 << 0)
/** OUT2 bit in command register */
#define L9733_OUT2_BIT (1 << 1)
/** OUT3 bit in command register */
#define L9733_OUT3_BIT (1 << 2)
/** OUT4 bit in command register */
#define L9733_OUT4_BIT (1 << 3)
/** OUT5 bit in command register */
#define L9733_OUT5_BIT (1 << 4)
/** OUT6 bit in command register */
#define L9733_OUT6_BIT (1 << 5)
/** OUT7 bit in command register */
#define L9733_OUT7_BIT (1 << 6)
/** OUT8 bit in command register */
#define L9733_OUT8_BIT (1 << 7)

/**Types of results from the flight management systems(FMS)*/
typedef enum{
   FMS_RSLT_CMD_COMPLETE = 1, //!< Command complete
   FMS_RSLT_CMD_FAILED = 2,    //!< Command failed
}fsm_rslt_t;

/**Types of fault status from the L9733 chip*/
typedef enum {
    L9733_OK = 0, //!< No fault is present
    L9733_OPEN_LOAD = 1 , //!< Open load 
    L9733_SHORT_CIRCUIT = 2, //!< Short circuit to GND (low-side) or short
    L9733_OVERCURRENT = 3,  //!< Overcurrent
}l9733_fault_status_t;

/**@Brief L9711 Object*/
typedef struct {
    spi_t *bus; //!< The SPI object to use for interfacing with the chip
    uint8_t id; //!< The L9733 ID number
    uint8_t output; //!< The output status value
    uint8_t diag_mode; //!< The diagnostic mode value
    uint8_t protection ; //!< The overcurrent 
    l9733_fault_status_t fault[L9733_OUTPUT_NUM]; //!< The fault status of outputs 1-8
    bool thermal_fault; //!< This flag is set when a thermal fault occurs
}l9733_t;

/**Sets output 1-8 ON or OFF*/
fms_rslt_t l9733_set_output(l9733_t *obj);

/**Set the diagnostic mode on outputs 1-8 to "Latch Mode" or "No Latch Mode"*/
fms_rslt_t l9733_set_diag_mode(l9733_t *obj);

/**Set the overcurrent protection on outputs 1-8 ON or OFF*/
fms_rslt_t l9733_set_protection(l9733_t *obj);

/**Get the fault diagnostic of outputs 1-8*/
fms_rslt_t l9733_get_fault_diag(l9733_t *obj);




/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
*******************************************************************************/
#if defined(__cplusplus)
}
#endif

#endif  // L9733_H_









