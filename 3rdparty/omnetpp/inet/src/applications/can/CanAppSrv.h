/*
 * Copyright (C) 2013 Embedded and Real-Time Systems Laboratory
 *             Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Modified by Matteo Morelli, ReTiS Lab., Scuola Superiore Sant'Anna, Pisa, Italy
 * email: matteo.morelli@sssup.it
 *
 *          - added the function 'int guessMessageID(int)'
 *          It's a member function that takes the ID of a can message (represented
 *          as int, ie., a 'key' for the SendMessageInfoList map) and returns the ID of
 *          the message represented in the SendMessageInfo struct (the 'value' in the
 *          SendMessageInfoList map that corresponds to that 'key')
 *          This member function is used within the TRES framework:
 *          http://retis.sssup.it/tres/
 */

#ifndef __INET_CANAPPSRV_H
#define __INET_CANAPPSRV_H

#include "INETDefs.h"
#include "CanFrame_m.h"
#include <map>

class INET_API CanAppSrv : public cSimpleModule
{
  protected:
	struct SendMessageInfo{
		int ID;
		int DLC;
		double SendInterval;
		std::vector<double> SendTime;
		double Offset;
	};
	std::map<int,SendMessageInfo> SendMessageInfoList; // key: message ID, value: infomation of a sending message

	// send parameters
    cPar *sendInterval;
    double sendIntervaldouble;
    int messageID;
    std::vector<double> sendTimeList;
    int numsendTime;
    double drift;

    // self messages
    cMessage *sendReqMsg;

    // statistics
    long packetsSent;
    long packetsReceived;
    static simsignal_t sentPkSignal;
    static simsignal_t rcvdPkSignal;

  public:
    CanAppSrv();
    ~CanAppSrv();
    // start modification
    virtual int guessMessageID(int mid)
    {
        std::map<int,SendMessageInfo>::iterator itr = SendMessageInfoList.find(mid);
	    return(itr->second.ID);
    }
    // end modification

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void sendMessage(CanFrame *msg);
    virtual void finish();

 private:
	void handleSelfSendRequest(int MessageID);
	void handleCanMessage(cMessage *msg);
	unsigned long ToDec(const char str[ ]);
};

#endif
