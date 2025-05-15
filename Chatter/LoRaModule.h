#ifndef __LORAMODULE_H__
#define __LORAMODULE_H__

#include <SPI.h>
#include <LoRa.h>

/*
  Declare all the constant and default values
*/
#define DEVICE_ID '0'               //Device ID in case you want more than one chatter
#define MAX_PACKET 255              //Max size of a packet to be sent
#define HISTORY_SIZE 8  

/*------------LoRa default values------------------*/
#define FREQUENCY 433E6             //Frecuency of the radio waves used (depends on your device)
#define BAND_WIDTH 125E3            //Default bandwidth of the signal
#define SPREADING_FACTOR 7          //Default spreading factor of the signal
#define CODING_RATE_DENOMINATOR 5   //It means that for each 4 bytes sended 5-4=1 bytes are redundant
#define TX_POWER 20                 //Default transmission power
//#define LNA_GAIN 0

//Password for encoding the messages
const byte PASSWORD[255] = {
   51,170, 25,120,179,241, 43, 10,157,238,156, 90,114,  0,116, 43,
   40,211, 76,159, 23,255,158,175,190,163,145,172,205,123, 63, 75,
  251,157,244, 18,150,205,210,119, 77, 43,159, 70, 70,135, 91,150,
  102,161,165, 53, 19, 38,156, 40,108, 55,125,157,  2,127,185, 99,
   78,110,254, 86, 63,103,  1, 52,  0,  0,174,186, 93,  5, 71,133,
  132,119,111,174,112,220,234, 70, 21,154, 39, 88,  2,219,140,123,
  140,214,145, 64,201, 91,170,227, 31,152,157, 14,173,163,193,180,
  157, 83,151,184,164, 16, 13,  8,181,229, 13,123,221,207,214,213,
  111,179, 45, 39, 99, 94, 73,167,189, 74, 65, 45,109, 97,143, 60,
  216,176,235, 28,166,225,168,112, 22,161, 64,145,241, 87,101,235,
  108, 61,168,168,199, 38,150,127,155, 19, 46, 91, 31,107,224,221,
    4,133,  3, 33,123,226, 14,249, 60,167,151, 61,130,223,192, 49,
  169,225,210,173, 66,236,249,143, 76, 23,135,133, 87,190,237,164,
   99, 90, 91, 21,225,182, 76, 39,219,104,168, 91,201, 16,157,138,
  130, 15,126,154,221,231,188,252,198,167,  1,  3,115,120,225,102,
   90,239,211, 91,159,222,203,219, 34,165,213, 22,225,152,182
};

class LoRaModule{
private:
  //Count of all the messages received
  unsigned long messagesReceived = 0;

  /*
  Package data for the last HISTORY_SIZE messages.
  They are used to optimize the gain, spreading factor and coding rate.
  */
  int previousRSSI[HISTORY_SIZE];
  int previousSNR[HISTORY_SIZE];
  int previousError[HISTORY_SIZE];
  byte size;

  /*
  Variables to store the current parameters for the signal.
  They are modified to ensure the optimal transmission of the message.
  */
  int _bandWidth = BAND_WIDTH;
  int _spreadingFactor = SPREADING_FACTOR;
  int _codingRateDenominator = CODING_RATE_DENOMINATOR;
  //int lnaGain = LNA_GAIN;

  //Functions to optimize the transmission if the message based on the data collected.

  /**
    @brief A function to get the average of v
    @param v the vector containing the values
    @return the average of the values in v
  */
  float GetAverage(const int* v);

  /**
    @brief Function to optimize the signal based on the RSSI data
  */
  void OptimizeRSSI();

  /**
    @brief Function to optimize the signal based on the SNR data
  */
  void OptimizeSNR();

  /**
    @brief Function to optimize the signal based on the error rate data
  */
  void OptimizeError();

  /**
    @brief Function to encode the password
  */
  void Encrypt(unsigned char* buffer, byte size);

  /**
    @brief decode de message based on the password shared
  */
  void Decrypt(char* buffer, byte size);


public:
  //flag to store if a message has been received and not read
  static bool messagePending;

  /**
    @brief The class constructor
    @param spi the spi interface to use
  */
  LoRaModule(SPIClass &spi);

  /**
    @brief The class constructor
  */
  ~LoRaModule();

  /**
    @brief Optimize the signal based on the data received (assuming the other device is in the same condition)
  */
  void Optimize();

  /**
    @brief Send a message through the LoRa module
    @param buffer a buffer containing the message to send
    @param size size of the message to send
    @return true if the message was successfully sent and false otherwise
  */
  bool SendMessage(const char* buffer, byte size);

  /**
    @brief Check if there is a message to be received
    @return true if a message was found and false otherwise
  */
  bool MessagePending();

  /**
    @brief Receive a message through the LoRa module
    @param buffer the buffer where the message will be stored
    @return the size of the message in bytes
  */
  byte ReceiveMessage(char* buffer);

  /**
    @brief Puts radio in sleep mode
  */
  void Sleep();

  /**
    @brief Puts radio in idle mode
  */
  void Idle();
};

/**
 @brief Activates the transmission mode of the radio
*/
void TXMode();

/**
  @brief Activates the receive mode of the radio
*/
void RXMode();

/**
  @brief Interrupt function to reactivate the receive mode after a massage has been sent
*/
void onTxDone();

/**
  @brief Interrupt function to activate a flag when a message has been received
*/
void onReceive(int packetSize);

#endif