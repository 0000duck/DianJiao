// Generated by gencpp from file chess_msgs/Play.msg
// DO NOT EDIT!


#ifndef CHESS_MSGS_MESSAGE_PLAY_H
#define CHESS_MSGS_MESSAGE_PLAY_H

#include <ros/service_traits.h>


#include <chess_msgs/PlayRequest.h>
#include <chess_msgs/PlayResponse.h>


namespace chess_msgs
{

struct Play
{

typedef PlayRequest Request;
typedef PlayResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct Play
} // namespace chess_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::chess_msgs::Play > {
  static const char* value()
  {
    return "9ca8bd096976365b8f806f82ceddea70";
  }

  static const char* value(const ::chess_msgs::Play&) { return value(); }
};

template<>
struct DataType< ::chess_msgs::Play > {
  static const char* value()
  {
    return "chess_msgs/Play";
  }

  static const char* value(const ::chess_msgs::Play&) { return value(); }
};


// service_traits::MD5Sum< ::chess_msgs::PlayRequest> should match 
// service_traits::MD5Sum< ::chess_msgs::Play > 
template<>
struct MD5Sum< ::chess_msgs::PlayRequest>
{
  static const char* value()
  {
    return MD5Sum< ::chess_msgs::Play >::value();
  }
  static const char* value(const ::chess_msgs::PlayRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::chess_msgs::PlayRequest> should match 
// service_traits::DataType< ::chess_msgs::Play > 
template<>
struct DataType< ::chess_msgs::PlayRequest>
{
  static const char* value()
  {
    return DataType< ::chess_msgs::Play >::value();
  }
  static const char* value(const ::chess_msgs::PlayRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::chess_msgs::PlayResponse> should match 
// service_traits::MD5Sum< ::chess_msgs::Play > 
template<>
struct MD5Sum< ::chess_msgs::PlayResponse>
{
  static const char* value()
  {
    return MD5Sum< ::chess_msgs::Play >::value();
  }
  static const char* value(const ::chess_msgs::PlayResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::chess_msgs::PlayResponse> should match 
// service_traits::DataType< ::chess_msgs::Play > 
template<>
struct DataType< ::chess_msgs::PlayResponse>
{
  static const char* value()
  {
    return DataType< ::chess_msgs::Play >::value();
  }
  static const char* value(const ::chess_msgs::PlayResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // CHESS_MSGS_MESSAGE_PLAY_H