#include <stdio.h>
#include <string.h>
#include "ComPort.h"
#include "../MeComAPI/MePort.h"

//added for SysStrToCharStr
#include <windows.h>
#pragma comment( lib, "winmm.lib" ) 
#include <msclr\marshal.h>


using namespace System;
#using "System.dll"

static void ComPort_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e);
static void WriteDataToDebugFile(char *prefix, char *in) ;
static void SysStrToCharStr(char *Dest, System::String ^Src, unsigned int maxSize);

ref class ComPortGlobal
{
    public: static System::IO::Ports::SerialPort^ serialPort1;
};


void ComPort_Open(int PortNr, int Speed)
{
    ComPortGlobal::serialPort1 = gcnew System::IO::Ports::SerialPort();
    ComPortGlobal::serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(ComPort_DataReceived);
    ComPortGlobal::serialPort1->BaudRate = Speed;
    switch(PortNr)
    {
        case  1: ComPortGlobal::serialPort1->PortName = "COM1"; break;
        case  2: ComPortGlobal::serialPort1->PortName = "COM2"; break;
        case  3: ComPortGlobal::serialPort1->PortName = "COM3"; break;
        case  4: ComPortGlobal::serialPort1->PortName = "COM4"; break;
        case  5: ComPortGlobal::serialPort1->PortName = "COM5"; break;
        case  6: ComPortGlobal::serialPort1->PortName = "COM6"; break;
        case  7: ComPortGlobal::serialPort1->PortName = "COM7"; break;
        case  8: ComPortGlobal::serialPort1->PortName = "COM8"; break;
        case  9: ComPortGlobal::serialPort1->PortName = "COM9"; break;
        case 10: ComPortGlobal::serialPort1->PortName = "COM10"; break;
        case 11: ComPortGlobal::serialPort1->PortName = "COM11"; break;
        case 12: ComPortGlobal::serialPort1->PortName = "COM12"; break;
        case 13: ComPortGlobal::serialPort1->PortName = "COM13"; break;
        case 14: ComPortGlobal::serialPort1->PortName = "COM14"; break;
        case 15: ComPortGlobal::serialPort1->PortName = "COM15"; break;
        case 16: ComPortGlobal::serialPort1->PortName = "COM16"; break;
        case 17: ComPortGlobal::serialPort1->PortName = "COM17"; break;
        case 18: ComPortGlobal::serialPort1->PortName = "COM18"; break;
        case 19: ComPortGlobal::serialPort1->PortName = "COM19"; break;
        case 20: ComPortGlobal::serialPort1->PortName = "COM20"; break;
        case 21: ComPortGlobal::serialPort1->PortName = "COM21"; break;
        case 22: ComPortGlobal::serialPort1->PortName = "COM22"; break;
        case 23: ComPortGlobal::serialPort1->PortName = "COM23"; break;
        case 24: ComPortGlobal::serialPort1->PortName = "COM24"; break;
        case 25: ComPortGlobal::serialPort1->PortName = "COM25"; break;
        case 26: ComPortGlobal::serialPort1->PortName = "COM26"; break;
        case 27: ComPortGlobal::serialPort1->PortName = "COM27"; break;
        case 28: ComPortGlobal::serialPort1->PortName = "COM28"; break;
        case 29: ComPortGlobal::serialPort1->PortName = "COM29"; break;
        case 30: ComPortGlobal::serialPort1->PortName = "COM30"; break;
        case 31: ComPortGlobal::serialPort1->PortName = "COM31"; break;
        case 32: ComPortGlobal::serialPort1->PortName = "COM32"; break;
        case 33: ComPortGlobal::serialPort1->PortName = "COM33"; break;
        case 34: ComPortGlobal::serialPort1->PortName = "COM34"; break;
        case 35: ComPortGlobal::serialPort1->PortName = "COM35"; break;
        case 36: ComPortGlobal::serialPort1->PortName = "COM36"; break;
        case 37: ComPortGlobal::serialPort1->PortName = "COM37"; break;
        case 38: ComPortGlobal::serialPort1->PortName = "COM38"; break;
        case 39: ComPortGlobal::serialPort1->PortName = "COM39"; break;
        case 40: ComPortGlobal::serialPort1->PortName = "COM40"; break;
        case 41: ComPortGlobal::serialPort1->PortName = "COM41"; break;
        case 42: ComPortGlobal::serialPort1->PortName = "COM42"; break;
        case 43: ComPortGlobal::serialPort1->PortName = "COM43"; break;
        case 44: ComPortGlobal::serialPort1->PortName = "COM44"; break;
        case 45: ComPortGlobal::serialPort1->PortName = "COM45"; break;
        case 46: ComPortGlobal::serialPort1->PortName = "COM46"; break;
        case 47: ComPortGlobal::serialPort1->PortName = "COM47"; break;
        case 48: ComPortGlobal::serialPort1->PortName = "COM48"; break;
        case 49: ComPortGlobal::serialPort1->PortName = "COM49"; break;
        case 50: ComPortGlobal::serialPort1->PortName = "COM50"; break;
        default: return;
    }
    try
    {
        ComPortGlobal::serialPort1->Open();
        printf("ComPort Opened!\n");
    }
    catch(...)
    {
        printf("ComPort opening faild!\n");
    }
    
}
void ComPort_Close(void)
{
    ComPortGlobal::serialPort1->Close();
}

void ComPort_Send(char *in)
{
    WriteDataToDebugFile("OUT: ", in);
    String^ str = System::Runtime::InteropServices::Marshal::PtrToStringAnsi(IntPtr((void*)in));

    try { ComPortGlobal::serialPort1->Write(str); } catch(...) { }
}

void ComPort_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) 
{
    String ^RcvData = ComPortGlobal::serialPort1->ReadExisting();
    //Console::Write("Data Received:" + RcvData);

    char RcvBuffer[1000];
    SysStrToCharStr(RcvBuffer, RcvData, sizeof(RcvBuffer));

    WriteDataToDebugFile("IN:  ", RcvBuffer);
    MePort_ReceiveByte((int8_t*)RcvBuffer);
}

static void WriteDataToDebugFile(char *prefix, char *in) 
{
    // int i = 100;
    // while(1)
    // {
    //     try
    //     {
    //         System::IO::StreamWriter ^ sr = gcnew System::IO::StreamWriter("ComLog.txt", true);
    //         sr->Write(gcnew String(prefix));
    //         sr->Write(gcnew String(in));
    //         sr->Write("\r\n");
    //         sr->Close();
    //         break;
    //     }
    //     catch(...) 
    //     {
    //         Sleep(10); 
    //         if(i>0) i--; 
    //         else 
    //         {
    //             printf("Writing to Debug File not possible!\n"); 
    //             return;
    //         }
    //     }
    // }
    
}

static void SysStrToCharStr(char *Dest, System::String ^Src, unsigned int maxSize)
{
   
   pin_ptr<const wchar_t> wch = PtrToStringChars(Src);
   size_t convertedChars = 0;
   size_t  sizeInBytes = ((Src->Length + 1) * 2);
   char    *ch = (char *)malloc(sizeInBytes);
   wcstombs_s(&convertedChars, ch, sizeInBytes, wch, sizeInBytes);
   convertedChars--;
   maxSize--;
   while((convertedChars > 0) && (maxSize > 0)) 
   {
       *Dest = *ch; 
       Dest++; 
       ch++; 
       maxSize--;
       convertedChars--;
   }
   *Dest = 0;

}
