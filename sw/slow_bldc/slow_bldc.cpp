#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include "lightweightserial.h"
extern "C" {
#include "parser.h"
}
#include "ros/ros.h"
#include "slow_bldc/SetIntParam.h"
#include "slow_bldc/GetIntParam.h"

LightweightSerial *g_serial = NULL;

// this class models the state of the microcontroller
class MCU
{
public:
  std::map
};

static MCU g_mcu;

bool send_pkt(const uint8_t *pkt, const uint32_t len)
{
  if (len >= 252) {
    ROS_ERROR("refusing to send %d-byte packet. must be <252.",
        static_cast<int>(len));
    return false;
  }
  ROS_INFO("sending %d-byte packet", static_cast<int>(len));
  uint8_t framed_pkt[len+5];
  framed_pkt[0] = 0xbe;
  framed_pkt[1] = 0xef;
  framed_pkt[2] = static_cast<uint8_t>(len);
  uint16_t csum = static_cast<uint16_t>(len);
  for (uint32_t i = 0; i < len; i++) {
    framed_pkt[i+3] = pkt[i];
    csum += pkt[i];  // so bad. do something smarter someday.
  }
  framed_pkt[len+3] = static_cast<uint8_t>(csum & 0xff);
  framed_pkt[len+4] = static_cast<uint8_t>(csum >> 8);
  return g_serial->write_block(framed_pkt, len+5);
}

// this function spins forever or until max_seconds
bool rs485_spin(const double max_seconds, const uint8_t expected_pkt_id = 0)
{
  ros::Rate loop_rate(1000);
  ros::Time t_end = ros::Time::now() + ros::Duration(max_seconds);
  while (ros::ok()) {
    if (max_seconds > 0 && t_end < ros::Time::now())
      break;
    loop_rate.sleep();
    ros::spinOnce();
    uint8_t rx_byte = 0;
    while (g_serial->read(&rx_byte)) {
      //printf("rx: %02x\n", rx_byte);
      uint8_t rx_pkt_id = parser_process_byte(rx_byte);
      if (expected_pkt_id && expected_pkt_id == rx_pkt_id)
        return rx_pkt_id;
    }
  }
  return 0;
}

bool set_led(bool on)
{
  uint8_t pkt[2] = { 0x10, 0x00 };
  if (on)
    pkt[1] = 1;
  return send_pkt(pkt, sizeof(pkt));
}

bool get_num_params()
{
  uint8_t pkt[1] = { 0x01 };
  send_pkt(pkt, sizeof(pkt));
  ROS_INFO("calling rs485_spin...");
  rs485_spin(1.0, 0x01);
  ROS_INFO("back from rs485_spin...");
  return 42;
}

void rs485_rx_num_params(const uint32_t payload_len, const uint8_t *payload)
{
  ROS_INFO("rs485_rx_num_params()");
  if (payload_len != 4) {
    ROS_ERROR("unexpected payload len: %d", (int)payload_len);
    return;
  }
  const uint32_t num_params =
      payload[0] | (payload[1]<<8) | (payload[2]<<16) | (payload[3]<<24);
  ROS_INFO("num_params = %d", (int)num_params);
}

void rs485_rx_pkt(const uint32_t len, const uint8_t *data)
{
  ROS_INFO("rs485_rx_pkt(%d)", (int)len);
  if (len == 0) {
    ROS_ERROR("received zero-length rs485 packet");
    return;
  }
  const uint8_t pkt_id = data[0];
  switch(pkt_id)
  {
    case 0x01: rs485_rx_num_params(len-1, data+1); break;
    default: ROS_INFO("unrecognized packet ID: %02x", (int)pkt_id);
  }
}

bool set_int_param(slow_bldc::SetIntParam::Request &request,
    slow_bldc::SetIntParam::Response &response)
{
  int param_name_len = static_cast<int>(request.name.size());
  if (param_name_len > 250) {
    ROS_ERROR("param name len is too long: %s", request.name.c_str());
    return false;
  }
  ROS_INFO("set_int_param(%s, %d)",
      request.name.c_str(), request.value);
  uint8_t pkt[256] = {0};
  pkt[0] = 4;  // packet type 4 = set int param by name
  memcpy(&pkt[1], &request.value, 4);
  strcpy((char *)&pkt[5], request.name.c_str());
  return send_pkt(pkt, 6 + param_name_len);
}

bool get_int_param(slow_bldc::GetIntParam::Request &request,
    slow_bldc::GetIntParam::Response &response)
{
  int param_name_len = static_cast<int>(request.name.size());
  if (param_name_len > 250) {
    ROS_ERROR("param name len is too long: %s", request.name.c_str());
    return false;
  }
  ROS_INFO("get_int_param(%s, %d)",
      request.name.c_str(), request.value);
  uint8_t pkt[256] = {0};
  pkt[0] = 3;  // packet type 3 = get int param by name
  strcpy((char *)&pkt[1], request.name.c_str());
  if (!send_pkt(pkt, 2 + param_name_len))
    return false;
  if (!rs485_spin(0.5, 3)) {
    ROS_ERROR("didn't hear back from MCU for request for parameter [%s]",
        request.name.c_str());
    return false;
  }
  return 
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "slow_bldc");
  ros::NodeHandle nh, nh_private("~");
  std::string rs485_device;
  nh_private.param<std::string>("rs485_device", rs485_device, "/dev/ttyUSB0");
  g_serial = new LightweightSerial(rs485_device.c_str(), 1000000);
  if (!g_serial) {
    ROS_FATAL("couldn't open serial device");
    return 1;
  }
  ROS_INFO("opened %s", rs485_device.c_str());
  parser_init();
  parser_set_rx_pkt_fptr(rs485_rx_pkt);
  const int num_params = get_num_params();
  ROS_INFO("device has %d params", num_params);
  ros::ServiceServer int_param_srv =
      nh.advertiseService("set_int_param", set_int_param);
  rs485_spin(-1);  // spin forever. wooooahhh that makes me feel dizzy
  ROS_INFO("entering slow_bldc spin loop");
  return 0;
}
