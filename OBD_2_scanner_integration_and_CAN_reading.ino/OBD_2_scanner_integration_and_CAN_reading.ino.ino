/*
 * Demo: CAN-BUS Shield, receive all frames and print all fields id/type/data.
 * This code is designed to work with a CAN-BUS Shield using the MCP2515 CAN controller.
 * It sets up the CAN-BUS interface, listens for incoming CAN frames, and prints each frame's ID, type, and data payload to the serial monitor.
 * To receive frames quickly, polling in the loop() function is employed.
 * 
 * Author: Ahmed Abdelghany <ahmedabdelghany15@gmail.com> 2024.
 */

#include <SPI.h> // Include SPI library for SPI communication

#define CAN_2515 // Define to use MCP2515 CAN controller

// Set SPI CS (Chip Select) Pin according to your hardware
const int SPI_CS_PIN = 9; // Use digital pin 9 for the SPI CS
const int CAN_INT_PIN = 2; // Interrupt pin set to digital pin 2

#include "mcp2515_can.h" // Include the library specific to the MCP2515 CAN controller
mcp2515_can CAN(SPI_CS_PIN); // Create an instance of the CAN class, specifying the Chip Select pin
#define MAX_DATA_SIZE 8 // Maximum data size for standard CAN frames

void setup() {
    SERIAL_PORT_MONITOR.begin(115200); // Start serial communication at 115200 baud rate
    while (!SERIAL_PORT_MONITOR) {} // Wait for the serial port to connect. Needed for native USB

    // Initialize the CAN interface with a baud rate of 500Kbps.
    // If initialization fails, print a message and retry until it succeeds.
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
        SERIAL_PORT_MONITOR.println(F("CAN init fail, retry..."));
        delay(100); // Wait 100ms before retrying
    }
    SERIAL_PORT_MONITOR.println(F("CAN init ok!")); // Indicate successful CAN initialization
}

// Variables to store incoming CAN frame information
uint32_t id;
uint8_t  type; // Stores frame properties: bit0 - extended frame, bit1 - remote transmission request
uint8_t  len; // Data length
byte cdata[MAX_DATA_SIZE] = {0}; // Data buffer

void loop() {
    // Check if a new CAN message is available
    if (CAN_MSGAVAIL != CAN.checkReceive()) {
        return; // If no new message, exit loop iteration early
    }

    // Buffer to hold the formatted incoming data for serial output
    char prbuf[32 + MAX_DATA_SIZE * 3];
    int i, n;

    // Fetch and format the current time since program start
    unsigned long t = millis();
    n = sprintf(prbuf, "%04lu.%03d ", t / 1000, int(t % 1000));

    // Read the incoming message and store its ID and type
    CAN.readMsgBuf(&len, cdata); // Read data: len = data length, cdata = data buffer
    id = CAN.getCanId();
    type = (CAN.isExtendedFrame() << 0) | (CAN.isRemoteRequest() << 1);

    // Format message type and ID for serial output
    static const byte type2[] = {0x00, 0x02, 0x30, 0x32};
    n += sprintf(prbuf + n, "RX: [%08lX](%02X) ", (unsigned long)id, type2[type]);

    // Append each byte of the CAN frame data to the output buffer
    for (i = 0; i < len; i++) {
        n += sprintf(prbuf + n, "%02X ", cdata[i]);
    }
    // Print the formatted data to the serial monitor
    SERIAL_PORT_MONITOR.println(prbuf);
}
