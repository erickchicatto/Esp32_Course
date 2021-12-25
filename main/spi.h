#ifndef SPI_H_
#define SPI_H_


#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
 *******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief SPI is like object?
 */

typedef struct {
  uint8_t mode;
  bool msb_first;
  uint64_t tx_buf;
  uint64_t rx_buf;
  uint32_t speed_hz;
  bool full_duplex;
}spi_t;


/*******************************************************************************
 * Simplifies integration with automated testing frameworks in C++ (i.e. gtest)
 *******************************************************************************/
#if defined(__cplusplus)
}
#endif

#endif  // SPI_H_