// Generated by gencpp from file chess_msgs/ModeRequest.msg
// DO NOT EDIT!


#ifndef CHESS_MSGS_MESSAGE_MODEREQUEST_H
#define CHESS_MSGS_MESSAGE_MODEREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace chess_msgs
{
template <class ContainerAllocator>
struct ModeRequest_
{
  typedef ModeRequest_<ContainerAllocator> Type;

  ModeRequest_()
    : manual(false)  {
    }
  ModeRequest_(const ContainerAllocator& _alloc)
    : manual(false)  {
  (void)_alloc;
    }



   typedef uint8_t _manual_type;
  _manual_type manual;




  typedef boost::shared_ptr< ::chess_msgs::ModeRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::chess_msgs::ModeRequest_<ContainerAllocator> const> ConstPtr;

}; // struct ModeRequest_

typedef ::chess_msgs::ModeRequest_<std::allocator<void> > ModeRequest;

typedef boost::shared_ptr< ::chess_msgs::ModeRequest > ModeRequestPtr;
typedef boost::shared_ptr< ::chess_msgs::ModeRequest const> ModeRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::chess_msgs::ModeRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::chess_msgs::ModeRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace chess_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'chess_msgs': ['/home/carson/chess_ws/src/chess_msgs/msg', '/home/carson/chess_ws/devel/share/chess_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::chess_msgs::ModeRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::chess_msgs::ModeRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::chess_msgs::ModeRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::chess_msgs::ModeRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::chess_msgs::ModeRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::chess_msgs::ModeRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::chess_msgs::ModeRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ecb6956f09b7517cbd6b11452418167f";
  }

  static const char* value(const ::chess_msgs::ModeRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xecb6956f09b7517cULL;
  static const uint64_t static_value2 = 0xbd6b11452418167fULL;
};

template<class ContainerAllocator>
struct DataType< ::chess_msgs::ModeRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "chess_msgs/ModeRequest";
  }

  static const char* value(const ::chess_msgs::ModeRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::chess_msgs::ModeRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
bool manual\n\
";
  }

  static const char* value(const ::chess_msgs::ModeRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::chess_msgs::ModeRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.manual);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ModeRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::chess_msgs::ModeRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::chess_msgs::ModeRequest_<ContainerAllocator>& v)
  {
    s << indent << "manual: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.manual);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CHESS_MSGS_MESSAGE_MODEREQUEST_H
