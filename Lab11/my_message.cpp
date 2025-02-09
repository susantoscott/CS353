/*
 *  Custom Message Class
 *  Author: Scott Susanto
 */

#include "my_message.h"

Message::Message()
{
    this->ok = false;
    this->should_terminate = false;

    this->status_code = 501;
    this->file_path = "";
    this->md5_hash = "";

    this->origin_nodeid = "";
    this->content_len = 0;
}

Message::Message(bool should_terminate)
{
    this->ok = false;
    this->should_terminate = should_terminate;

    this->status_code = 501;
    this->file_path = "";
    this->md5_hash = "";

    this->origin_nodeid = "";
    this->content_len = 0;
}

Message::Message(int status_code, string file_path, string md5_hash)
{
    this->ok = true;
    this->should_terminate = false;

    this->status_code = status_code;
    this->file_path = file_path;
    this->md5_hash = md5_hash;

    this->is_http = true;
    this->origin_nodeid = "";
}

Message::Message(string origin_nodeid, int content_len)
{
    this->ok = true;
    this->is_http = false;
    this->should_terminate = false;

    this->status_code = 0;
    this->file_path = "";
    this->md5_hash = "";

    this->hello = true;
    this->origin_nodeid = origin_nodeid;
    this->content_len = content_len;
}

Message::Message(int ttl, int flood_reason, string message_id, string sender_nodeid, string origin_nodeid, string origin_start_time, string message_body, int net_content_len)
{
    this->ok = true;
    this->is_http = false;
    this->should_terminate = false;

    this->status_code = 0;
    this->file_path = "";
    this->md5_hash = "";

    this->hello = false;
    this->ttl = ttl;
    this->flood_reason = flood_reason;
    this->message_id = message_id;
    this->sender_nodeid = sender_nodeid;
    this->origin_nodeid = origin_nodeid;
    this->origin_start_time = origin_start_time;
    this->message_body = message_body;
    this->net_content_len = net_content_len;
}

Message::Message(string neighbor_nodeid, shared_ptr<Message> old_message)
{
    this->ok = true;
    this->is_http = false;
    this->should_terminate = false;

    this->status_code = 0;
    this->file_path = "";
    this->md5_hash = "";

    this->hello = false;
    this->ttl = old_message->get_ttl();
    this->flood_reason = old_message->get_flood_reason();
    this->message_id = old_message->get_message_id();
    this->origin_nodeid = neighbor_nodeid;
    this->origin_start_time = old_message->get_origin_start_time();
    this->message_body = old_message->get_message_body();
    this->net_content_len = old_message->get_net_content_len();
}

bool Message::is_ok()
{
    return ok;
}

bool Message::is_mode_http()
{
    return is_http;
}

bool Message::thread_should_terminate()
{
    return should_terminate;
}

int Message::get_status_code()
{
    return status_code;
}

int Message::get_content_len()
{
    return content_len;
}

string Message::get_file_path()
{
    return file_path;
}

string Message::get_md5_hash()
{
    return md5_hash;
}

bool Message::is_hello()
{
    return hello;
}

int Message::get_ttl()
{
    return ttl;
}

int Message::get_flood_reason()
{
    return flood_reason;
}
string Message::get_message_id()
{
    return message_id;
}

string Message::get_sender_nodeid()
{
    return sender_nodeid;
}

string Message::get_origin_nodeid()
{
    return origin_nodeid;
}

string Message::get_origin_start_time()
{
    return origin_start_time;
}

string Message::get_message_body()
{
    return message_body;
}

int Message::get_net_content_len()
{
    return net_content_len;
}

shared_ptr<Message> Message::decr_ttl_update_sender(string sender_nodeid)
{
    return make_shared<Message>(ttl - 1, flood_reason, message_id, sender_nodeid, origin_nodeid, origin_start_time, message_body, net_content_len);
}

string Message::to_string()
{
    string result = "";
    if (is_http)
    {
        result += "HTTP/1.1 " + std::to_string(status_code) + " OK\r";
        result += "URI: " + file_path + "\r";
        result += "Content-Length: " + std::to_string(content_len) + "\r";
        result += "MD5: " + md5_hash + "\r";
    }
    else
    {
        result += "TTL: " + std::to_string(ttl) + "\r";
        result += "FLOOD_REASON: " + std::to_string(flood_reason) + "\r";
        result += "MESSAGE_ID: " + message_id + "\r";
        result += "ORIGIN_NODEID: " + origin_nodeid + "\r";
        result += "ORIGIN_START_TIME: " + origin_start_time + "\r";
        result += "CONTENT_LEN: " + std::to_string(net_content_len) + "\r";
        result += "MESSAGE_BODY: " + message_body + "\r";
    }

    return result;
}