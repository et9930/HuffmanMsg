#pragma once
#define MYCOPYDATA WM_USER+1
class Communication
{
public:
	Communication();
	~Communication();
	void setSendMsg(FileList Msg);
	void SendMsg();
	void ReceiveMsg();
private:
	FileList SentMsg;
	FileList ReceivedMsg;
	COPYDATASTRUCT MyCDS;
	PCOPYDATASTRUCT pMyCDS;
};

