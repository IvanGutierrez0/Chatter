#ifndef __LORAMODULE_H__
#define __LORAMODULE_H__

#include <SPI.h>
#include <LoRa.h>

/*
  Declare all the constant and default values
*/
#define MAX_PACKET 255              //Max size of a packet to be sent
#define BUFFER_COLS 32              //Max message size
#define BUFFER_ROWS 16              //Maxx capacitiy for the buffer

/*----------------------Pinout----------------------*/
#define CS 5				//Chip select pin
#define RST 21			//Reset pin
#define DIOO 2			//Interrupt pin

/*------------Radio default values------------------*/
#define FREQUENCY 433E6             //Frecuency of the radio waves used (depends on your device)
#define BAND_WIDTH 125E3            //Default bandwidth of the signal
#define SPREADING_FACTOR 7          //Default spreading factor of the signal
#define CODING_RATE_DENOMINATOR 5   //It means that for each 4 bytes sended 5-4=1 bytes are redundant
#define TX_POWER 20                 //Default transmission power
//#define LNA_GAIN 0

class LoRaModule {
private:
  //Reference to the current SPI interface
  SPIClass &_spi;

  //Received packet size
  inline static volatile byte packetSize[BUFFER_ROWS];

  //Number of messages waiting to be read
  inline static volatile byte messagesPending = 0;

  //Buffer 
  inline static volatile unsigned char _buffer[BUFFER_ROWS][BUFFER_COLS];

public:
	/**
    @brief The class constructor
    @param spi the spi interface to use
  */
  LoRaModule(SPIClass &spi);

  /**
    @brief The class destructor
  */
  ~LoRaModule();

  /**
  	@brief Initializes both the SPI interface and the LoRa module
  */
  bool begin();

  /**
    @brief Send a message through the LoRa module
    @param buffer a buffer containing the message to send
    @param size size of the message to send
    @return true if the message was successfully sent and false otherwise
  */
  bool SendMessage(const unsigned char* buffer, byte size);

  /**
    @brief Check if there is a message to be received
    @return true if a message was found and false otherwise
  */
  byte MessagePending();

  /**
    @brief Receive a message through the LoRa module
    @param buffer the buffer where the message will be stored
    @return the size of the message in bytes
  */
  byte ReceiveMessage(unsigned char* buffer);

  /**
    @brief Puts radio in idle mode
  */
  void Idle();

  /**
    @brief Puts radio in sleep mode
  */
  void Sleep();

	/**
		@brief Activates the transmission mode of the radio
	*/
	void TXMode();

	/**
	  @brief Activates the receive mode of the radio
	*/
	void RXMode();

  /**
    @brief Callback funtion for a newly arrived message
    @param size Number of characters on the message
  */
  static void onReceive(int size);
};

#endif