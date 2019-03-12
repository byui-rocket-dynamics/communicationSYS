// #include <wiringPiSPI.h>
#include <stdlib.h>
#include <stdio.h>
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

const unsigned char AT_SERIAL_COMM[7][3] = {
   "BD",/*Baud Rate*/               "NB",/*Parity Bit*/
   "SB",/*Stop Bits*/               "RO",/*Packetization Timeout*/
   "FT",/*Flow Control Treshold*/   "AP",/*API Mode*/
   "AO",/*API Options*/ 
};

const unsigned char AT_DIOGNOSTIC_COMM[5][3] = {
   "BC",/*Bytes Transmitted*/      "DB",/*dB Query of Last Packet*/
   "ER",/*Error Count*/            "GD",/*Good Packets Received*/
   "TR",/*Transmission Failure Count*/
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

void TX(Packet *packet, char *data[])
{
   packet->frameType = TX_REQ;
   addData(packet, data);
   calcLength(packet, data);
   calcChecksum(data, packet);
   packetPrint(packet);
}

void AT(Packet *packet, unsigned char *command[], LinkedList *parameterVal)
{
   packet->frameType = AT_COMM_SEND;
   push_front(parameterVal, command[1]);
   push_front(parameterVal, command[0]);
   packet->lenMSB = parameterVal->lenMSB;
   packet->lenLSB = parameterVal->lenLSB;
}

void ATQ(Packet *packet, unsigned char *command, LinkedList *parameterVal)
{
   packet->frameType = AT_COMM_SEND;
   push_front(parameterVal, command);
   packet->lenMSB = parameterVal->lenMSB;
   packet->lenLSB = parameterVal->lenLSB;
}

void calcLength(Packet *packet, char *data[])
{
   short length = (short) sizeof(data);
   packet->lenMSB = (length >> 8) & 0xFF;
   packet->lenLSB = length & 0xFF;
}

void addData(Packet *packet, char *data[])
{
   for(int i = 0; data[i] != '\0'; i++)
      push_back(&packet->data, (unsigned char *) data[i]);
}

void calcChecksum(char *data[], Packet *packet){
   unsigned char num;
   for(int i = 0; data[i] != '\0'; i++)
      num += *data[i];
   
   num += packet->lenLSB;
   num += packet->lenMSB;
   num += packet->startByte;
   num += packet->frameType;
   packet->checksum = 0xFF - num;
}

void packetPrint(Packet *packet){ 
   printf("%h %h%h %h ", packet->startByte, packet->lenMSB, packet->lenLSB, packet->frameType);
   printList(&packet->data);
   printf(" %h", packet->checksum);
}

