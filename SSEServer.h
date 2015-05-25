#ifndef SERVER_H
#define SERVER_H
#include "SSEConfig.h"
#include "SSEChannel.h"
#include <glog/logging.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <signal.h>
#include <errno.h>

#define MAXEVENTS 1024

extern int stop;

typedef vector<SSEChannel*> SSEChannelList;

class SSEServer {
  public:
    SSEServer(SSEConfig*);
    ~SSEServer();
    void run();
    static void *routerThreadMain(void *);
    string getUri(const char *);

  private:
    SSEConfig *config;
    SSEChannelList channels;
    int serverSocket;
    int efd;
    struct epoll_event *eventList;
    struct sockaddr_in sin;
    pthread_t routerThread;
    void initSocket();
    void initChannels();
    void acceptLoop();
    void clientRouterLoop();
    SSEChannel* getChannel(string id);
};

#endif