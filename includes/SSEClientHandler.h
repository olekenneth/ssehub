#ifndef SSECLIENTHANDLER_H
#define SSECLIENTHANDLER_H

#include <string>
#include <pthread.h>
#include <deque>
#include <boost/shared_ptr.hpp>

using namespace std;

// Forward declarations.
class SSEClient;

typedef boost::shared_ptr<SSEClient> SSEClientPtr;
typedef vector<SSEClientPtr> SSEClientPtrList;
typedef deque<std::string> MessageQueue;

class SSEClientHandler {
  public:
    SSEClientHandler(int);
    ~SSEClientHandler();

    bool AddClient(class SSEClient* client);
    bool RemoveClient(SSEClient* client);
    long GetNumClients();
    void Broadcast(const string msg);
    void AsyncBroadcast(const string msg);
  
  private:
    int id;
    int epoll_fd;
    long num_clients;
    pthread_t cleanup_thread;
    SSEClientPtrList client_list;

    static void* CleanupMain(void* pThis);
    void CleanupMainFunc();
    static void* AsyncBroadcastFunc(void* mp);
};

#endif
