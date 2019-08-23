// Generated by gencpp from file anker_data_publish/AnkerDataType.msg
// DO NOT EDIT!


#ifndef ANKER_DATA_PUBLISH_MESSAGE_ANKERDATATYPE_H
#define ANKER_DATA_PUBLISH_MESSAGE_ANKERDATATYPE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace anker_data_publish
{
template <class ContainerAllocator>
struct AnkerDataType_
{
  typedef AnkerDataType_<ContainerAllocator> Type;

  AnkerDataType_()
    : time_s(0.0)
    , gx(0.0)
    , gy(0.0)
    , gz(0.0)
    , ax(0.0)
    , ay(0.0)
    , az(0.0)
    , odo_right_pos(0.0)
    , odo_left_pos(0.0)
    , odo_right_vel(0.0)
    , odo_left_vel(0.0)
    , opt_pos_x(0.0)
    , opt_pos_y(0.0)
    , opt_quality(0)
    , wall_distance_right(0)
    , wall_distance_left(0)  {
    }
  AnkerDataType_(const ContainerAllocator& _alloc)
    : time_s(0.0)
    , gx(0.0)
    , gy(0.0)
    , gz(0.0)
    , ax(0.0)
    , ay(0.0)
    , az(0.0)
    , odo_right_pos(0.0)
    , odo_left_pos(0.0)
    , odo_right_vel(0.0)
    , odo_left_vel(0.0)
    , opt_pos_x(0.0)
    , opt_pos_y(0.0)
    , opt_quality(0)
    , wall_distance_right(0)
    , wall_distance_left(0)  {
  (void)_alloc;
    }



   typedef double _time_s_type;
  _time_s_type time_s;

   typedef double _gx_type;
  _gx_type gx;

   typedef double _gy_type;
  _gy_type gy;

   typedef double _gz_type;
  _gz_type gz;

   typedef double _ax_type;
  _ax_type ax;

   typedef double _ay_type;
  _ay_type ay;

   typedef double _az_type;
  _az_type az;

   typedef double _odo_right_pos_type;
  _odo_right_pos_type odo_right_pos;

   typedef double _odo_left_pos_type;
  _odo_left_pos_type odo_left_pos;

   typedef double _odo_right_vel_type;
  _odo_right_vel_type odo_right_vel;

   typedef double _odo_left_vel_type;
  _odo_left_vel_type odo_left_vel;

   typedef double _opt_pos_x_type;
  _opt_pos_x_type opt_pos_x;

   typedef double _opt_pos_y_type;
  _opt_pos_y_type opt_pos_y;

   typedef uint16_t _opt_quality_type;
  _opt_quality_type opt_quality;

   typedef uint16_t _wall_distance_right_type;
  _wall_distance_right_type wall_distance_right;

   typedef uint16_t _wall_distance_left_type;
  _wall_distance_left_type wall_distance_left;





  typedef boost::shared_ptr< ::anker_data_publish::AnkerDataType_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::anker_data_publish::AnkerDataType_<ContainerAllocator> const> ConstPtr;

}; // struct AnkerDataType_

typedef ::anker_data_publish::AnkerDataType_<std::allocator<void> > AnkerDataType;

typedef boost::shared_ptr< ::anker_data_publish::AnkerDataType > AnkerDataTypePtr;
typedef boost::shared_ptr< ::anker_data_publish::AnkerDataType const> AnkerDataTypeConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::anker_data_publish::AnkerDataType_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace anker_data_publish

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'anker_data_publish': ['/home/kdq/Workspace/Anker/catkin_ws/src/AnkerDatasPublish/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::anker_data_publish::AnkerDataType_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::anker_data_publish::AnkerDataType_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::anker_data_publish::AnkerDataType_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1a718d0c383faab3290a892f624d74ab";
  }

  static const char* value(const ::anker_data_publish::AnkerDataType_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1a718d0c383faab3ULL;
  static const uint64_t static_value2 = 0x290a892f624d74abULL;
};

template<class ContainerAllocator>
struct DataType< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
{
  static const char* value()
  {
    return "anker_data_publish/AnkerDataType";
  }

  static const char* value(const ::anker_data_publish::AnkerDataType_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 time_s\n\
float64 gx\n\
float64 gy\n\
float64 gz\n\
float64 ax\n\
float64 ay\n\
float64 az\n\
float64 odo_right_pos\n\
float64 odo_left_pos\n\
float64 odo_right_vel\n\
float64 odo_left_vel\n\
float64 opt_pos_x\n\
float64 opt_pos_y\n\
uint16 opt_quality\n\
uint16 wall_distance_right\n\
uint16 wall_distance_left\n\
";
  }

  static const char* value(const ::anker_data_publish::AnkerDataType_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.time_s);
      stream.next(m.gx);
      stream.next(m.gy);
      stream.next(m.gz);
      stream.next(m.ax);
      stream.next(m.ay);
      stream.next(m.az);
      stream.next(m.odo_right_pos);
      stream.next(m.odo_left_pos);
      stream.next(m.odo_right_vel);
      stream.next(m.odo_left_vel);
      stream.next(m.opt_pos_x);
      stream.next(m.opt_pos_y);
      stream.next(m.opt_quality);
      stream.next(m.wall_distance_right);
      stream.next(m.wall_distance_left);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct AnkerDataType_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::anker_data_publish::AnkerDataType_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::anker_data_publish::AnkerDataType_<ContainerAllocator>& v)
  {
    s << indent << "time_s: ";
    Printer<double>::stream(s, indent + "  ", v.time_s);
    s << indent << "gx: ";
    Printer<double>::stream(s, indent + "  ", v.gx);
    s << indent << "gy: ";
    Printer<double>::stream(s, indent + "  ", v.gy);
    s << indent << "gz: ";
    Printer<double>::stream(s, indent + "  ", v.gz);
    s << indent << "ax: ";
    Printer<double>::stream(s, indent + "  ", v.ax);
    s << indent << "ay: ";
    Printer<double>::stream(s, indent + "  ", v.ay);
    s << indent << "az: ";
    Printer<double>::stream(s, indent + "  ", v.az);
    s << indent << "odo_right_pos: ";
    Printer<double>::stream(s, indent + "  ", v.odo_right_pos);
    s << indent << "odo_left_pos: ";
    Printer<double>::stream(s, indent + "  ", v.odo_left_pos);
    s << indent << "odo_right_vel: ";
    Printer<double>::stream(s, indent + "  ", v.odo_right_vel);
    s << indent << "odo_left_vel: ";
    Printer<double>::stream(s, indent + "  ", v.odo_left_vel);
    s << indent << "opt_pos_x: ";
    Printer<double>::stream(s, indent + "  ", v.opt_pos_x);
    s << indent << "opt_pos_y: ";
    Printer<double>::stream(s, indent + "  ", v.opt_pos_y);
    s << indent << "opt_quality: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.opt_quality);
    s << indent << "wall_distance_right: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.wall_distance_right);
    s << indent << "wall_distance_left: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.wall_distance_left);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ANKER_DATA_PUBLISH_MESSAGE_ANKERDATATYPE_H
