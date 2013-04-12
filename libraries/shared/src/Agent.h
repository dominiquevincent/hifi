//
//  Agent.h
//  hifi
//
//  Created by Stephen Birarda on 2/15/13.
//  Copyright (c) 2013 High Fidelity, Inc. All rights reserved.
//

#ifndef __hifi__Agent__
#define __hifi__Agent__

#include <iostream>
#include <stdint.h>
#include "AgentData.h"
#include <pthread.h>

#ifdef _WIN32
#include "Syssocket.h"
#else
#include <sys/socket.h>
#endif

class Agent {
    void swap(Agent &first, Agent &second);
    sockaddr *publicSocket, *localSocket, *activeSocket;
    char type;
    uint16_t agentId;
    double firstRecvTimeUsecs;
    double lastRecvTimeUsecs;
    AgentData *linkedData;
    
public:    
    Agent();
    Agent(sockaddr *agentPublicSocket, sockaddr *agentLocalSocket, char agentType, uint16_t thisAgentId);
    Agent(const Agent &otherAgent);
    ~Agent();
    Agent& operator=(Agent otherAgent);
    bool operator==(const Agent& otherAgent);
    
    bool matches(sockaddr *otherPublicSocket, sockaddr *otherLocalSocket, char otherAgentType);
    
    pthread_mutex_t deleteMutex;
    
    char getType() const;
    const char* getTypeName() const;
    void setType(char newType);
    uint16_t getAgentId();
    void setAgentId(uint16_t thisAgentId);
    double getFirstRecvTimeUsecs();
    void setFirstRecvTimeUsecs(double newTimeUsecs);
    double getLastRecvTimeUsecs();
    void setLastRecvTimeUsecs(double newTimeUsecs);
    sockaddr* getPublicSocket();
    void setPublicSocket(sockaddr *newSocket);
    sockaddr* getLocalSocket();
    void setLocalSocket(sockaddr *newSocket);
    sockaddr* getActiveSocket();
    void activatePublicSocket();
    void activateLocalSocket();
    AgentData* getLinkedData();
    void setLinkedData(AgentData *newData);

    friend std::ostream& operator<<(std::ostream& os, const Agent* agent);       
};

std::ostream& operator<<(std::ostream& os, const Agent* agent);

#endif /* defined(__hifi__Agent__) */
