// #include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

#define START_BYTE               0x7E

// API IDs to send to xBee
#define AT_COMM_SEND             0x08
#define AT_COMM_SENDQ            0x09
#define TX_REQ                   0x10
#define TX_REQ_EXP               0x11
#define REMOTE_COMM              0x17

// API IDs to receive from xBee
#define AT_COMM_RESP             0x88
#define MODEM_STAT               0x8A
#define TRANSMIT_STAT            0x8B
#define ROUTE_PACKET             0x8D
#define AGRGTE_ADDR_UPDATE_FRAME 0x8E
#define RX_IND                   0x90
#define RX_IND_EXP               0x91
#define RX_DATA_SAMPLE           0x92
#define NODE_IDENTFY             0x95
#define REMOTE_COM_RESP          0x97

//Transmit Options
#define ADDRESS                  0xFFFFFFFE //Last 4 nibbles need to be 0xFFFE (Reserved)
#define RADIUS                   0x00
#define TRANS_OPTION             0x00

const unsigned char AT_SERIAL_COMM[7][2] = {
   "BD" /*Baud Rate*/,              "NB" /*Parity Bit*/,
   "SB" /*Stop Bits*/,              "RO" /*Packetization Timeout*/
   "FT" /*Flow Control Treshold*/,  "AP" /*API Mode*/,
   "AO" /*API Options*/ 
};

const unsigned char AT_DIOGNOSTIC_COMM[5][2] = {
   "BC" /*Bytes Transmitted*/,      "DB" /*dB Query of Last Packet*/,
   "ER" /*Error Count*/,            "GD" /*Good Packets Received*/,
   "TR" /*Transmission Failure Count*/
};

typedef struct Packet
{
   unsigned char startByte;
   unsigned char lenMSB;
   unsigned char lenLSB;
   unsigned char frameType;
   LinkedList data;
   unsigned char checksum;
}Packet;

void TX(Packet *packet, LinkedList *data)
{
   packet->frameType = TX_REQ;
   packet->lenMSB = data->lenMSB;
   packet->lenLSB = data->lenLSB;
   
}

void AT(Packet *packet, unsigned char command[], LinkedList *parameterVal)
{
   packet->frameType = AT_COMM_SEND;
   push_front(parameterVal, command[1]);
   push_front(parameterVal, command[0]);
   packet->lenMSB = parameterVal->lenMSB;
   packet->lenLSB = parameterVal->lenLSB;
}

void ATQ(Packet *packet, unsigned char command, LinkedList *parameterVal)
{
   packet->frameType = AT_COMM_SEND;
   push_front(parameterVal, command);
   packet->lenMSB = parameterVal->lenMSB;
   packet->lenLSB = parameterVal->lenLSB;
}

