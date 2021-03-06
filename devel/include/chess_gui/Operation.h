// Generated by gencpp from file chess_gui/Operation.msg
// DO NOT EDIT!


#ifndef CHESS_GUI_MESSAGE_OPERATION_H
#define CHESS_GUI_MESSAGE_OPERATION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace chess_gui
{
template <class ContainerAllocator>
struct Operation_
{
  typedef Operation_<ContainerAllocator> Type;

  Operation_()
    : type(0)
    , pick_x(0.0)
    , pick_y(0.0)
    , place_x(0.0)
    , place_y(0.0)  {
    }
  Operation_(const ContainerAllocator& _alloc)
    : type(0)
    , pick_x(0.0)
    , pick_y(0.0)
    , place_x(0.0)
    , place_y(0.0)  {
  (void)_alloc;
    }



   typedef uint32_t _type_type;
  _type_type type;

   typedef float _pick_x_type;
  _pick_x_type pick_x;

   typedef float _pick_y_type;
  _pick_y_type pick_y;

   typedef float _place_x_type;
  _place_x_type place_x;

   typedef float _place_y_type;
  _place_y_type place_y;


    enum { OPERATION_GO = 0u };
     enum { OPREATION_CAPTURE = 1u };
 

  typedef boost::shared_ptr< ::chess_gui::Operation_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::chess_gui::Operation_<ContainerAllocator> const> ConstPtr;

}; // struct Operation_

typedef ::chess_gui::Operation_<std::allocator<void> > Operation;

typedef boost::shared_ptr< ::chess_gui::Operation > OperationPtr;
typedef boost::shared_ptr< ::chess_gui::Operation const> OperationConstPtr;

// constants requiring out of line definition

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::chess_gui::Operation_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::chess_gui::Operation_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace chess_gui

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'chess_gui': ['/home/carson/chess_ws/src/chess_gui/msg', '/home/carson/chess_ws/devel/share/chess_gui/msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::chess_gui::Operation_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::chess_gui::Operation_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::chess_gui::Operation_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::chess_gui::Operation_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::chess_gui::Operation_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::chess_gui::Operation_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::chess_gui::Operation_<ContainerAllocator> >
{
  static const char* value()
  {
    return "046491d7b82018f3000327296ff1ce9a";
  }

  static const char* value(const ::chess_gui::Operation_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x046491d7b82018f3ULL;
  static const uint64_t static_value2 = 0x000327296ff1ce9aULL;
};

template<class ContainerAllocator>
struct DataType< ::chess_gui::Operation_<ContainerAllocator> >
{
  static const char* value()
  {
    return "chess_gui/Operation";
  }

  static const char* value(const ::chess_gui::Operation_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::chess_gui::Operation_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# operation type go = 0 ; capture = 1\n\
uint32 OPERATION_GO = 0      \n\
uint32 OPREATION_CAPTURE = 1\n\
\n\
uint32 type\n\
\n\
float32 pick_x\n\
float32 pick_y\n\
\n\
float32 place_x\n\
float32 place_y\n\
\n\
";
  }

  static const char* value(const ::chess_gui::Operation_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::chess_gui::Operation_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.type);
      stream.next(m.pick_x);
      stream.next(m.pick_y);
      stream.next(m.place_x);
      stream.next(m.place_y);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Operation_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::chess_gui::Operation_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::chess_gui::Operation_<ContainerAllocator>& v)
  {
    s << indent << "type: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.type);
    s << indent << "pick_x: ";
    Printer<float>::stream(s, indent + "  ", v.pick_x);
    s << indent << "pick_y: ";
    Printer<float>::stream(s, indent + "  ", v.pick_y);
    s << indent << "place_x: ";
    Printer<float>::stream(s, indent + "  ", v.place_x);
    s << indent << "place_y: ";
    Printer<float>::stream(s, indent + "  ", v.place_y);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CHESS_GUI_MESSAGE_OPERATION_H
