/*
 *  Custom Reaper Class
 *  Author: Scott Susanto
 */

#include <iostream>

#include "my_reaper.h"
#include "my_utils.h"

void reap_threads(vector<shared_ptr<Connection>> *conns)
{
    while (true)
    {
        shared_ptr<Connection> conn = wait_to_reap();
        if (conn == NULL)
            break;

        mut.lock();
        int conn_number = conn->get_conn_number();
        for (vector<shared_ptr<Connection>>::iterator itr = conns->begin(); itr != conns->end();)
        {
            shared_ptr<Connection> conn = (*itr);
            if (conn->get_conn_number() == conn_number)
            {
                conn->get_reader_thread()->join();
                conn->get_writer_thread()->join();
                log("Socket-reading thread has joined with socket-writing thread");

                itr = conns->erase(itr);
            }
            else
                itr++;
        }
        mut.unlock();
    }

    while (true)
    {
        mut.lock();
        if (server_socketfd == -1 && conns->empty())
        {
            mut.unlock();
            log("Reaper has joined with connection thread.");
            return;
        }

        for (vector<shared_ptr<Connection>>::iterator itr = conns->begin(); itr != conns->end();)
        {
            shared_ptr<Connection> conn = (*itr);
            if (conn->get_curr_socketfd() == -2)
            {
                conn->get_reader_thread()->join();
                conn->get_writer_thread()->join();
                log("Socket-reading thread has joined with socket-writing thread");

                itr = conns->erase(itr);
            }
            else
                itr++;
        }
        mut.unlock();
    }
}

void reap_thread(shared_ptr<Connection> conn)
{
    mut.lock();
    reaper_q.push(conn);
    reaper_cv.notify_one();
    mut.unlock();
}

shared_ptr<Connection> wait_to_reap()
{
    unique_lock<mutex> lock(mut);
    while (reaper_q.empty())
        reaper_cv.wait(lock);

    shared_ptr<Connection> conn = reaper_q.front();
    reaper_q.pop();
    return conn;
}
